#pragma once
//this will serve as the centralized interface for rending operations
#include "GL/glew.h"
#include <memory>
#include <string>
#include <vector>
namespace eng {

	class ShaderProgram;
	class Material;
	class Mesh;

	class GraphicsAPI {

	public:
		//this will receive the source code for vertex and fragment shader compile them, link them to shader program and return new shader program instance
		std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
		
		GLuint CreateVertexBuffer(const std::vector<float>& vertices);
		GLuint CreateIndexBuffer(const std::vector<uint32_t>& indices);
		
		void SetClearColor(float r, float g, float b, float a);
		void ClearBuffers();
		
		void BindShaderProgram(ShaderProgram* shaderProgram);
		void BindMaterial(Material* material);
		void BindMesh(Mesh* mesh);
		void DrawMesh(Mesh* mesh);
	};
}