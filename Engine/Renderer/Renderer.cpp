#include "Renderer.hpp"
#include <string>
#include <Application.hpp>

namespace Unknown
{
	const char* basic3DVertexShader = R"(
#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aNormal;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 normal;
out vec3 fragPos;

void main()
{
	normal = aNormal;
    fragPos = vec3(modelMatrix * vec4(aPos, 1.0));
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}
)";

	const char* basic3DFragmentShader = R"(
#version 450 core

uniform vec4 color;
uniform vec3 cameraPosition;
uniform vec3 lightPosition[256];

out vec4 outputColor;

in vec3 normal;
in vec3 fragPos;

void main()
{
    float cameraDistance = distance(cameraPosition, fragPos);
    vec3 lightDirection = normalize(lightPosition[0] - fragPos);
    float d = max(dot(normal, lightDirection), 0.0);
	outputColor = vec4(color.r * d, color.g * d, color.b * d, 1.0);
}
)";

	const char* baseTextureVertexShader = R"(
#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureCoordinate;
layout (location = 2) in vec3 aNormal;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec2 textureCoordinate;

void main()
{
	textureCoordinate = aTextureCoordinate;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}
)";

	const char* baseTextureFragmentShader = R"(
#version 450 core

out vec4 outputColor;

uniform sampler2D texture0;

in vec2 textureCoordinate;

void main()
{
	outputColor = vec4(texture(texture0, textureCoordinate * -1.0).r);
	if(outputColor.r < 0.9)
		discard;
}
)";

	const char* basicCircleVertexShader = R"(
#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureCoordinate;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec2 textureCoordinate;

void main()
{
	textureCoordinate = aTextureCoordinate;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}
)";

	const char* basicCircleFragmentShader = R"(
#version 450 core

out vec4 outputColor;
uniform vec4 color;
in vec2 textureCoordinate;

