#include "UiDevelopment.hpp"
#include <Core/Macro.hpp>
#include <msdfgen/msdfgen.h>
#include <msdfgen/msdfgen-ext.h>
#include <Macro.hpp>
#include <stb/stb_image_write.h>
#include <thread>
#include <functional>
#include <memory>
#include <print>
#include <mutex>
#include <vector>
#include <cstring>
#include <fstream>
#include <GLFW/glfw3.h>

using namespace glm;
using namespace Unknown;

std::mutex mtx;

static void LoadCharacters(
Image& image, char character, msdfgen::FontHandle* font)
{
	UNK_SCOPE_PROFILER();
	msdfgen::Shape shape;
	mtx.lock();
	msdfgen::loadGlyph(shape, font, character, msdfgen::FONT_SCALING_EM_NORMALIZED);
	mtx.unlock();
	shape.normalize();
	msdfgen::edgeColoringSimple(shape, 3.0);

	msdfgen::Bitmap<float, 3> msdf(64, 64);
	msdfgen::SDFTransformation t(msdfgen::Projection(32, msdfgen::Vector2(0.50, 0.50)), msdfgen::Range(0.125));

	msdfgen::generateMSDF(msdf, shape, t);

	image.data = new unsigned char[64 * 64 * 4];
	image.size = { 64, 64 };

	msdfgen::BitmapRef<float, 3> bitmap = msdf;


	for (int i = 0, j = 0; i < 64 * 64 * 4; i++)
	{
		if ((i % 4) == 3)
		{
			image.data[i] = 255;
			continue;
		}
		image.data[i] = msdfgen::pixelFloatToByte(bitmap.pixels[j]);
		j++;
	}

}

const char startCharacter = '!'; // 33
const int endCharacter = 127; // 127
const int characterCount = endCharacter - startCharacter;

static void print(std::string message)
{
	std::println("{}", message);
}


namespace Unknown
{

	static std::string readFile(const std::string& filename)
	{
		if (filename.size() == 0)
		{
			return std::string();
		}
		std::string result;

		std::ifstream input(filename);

		if (!input.is_open())
		{
			printf("Error: file not found [%s]\n", filename.c_str());
			return std::string();
		}

		input.seekg(0, std::ios::end);
		size_t size = input.tellg();
		input.seekg(0, std::ios::beg);

		result.resize(size);

		input.read(&result[0], size);

		return result;
	}

	static Ref<Shader> LoadShader(const ShaderFile& files)
	{
		assert(files.vertex.size() != 0);
		assert(files.fragment.size() != 0);


		ShaderSource source;

		source.vertex = readFile(files.vertex);
		source.fragment = readFile(files.fragment);
		source.geometry = readFile(files.geometry);
		source.tessellation = readFile(files.tessellation);
		source.compute = readFile(files.compute);


		Ref<Shader> shader;
		shader.reset(Shader::Create(source));
		return shader;
	}

	class MSDFFont
	{
	public:
		void LoadFromTTF(const char* filename);
		void LoadFromPng(const char* filename);
		void WriteImage(const char* filename);
		Image GetAtlas() const { return mAtlas; }
		Image& GetAtlasRef() { return mAtlas; }
		void SetAtlas(const Image& image) { mAtlas = image; }

		Ref<Texture> GetAtlasTexture() const { return mAtlasTexture; }

	private:
		Image mAtlas;
		Ref<Texture> mAtlasTexture;
		std::string mCacheFile;
	};

	void MSDFFont::LoadFromTTF(const char* filename)
	{
		UNK_CORE_CHECK_FILE_EXIST(filename);


		msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype();
		if (ft == nullptr)
		{
			UNK_CLIENT_ERROR("Failed to initialize freetype");
		}
		msdfgen::FontHandle* font = msdfgen::loadFont(ft, "Cascadia-Regular.ttf");
		if (font == nullptr)
		{
			UNK_CLIENT_ERROR("Failed to load font");
		}

		int totalWidth = 0;
		Image* letterImages = new Image[characterCount];

		std::vector<std::thread> threads;

		for (int i = 0; i < characterCount; i++)
		{
			LoadCharacters(letterImages[i], char(i + startCharacter), font);
			totalWidth += 64;
		}

		mAtlas.size = { totalWidth, 64 };
		mAtlas.data = new unsigned char[4 * totalWidth * 64];
		mAtlas.format = RGBA;
		int heightOffset = 0;
		for (int i = 0; i < 64; i++) // height
		{
			for (int j = 0; j < characterCount; j++)
			{
				unsigned char* destination = mAtlas.data + (letterImages[j].size.x * 4 * j) + (mAtlas.size.x * 4 * i);
				unsigned char* source = letterImages[j].data + (letterImages[j].size.x * 4 * i);
				memcpy(destination, source, letterImages[j].size.x * 4);
			}
		}

		TextureProperty property;
		property.image = mAtlas;
		property.magFilter = LINEAR;
		property.minFilter = LINEAR;

		mAtlasTexture.reset(Texture::Create(property));
	}

	void MSDFFont::LoadFromPng(const char* filename)
	{
		UNK_CORE_CHECK_FILE_EXIST(filename);

		mAtlas.Load(filename);
		TextureProperty property;
		property.image = mAtlas;
		property.magFilter = LINEAR;
		property.minFilter = LINEAR;
		
		mAtlasTexture.reset(Texture::Create(property));
	}

	void MSDFFont::WriteImage(const char* filename)
	{
		mAtlas.Write(filename);
	}

