#include "render/Mesh.h"
#include "graphics/GraphicsAPI.h"
#include "Engine.h"

namespace eng {

	Mesh::Mesh(const VertexLayout& layout, const std::vector<float>& vertices, const std::vector<uint32_t>& indices) {

		m_vertexLayout = layout;
		auto& graphicsAPI = Engine::GetInstance().GetGraphicsAPI();

		m_VBO =  graphicsAPI.CreateVertexBuffer(vertices);
		m_EBO =  graphicsAPI.CreateIndexBuffer(indices);

		//generate and bind vao
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		//bind vbo
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		//setup vertex attributes
		for (auto& element : m_vertexLayout.elements) {

			glVertexAttribPointer(element.index, element.size, element.type, GL_FALSE, m_vertexLayout.stride, (void*)(uintptr_t)element.offset);
			glEnableVertexAttribArray(element.index);
		}

		//bind indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

		//now unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//calculate vertex and index count
		m_vertexCount = (vertices.size() * sizeof(float) / m_vertexLayout.stride);
		m_indexCount = indices.size();
	}
	Mesh::Mesh(const VertexLayout& layout, const std::vector<float>& vertices) {

		m_vertexLayout = layout;
		auto& graphicsAPI = Engine::GetInstance().GetGraphicsAPI();

		m_VBO = graphicsAPI.CreateVertexBuffer(vertices);

		//generate and bind vao
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		//bind vbo
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		//setup vertex attributes
		for (auto& element : m_vertexLayout.elements) {

			glVertexAttribPointer(element.index, element.size, element.type, GL_FALSE, m_vertexLayout.stride, (void*)(uintptr_t)element.offset);
			glEnableVertexAttribArray(element.index);
		}

		//now unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//calculate vertex count
		m_vertexCount = (vertices.size() * sizeof(float) / m_vertexLayout.stride);

	}
	void Mesh::Bind() {

		glBindVertexArray(m_VAO);

	}

	void Mesh::Draw() {

		if (m_indexCount > 0) {
			glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
		}
	}

}