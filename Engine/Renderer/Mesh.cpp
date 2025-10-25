#include "Mesh.hpp"
#include <print>

namespace Unknown
{
	Mesh::Mesh(const Mesh& mesh)
	{
		vertices = mesh.vertices;
		indices = mesh.indices;
		CreateBuffers();
	}

	void Mesh::CreateBuffers()
	{
		CreateVertexBuffer();
		CreateIndexBuffer();
	}


	void Mesh::UpdateData()
	{
		size_t newVertexBufferSize = sizeof(Vertex) * vertices.size();
		size_t newIndexBufferSize = sizeof(uint32_t) * indices.size();

		if (mVertexBufferSize >= newVertexBufferSize) { vertexBuffer->SubData(newVertexBufferSize, vertices.data(), 0); }
		else
		{
			CreateVertexBuffer();
			std::println("reallocation vertex buffer");
		}
		if (mIndexBufferSize >= newIndexBufferSize) { indexBuffer->SubData(newIndexBufferSize, indices.data(), 0); }
		else
		{
			CreateIndexBuffer();
			std::println("reallocation index buffer");
		}

		mVertexBufferSize = newVertexBufferSize;
		mIndexBufferSize = newIndexBufferSize;

	}

	void Mesh::Bind()
	{
		vertexBuffer->Bind();
		indexBuffer->Bind();
	}

	void Mesh::CreateVertexBuffer()
	{
		mVertexBufferSize = sizeof(Vertex) * vertices.size();
		vertexBuffer.reset(VertexBuffer::Create(mVertexBufferSize, vertices.data()));
		vertexBuffer->AddLayout(Vec3);
		vertexBuffer->AddLayout(Vec2);
		vertexBuffer->AddLayout(Vec3);
	}

	void Mesh::CreateIndexBuffer()
	{
		mIndexBufferSize = sizeof(uint32_t) * indices.size();
		indexBuffer.reset(IndexBuffer::Create(mIndexBufferSize, indices.data()));
	}


	Mesh Mesh::CubeMesh()
	{
		Mesh mesh;
		mesh.vertices.push_back({ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f,  0.0f,  1.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f,  0.0f,  1.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f,  0.0f, -1.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f,  0.0f, -1.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f,  0.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f,  0.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f,  1.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f,  1.0f,  0.0f) });

		mesh.indices =
		{
			0, 1, 2,  2, 3, 0,
			4, 5, 6,  6, 7, 4,
			8, 9,10, 10,11, 8,
		   12,13,14, 14,15,12,
		   16,17,18, 18,19,16,
		   20,21,22, 22,23,20
		};

		mesh.CreateBuffers();
		return mesh;
	}

	Mesh Mesh::SkyBoxMesh()
	{
		Mesh mesh;
		mesh.vertices.push_back({ glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec2(0.50f , 0.66666666f), glm::vec3(0.0f,  0.0f,  1.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec2(0.25f,  0.66666666f), glm::vec3(0.0f,  0.0f,  1.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0.25f,  0.33333333f), glm::vec3(0.0f,  0.0f,  1.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.50f , 0.33333333f), glm::vec3(0.0f,  0.0f,  1.0f) });

		mesh.vertices.push_back({ glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.75f,  0.66666666f), glm::vec3(0.0f,  0.0f, -1.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f,-0.5f,-0.5f), glm::vec2(1.00f, 0.66666666f), glm::vec3(0.0f,  0.0f, -1.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, 0.5f,-0.5f), glm::vec2(1.00f, 0.33333333f), glm::vec3(0.0f,  0.0f, -1.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec2(0.75f,  0.33333333f), glm::vec3(0.0f,  0.0f, -1.0f) });

		mesh.vertices.push_back({ glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.75f, 0.66666666f), glm::vec3(-1.0f,  0.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec2(0.50f, 0.66666666f), glm::vec3(-1.0f,  0.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.50f, 0.33333333f), glm::vec3(-1.0f,  0.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec2(0.75f, 0.33333333f), glm::vec3(-1.0f,  0.0f,  0.0f) });

		mesh.vertices.push_back({ glm::vec3(0.5f,-0.5f,-0.5f), glm::vec2(0.00f, 0.66666666f), glm::vec3(1.0f,  0.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f,-0.5f, 0.5f), glm::vec2(0.25f, 0.66666666f), glm::vec3(1.0f,  0.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0.25f, 0.33333333f), glm::vec3(1.0f,  0.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, 0.5f,-0.5f), glm::vec2(0.00f, 0.33333333f), glm::vec3(1.0f,  0.0f,  0.0f) });

		mesh.vertices.push_back({ glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.50f , 1.0000000f), glm::vec3(0.0f, -1.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, -0.5f,-0.5f), glm::vec2(0.25f,  1.0000000f), glm::vec3(0.0f, -1.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.25f,  0.6666666f), glm::vec3(0.0f, -1.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec2(0.50f , 0.6666666f), glm::vec3(0.0f, -1.0f,  0.0f) });

		mesh.vertices.push_back({ glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec2(0.50f , 0.0000000f), glm::vec3(0.0f,  1.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, 0.5f,-0.5f), glm::vec2(0.25f,  0.0000000f), glm::vec3(0.0f,  1.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0.25f,  0.3333333f), glm::vec3(0.0f,  0.0f,  0.0f) });
		mesh.vertices.push_back({ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.50f , 0.3333333f), glm::vec3(0.0f,  1.0f,  0.0f) });

		mesh.indices =
		{
			0, 1, 2,  2, 3, 0,
			4, 5, 6,  6, 7, 4,
			8, 9,10, 10,11, 8,
		   12,13,14, 14,15,12,
		   16,17,18, 18,19,16,
		   20,21,22, 22,23,20
		};

		mesh.CreateBuffers();
		return mesh;
	}

	Mesh Mesh::QuadMesh()
	{
		Mesh mesh;
		Vertex vertices[4];
		vertices[0].position = glm::vec3(0.5, 0.5, 0.0);
		vertices[1].position = glm::vec3(0.5, -0.5, 0.0);
		vertices[2].position = glm::vec3(-0.5, -0.5, 0.0);
		vertices[3].position = glm::vec3(-0.5, 0.5, 0.0);

		vertices[0].textureCoordinate = glm::vec2(1, 1);
		vertices[1].textureCoordinate = glm::vec2(1, 0);
		vertices[2].textureCoordinate = glm::vec2(0, 0);
		vertices[3].textureCoordinate = glm::vec2(0, 1);

		vertices[0].normal = glm::vec3(0, 0, 1);
		vertices[1].normal = glm::vec3(0, 0, 1);
		vertices[2].normal = glm::vec3(0, 0, 1);
		vertices[3].normal = glm::vec3(0, 0, 1);

		mesh.vertices.insert(mesh.vertices.begin(), std::begin(vertices), std::end(vertices));

		mesh.indices = { 0,1,2,2,3,0 };

		mesh.CreateBuffers();

		return mesh;
	}
}
