#pragma once
#include <GL/glew.h>
#include "graphics/VertexLayout.h"

namespace eng {

	class Mesh {
	public:

		Mesh(const VertexLayout& layout, const std::vector<float>& vertices, const std::vector<uint32_t>& indices);
		Mesh(const VertexLayout& layout, const std::vector<float>& vertices);
		//disable copy and assignment to avoid accidental resource duplication
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;


		void Bind();
		void Draw();

	private:
		VertexLayout m_vertexLayout;
		
		GLuint m_VBO = 0; //for vertices
		GLuint m_EBO = 0; //for indices
		GLuint m_VAO = 0;

		size_t m_vertexCount = 0;
		size_t m_indexCount = 0;
	};
}