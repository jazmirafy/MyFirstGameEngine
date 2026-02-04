//this is used to define vertex layout to communicate vertex structure to the gpu/ description of the format of our vertex data
#pragma once
#include <GL/glew.h>
#include <vector>
#include <stdint.h>

namespace eng {
	struct VertexElement {

		GLuint index; //attribute location from the shader
		GLuint size; //number of components
		GLuint type; //data type (ex: GL_FLOAT)
		uint32_t offset; //bytes offset from start of vertex
	};

	struct VertexLayout {

		std::vector<VertexElement> elements;
		uint32_t stride = 0; //total size of a single vertex


	};
}