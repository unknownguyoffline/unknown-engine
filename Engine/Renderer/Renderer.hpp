#pragma once
#include "CoreTypes.hpp"
#include <memory>
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "RenderCommand.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "Sprite.hpp"
#include "TextureLibrary.hpp"
#include "ShaderLibrary.hpp"
#include "FrameBuffer.hpp"
#include <Utility/Memory.hpp>

#define BASIC_3D_SHADER "basic3D"
#define BASIC_TEXTURE_SHADER "basicTexture"
#define BASIC_CIRCLE_SHADER "basicCircle"

namespace Unk
{
	struct RendererProperty
	{
		GraphicApi api = Opengl;
		bool enableSkybox = true;
		bool enableDepthTest = true;
		bool enableBlending = true;
		bool enableCulling = false;
	};

	struct MeshRenderer
	{
		Mesh mesh;
		Material material;
	};


	class Renderer
	{
	public:
		Renderer(const RendererProperty& property);

		void Initialize(const RendererProperty& property);

		void SetViewport(const glm::vec2& size, const glm::vec2& offset = glm::vec2(0, 0));
		void BeginFrame(const glm::vec4& color = glm::vec4(0.5f), const glm::uvec2& size = { 800, 600 });
		void EndFrame();

		void Submit(Mesh& mesh, Material& material, const Transform& transform);
		void Submit(Ref<VertexBuffer> vertexBuffer, Ref<IndexBuffer> indexBuffer, Ref<Shader> shader, int count, DrawPrimitive primitive = Triangle);
		void Submit(Ref<VertexBuffer> vertexBuffer, Ref<Shader> shader, int count, DrawPrimitive primitive = Triangle);

		void SetCameraProperty(const CameraProperty& property);
		void SetCamera(const Camera& camera);

		CameraProperty GetCameraProperty();
		Camera GetCamera() const;

		void LoadTexture(const char* filename, const char* identifier);
		void CreateTexture(const TextureProperty& property, const char* identifier);
		void CreateTexture(Image& image, const char* identifier);
		void RemoveTexture(const char* identifier);
		Texture* GetTexture(const char* identifier);

		void LoadShader(const ShaderFile& files, const char* identifier);
		void CreateShader(const ShaderSource& sources, const char* identifier);
		void RemoveShader(const char* identifier);
		Shader* GetShader(const char* identifier);
		void ClearScreen(const glm::vec4& color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
		Camera& GetCameraRef();

		void EnableWireframe();

		Ref<RenderCommand> GetRenderCommand() { return mRenderCommand; }

		void AddLight(const Mesh& mesh, const Transform& transform);
	private:
		Camera mCamera;
		TextureLibrary mTextureLibrary;
		ShaderLibrary mShaderLibrary;
		Ref<RenderCommand> mRenderCommand;
		Ref<FrameBuffer> mFrameBuffer;

		std::vector<Transform> mLightTransforms;
	};
}