void main()
{
    float dis = distance(textureCoordinate, vec2(0.5,0.5));
	if(dis < 0.5)
		outputColor = color;
	else
		discard;
}
)";

	Renderer::Renderer(const RendererProperty& property)
	{
		Initialize(property);
	}

	void Renderer::Initialize(const RendererProperty& property)
	{
		mRenderCommand.reset(RenderCommand::Create());
		if (property.enableDepthTest)
			mRenderCommand->EnableDepthTest();
		if (property.enableBlending)
			mRenderCommand->EnableBlending();
		if (property.enableCulling)
			mRenderCommand->EnableCulling();

		CreateShader({ basic3DVertexShader, basic3DFragmentShader }, BASIC_3D_SHADER);
		CreateShader({ baseTextureVertexShader, baseTextureFragmentShader }, BASIC_TEXTURE_SHADER);
		CreateShader({ basicCircleVertexShader, basicCircleFragmentShader }, BASIC_CIRCLE_SHADER);
	}

	void Renderer::ClearScreen(const glm::vec4& color)
	{
		mRenderCommand->SetClearColor(color);
		mRenderCommand->ClearColorBuffer();
		mRenderCommand->ClearDepthBuffer();
	}

	Camera& Renderer::GetCameraRef()
	{
		return mCamera;
	}

	void Renderer::EnableWireframe()
	{
		mRenderCommand->EnableWireframe();
	}

	void Renderer::AddLight(const Mesh& mesh, const Transform& transform)
	{
		mLightTransforms.push_back(transform);
	}

	void Renderer::SetViewport(const glm::vec2& size, const glm::vec2& offset)
	{
		mRenderCommand->SetViewport(size, offset);
	}

	//void Renderer::BeginFrame(const glm::vec4& color, std::shared_ptr<FrameBuffer> targetFrameBuffer, bool clear)
	//{
	//	mFrameBuffer = targetFrameBuffer;
	//	if (mFrameBuffer.get() != nullptr)
	//	{
	//		mFrameBuffer->Bind();
	//		SetViewport(mFrameBuffer->GetProperty().size);
	//		auto property = mCamera.GetProperty();
	//		property.size = mFrameBuffer->GetProperty().size;
	//		mCamera.SetProperty(property);
	//	}
	//
	//	ClearScreen(color);
	//	mCamera.Calculate();
	// }

	void Renderer::BeginFrame(const glm::vec4& color, const glm::uvec2& size)
	{
		SetViewport(size);

		CameraProperty property = mCamera.GetProperty();
		property.size = size;

		mCamera.SetProperty(property);
		ClearScreen(color);
	}

	void Renderer::EndFrame()
	{
		if (mFrameBuffer.get() != nullptr)
			mFrameBuffer->UnBind();

		mLightTransforms.clear();
	}

	void Renderer::Submit(Mesh& mesh, Material& material, const Transform& transform)
	{
		mesh.Bind();
		Shader* shader = mShaderLibrary.Get(material.shader);
		shader->Bind();
		glm::mat4 model = transform.GetMatrix();
		glm::mat4 view = glm::mat4(1.0);
		if (material.shader == "skybox")
		{
			view = glm::mat4(glm::mat3(mCamera.GetViewMatrix()));

		}
		else
		{
			view = mCamera.GetViewMatrix();
		}
		glm::mat4 proj = mCamera.GetProjectionMatrix();
		glm::vec3 cameraPosition = mCamera.GetProperty().position;
		shader->SetUniform(Mat4, "modelMatrix", &model);
		shader->SetUniform(Mat4, "viewMatrix", &view);
		shader->SetUniform(Mat4, "projectionMatrix", &proj);
		shader->SetUniform(Vec4, "color", &material.color);
		shader->SetUniform(Vec3, "cameraPosition", &cameraPosition);
		float t = Application::GetInstance()->GetTimer().GetElapsedTime();
		shader->SetUniform(Float, "time", &t);

		for (int i = 0; i < 32; i++)
		{
			shader->SetUniform(Int, ("textures[" + std::to_string(i) + "]").c_str(), &i);
			if (material.texture[i].size() != 0)
				mTextureLibrary.Get(material.texture[i])->Bind(i);
		}

		for (int i = 0; i < mLightTransforms.size() && i < 255; i++)
		{
			shader->SetUniform(Vec3, ("lightPosition[" + std::to_string(i) + "]").c_str(), &mLightTransforms[i]);
		}
		mRenderCommand->DrawIndexed(mesh.indices.size());
	}

	void Renderer::Submit(Ref<VertexBuffer> vertexBuffer, Ref<IndexBuffer> indexBuffer, Ref<Shader> shader, int count, DrawPrimitive primitive)
	{
		vertexBuffer->Bind();
		indexBuffer->Bind();
		shader->Bind();
		mRenderCommand->DrawIndexed(count, primitive);
	}

	void Renderer::Submit(Ref<VertexBuffer> vertexBuffer, Ref<Shader> shader, int count, DrawPrimitive primitive /*= Triangle*/)
	{
		vertexBuffer->Bind();
		shader->Bind();
		mRenderCommand->DrawArrays(count, primitive);
	}

	Camera Renderer::GetCamera() const
	{
		return mCamera;
	}

	void Renderer::LoadTexture(const char* filename, const char* identifier)
	{
		mTextureLibrary.Load(filename, identifier);
	}

	void Renderer::CreateTexture(const TextureProperty& property, const char* identifier)
	{
		mTextureLibrary.Create(property, identifier);
	}

	void Renderer::CreateTexture(Image& image, const char* identifier)
	{
		mTextureLibrary.Create(image, identifier);
	}

	void Renderer::RemoveTexture(const char* identifier)
	{
		mTextureLibrary.Remove(identifier);
	}

	Texture* Renderer::GetTexture(const char* identifier)
	{
		return mTextureLibrary.Get(identifier);
	}

	void Renderer::LoadShader(const ShaderFile& files, const char* identifier)
	{
		mShaderLibrary.Load(files, identifier);
	}

	void Renderer::CreateShader(const ShaderSource& sources, const char* identifier)
	{
		mShaderLibrary.Create(sources, identifier);
	}

	void Renderer::RemoveShader(const char* identifier)
	{
		mShaderLibrary.Remove(identifier);
	}

	Shader* Renderer::GetShader(const char* identifier)
	{
		return mShaderLibrary.Get(identifier);
	}

	void Renderer::SetCamera(const Camera& camera)
	{
		mCamera = camera;
	}

	void Renderer::SetCameraProperty(const CameraProperty& property)
	{
		mCamera.SetProperty(property);
	}

	CameraProperty Renderer::GetCameraProperty()
	{
		return mCamera.GetProperty();
	}
}