	struct MSDFFontVertex
	{
		glm::vec3 position = glm::vec3(0);
		glm::vec2 uv = glm::vec2(0);
		uint32_t textId = 0;
	};

	class MSDFFontMeshGenerator
	{
	public:

		void Bind();

		void GenerateMesh(const char* text);

		std::vector<MSDFFontVertex> GetVertices() const { return mVertices; }
		std::vector<MSDFFontVertex>& GetVerticesRef() { return mVertices; }
		void SetVertices(std::vector<MSDFFontVertex> vertex) { mVertices = vertex; }

		std::vector<uint32_t> GetIndices() const { return mIndices; }
		std::vector<uint32_t>& GetIndicesRef() { return mIndices; }
		void SetIndices(std::vector<uint32_t> index) { mIndices = index; }

	private:
		std::vector<MSDFFontVertex> mVertices;
		std::vector<uint32_t> mIndices;
		Ref<VertexBuffer> mVertexBuffer;
		Ref<IndexBuffer> mIndexBuffer;
	};

	void MSDFFontMeshGenerator::Bind()
	{
		mVertexBuffer->Bind();
		mIndexBuffer->Bind();
	}

	void MSDFFontMeshGenerator::GenerateMesh(const char* text)
	{
		uint32_t count = strlen(text);

		for (int i = 0; i < count; i++)
		{
			MSDFFontVertex vertices[4];
			vertices[0].position = glm::vec3(0.5 - i, 0.5, 0.0);
			vertices[1].position = glm::vec3(0.5 - i, -0.5, 0.0);
			vertices[2].position = glm::vec3(-0.5 - i, -0.5, 0.0);
			vertices[3].position = glm::vec3(-0.5 - i, 0.5, 0.0);

			vertices[0].uv = glm::vec2(0, 1);
			vertices[1].uv = glm::vec2(0, 0);
			vertices[2].uv = glm::vec2(1, 0);
			vertices[3].uv = glm::vec2(1, 1);

			vertices[0].textId = text[i] - startCharacter;
			vertices[1].textId = text[i] - startCharacter;
			vertices[2].textId = text[i] - startCharacter;
			vertices[3].textId = text[i] - startCharacter;

			uint32_t indices[6] = { 0 + (4 * i), 1 + (4 * i), 2 + (4 * i), 2 + (4 * i), 3 + (4 * i), 0 + (4 * i) };

			for (int j = 0; j < sizeof(vertices) / sizeof(MSDFFontVertex); j++)
			{
				mVertices.push_back(vertices[j]);
			}
			for (int j = 0; j < sizeof(indices) / sizeof(uint32_t); j++)
			{
				mIndices.push_back(indices[j]);
			}
		}

		mVertexBuffer.reset(VertexBuffer::Create(sizeof(MSDFFontVertex) * mVertices.size(), mVertices.data()));
		mIndexBuffer.reset(IndexBuffer::Create(sizeof(uint32_t) * mIndices.size(), mIndices.data()));

		mVertexBuffer->AddLayout(Vec3);
		mVertexBuffer->AddLayout(Vec2);
		mVertexBuffer->AddLayout(Int);
	}

	class MSDFTextRenderer
	{
	public:
		void Initialize();
		void Submit(MSDFFontMeshGenerator& mesh, MSDFFont& font, const Transform& transform);

	public:
		// Getters
		Camera GetCamera() const { return mCamera; }
		Camera& GetCameraRef() { return mCamera; }
		void SetCamera(const Camera& val) { mCamera = val; }
	private:
		Camera mCamera;
		Ref <Shader> textShader;
		Ref<RenderCommand> mRenderCommand;
	};

	void MSDFTextRenderer::Initialize()
	{
		textShader = LoadShader({ "basic.vert", "basic.frag" });
		mRenderCommand.reset(RenderCommand::Create());
	}

	void MSDFTextRenderer::Submit(MSDFFontMeshGenerator& mesh, MSDFFont& font, const Transform& transform)
	{
		mCamera.Calculate();
		mesh.Bind();
		glm::mat4 model = transform.GetMatrix();
		glm::mat4 view = mCamera.GetViewMatrix();
		glm::mat4 projection = mCamera.GetProjectionMatrix();

		textShader->Bind();
		int test = int(glfwGetTime() * 5);
		textShader->SetUniform(Int, "test", &test);
		textShader->SetUniform(Mat4, "modelMatrix", &model);
		textShader->SetUniform(Mat4, "viewMatrix", &view);
		textShader->SetUniform(Mat4, "projectionMatrix", &projection);

		mRenderCommand->DrawIndexed(mesh.GetIndicesRef().size());
	}

}


MSDFTextRenderer rend;
MSDFFontMeshGenerator gen;	
MSDFFont font;
void UiDevelopment::OnStart()
{

	font.LoadFromTTF("Cascadia-Regular.ttf");
	gen.GenerateMesh("HelloWorld");
	rend.Initialize();
	
}

void UiDevelopment::OnRenderUi()
{
}

void UiDevelopment::OnUpdate(float dt)
{
	GetRenderer()->BeginFrame(vec4(0.1), GetWindow()->GetSize());
	font.GetAtlasTexture()->Bind(0);
	rend.GetCameraRef() = GetRenderer()->GetCameraRef();
	Transform transform;
	transform.scale = vec3(0.1);
	rend.Submit(gen, font, transform);
	GetRenderer()->EndFrame();
}

void UiDevelopment::OnEnd()
{
}

CREATE_APPLICATION(UiDevelopment)
