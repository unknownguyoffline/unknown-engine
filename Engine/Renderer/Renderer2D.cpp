#include "Renderer2D.hpp"
#include <Core/Macro.hpp>

namespace Unknown
{
	
	const char* quadrilateralVertexShader = R"(
	#version 450 core
	
	layout(location = 0) in vec3 aPos;
	layout(location = 1) in vec4 aColor;

	out vec4 color;

	uniform mat4 view;
	uniform mat4 projection;

	void main()
	{
		gl_Position = projection * view * vec4(aPos, 1.0);
		color = aColor;
	}
	)";

	const char* quadrilateralFragmentShader = R"(
	#version 450 core
	
	out vec4 outputColor;

	in vec4 color;

	void main()
	{
		outputColor = vec4(1.0);
	}
	)";

	void Renderer2D::Initialize()
	{
		mRenderCommand.reset(RenderCommand::Create());
		mQuadrilateralShader.reset(Shader::Create({ quadrilateralVertexShader , quadrilateralFragmentShader }));

		CameraProperty property;
		property.size.x = float(mViewport.size.x) / float(mViewport.size.y);
		property.size.y = float(mViewport.size.y) / float(mViewport.size.y); // = 1.f
		property.projectionType = Orthographic;
		
		mCamera.SetProperty(property);
	}

	void Renderer2D::Terminate()
	{

	}

	void Renderer2D::BeginFrame()
	{
		mCamera.Calculate();
	}

	void Renderer2D::EndFrame()
	{
		Flush();
	}

	void Renderer2D::PushQuadrilateral(const Quadrilateral& quadrilateral)
	{
		QuadrilateralVertex vertices[4];

		vertices[0].position = glm::vec3( 0.5, 0.5, 0.0);
		vertices[1].position = glm::vec3( 0.5,-0.5, 0.0);
		vertices[2].position = glm::vec3(-0.5,-0.5, 0.0);
		vertices[3].position = glm::vec3(-0.5, 0.5, 0.0);

		glm::mat4 transformMatrix = quadrilateral.transform.GetMatrix();

		for (int i = 0; i < sizeof(vertices) / sizeof(QuadrilateralVertex); i++)
		{

			vertices[i].position = glm::vec3(transformMatrix * glm::vec4(vertices[i].position, 1.0));
			vertices[i].color = quadrilateral.color;

			mQuadrilateralVertices.push_back(vertices[i]);

		}


		uint32_t quadrilateralCount = mQuadrilateralIndices.size() / 6;
		uint32_t indices[] = { 0,1,2,2,3,0 };

		for (int i = 0; i < sizeof(indices) / sizeof(uint32_t); i++)
		{

			indices[i] = indices[i] + (quadrilateralCount * 4);
			mQuadrilateralIndices.push_back(indices[i]);

		}
	}

	void Renderer2D::PushCircle(const Circle& crcle)
	{

	}

	void Renderer2D::PushSprite(const Sprite& sprite)
	{

	}

	void Renderer2D::Flush()
	{
		FlushQuadrilateral();
		FlushCircle();
		FlushSprite();
	}

	void Renderer2D::FlushQuadrilateral()
	{
		mQuadrilateralShader->Bind();
		mQuadrilateralVertexBuffer.reset(VertexBuffer::Create(mQuadrilateralVertices.size() * sizeof(QuadrilateralVertex), mQuadrilateralVertices.data()));
		mQuadrilateralIndexBuffer.reset(IndexBuffer::Create(mQuadrilateralIndices.size() * sizeof(uint32_t), mQuadrilateralIndices.data()));

		mQuadrilateralVertexBuffer->AddLayout(Vec3);
		mQuadrilateralVertexBuffer->AddLayout(Vec4);

		mQuadrilateralVertexBuffer->Bind();
		mQuadrilateralIndexBuffer->Bind();
		glm::mat4 view = mCamera.GetViewMatrix();
		glm::mat4 projection = mCamera.GetProjectionMatrix();

		mQuadrilateralShader->SetUniform(Mat4, "view", &view);
		mQuadrilateralShader->SetUniform(Mat4, "projection", &projection);

		mRenderCommand->DrawIndexed(mQuadrilateralIndices.size());

		mQuadrilateralIndices.clear();
		mQuadrilateralVertices.clear();
	}

	void Renderer2D::FlushCircle()
	{

	}

	void Renderer2D::FlushSprite()
	{

	}

	void Renderer2D::SetCamera(const Camera& camera)
	{
		mCamera = camera;
	}

	Camera Renderer2D::GetCamera() const
	{
		return mCamera;
	}

	Camera& Renderer2D::GetCameraRef()
	{
		return mCamera;
	}

}
