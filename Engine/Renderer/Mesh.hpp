#pragma once
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Material.hpp"

namespace Unk
{
	struct Mesh
	{
		Mesh() {}
		Mesh(const Mesh& mesh);
		std::shared_ptr<VertexBuffer> vertexBuffer = nullptr;
		std::shared_ptr<IndexBuffer> indexBuffer = nullptr;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		Material material;

		void CreateBuffers();
		void UpdateData();
		void Bind();

		size_t mVertexBufferSize = 0;
		size_t mIndexBufferSize = 0;


		static Mesh QuadMesh();
		static Mesh CubeMesh();
		static Mesh SkyBoxMesh();
	private:
		void CreateVertexBuffer();
		void CreateIndexBuffer();
	};
}