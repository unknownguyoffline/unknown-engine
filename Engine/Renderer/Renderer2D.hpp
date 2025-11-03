#pragma once
#include <Renderer/Types.hpp>
#include <Renderer/Texture.hpp>
#include <Renderer/VertexBuffer.hpp>
#include <Renderer/IndexBuffer.hpp>
#include <Renderer/RenderCommand.hpp>
#include <Renderer/Camera.hpp>
#include <Renderer/Shader.hpp>
#include <Utility/Memory.hpp>

namespace Unknown
{
	struct Viewport
	{
		glm::ivec2 position = glm::ivec2(0);
		glm::ivec2 size = glm::ivec2(800, 600);
	};
	struct QuadrilateralVertex
	{
		glm::vec3 position = glm::vec3(0);
		glm::vec4 color = glm::vec4(1);
	};

	struct CircleVertex
	{
		glm::vec3 position = glm::vec3(0);
		glm::vec4 color = glm::vec4(1);
	};

	struct SpriteVertex
	{
		glm::vec3 position = glm::vec3(0);
		glm::vec4 color = glm::vec4(1);
		glm::ivec2 spriteIndex = glm::ivec2(0);
		uint32_t textureSlot = 0;
	};

	struct Quadrilateral
	{
		Transform transform = Transform();
		glm::vec4 color = glm::vec4(1.0);
	};

	struct Circle
	{
		Transform transform = Transform();
		glm::vec4 color = glm::vec4(1.0);
	};

	struct Sprite
	{
		Transform transform = Transform();
		glm::ivec2 spriteCount = glm::ivec2(1);
		glm::ivec2 spriteIndex = glm::ivec2(0);
		Ref<Texture> texture;
	};

	class Renderer2D
	{
	public:
		void Initialize();
		void Terminate();

		void BeginFrame();
		void EndFrame();

		void PushQuadrilateral(const Quadrilateral& quadrilateral);
		void PushCircle(const Circle& crcle);
		void PushSprite(const Sprite& sprite);

		void Flush();

		void FlushQuadrilateral();
		void FlushCircle();
		void FlushSprite();

		void SetCamera(const Camera& camera);
		Camera GetCamera() const;
		Camera& GetCameraRef();
	private:
		std::vector<QuadrilateralVertex> mQuadrilateralVertices;
		std::vector <uint32_t> mQuadrilateralIndices;
		Ref<Shader> mQuadrilateralShader;
		Ref<VertexBuffer> mQuadrilateralVertexBuffer;
		Ref<IndexBuffer> mQuadrilateralIndexBuffer;

		std::vector<CircleVertex> mCircleVertices;
		std::vector <uint32_t> mCircleIndices;
		Ref<Shader> mCircleShader;

		std::vector<SpriteVertex> mSpriteVertices;
		std::vector <uint32_t> mSpriteIndices;
		std::vector<Ref<Texture>> mSpriteTextures;
		Ref<Shader> mSpriteShader;

		Ref<RenderCommand> mRenderCommand;
		Camera mCamera;

		Viewport mViewport;
	};
}
