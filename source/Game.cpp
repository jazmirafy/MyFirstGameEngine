#include "Game.h"
#include <iostream>
#include <GLFW/glfw3.h>

bool Game::Init(){
    //vertex shader source code
    std::string vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;

    out vec3 vColor;

    uniform vec2 uOffset;
    
    void main() {
        vColor = color;
        gl_Position = vec4(position.x + uOffset.x, position.y + uOffset.y, position.z, 1.0);
    }
)";
    //fragment shader source code
    std::string fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;

    in vec3 vColor;
    
    void main() {
        FragColor = vec4(vColor, 1.0);
    }
)";
    auto& graphicsAPI = eng::Engine::GetInstance().GetGraphicsAPI();
    auto shaderProgram = graphicsAPI.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
    m_material.SetShaderProgram(shaderProgram);

    
    std::vector<float> vertices = {
        /* //rectangle
        //position           color
        0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
       0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 0.0f */
        //triangle
        //position              //color
        0.0f, 0.5f, 0.0f,       2.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,     0.0f, 2.0f, 0.0f,
        0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 2.0f,

    };

    
    std::vector<unsigned int> indices = {
        //rectangle indices
       /* 0, 1, 2,
        0, 2, 3*/
        //triangle indices
        0, 1, 2
    };


    eng::VertexLayout vertexLayout;

    //positon
    vertexLayout.elements.push_back({
        0,
        3,
        GL_FLOAT,
        0
        });
    //color
    vertexLayout.elements.push_back({
        1,
        3,
        GL_FLOAT,
        sizeof(float) * 3
        });
    vertexLayout.stride = sizeof(float) * 6;

    m_mesh = std::make_unique<eng::Mesh>(vertexLayout, vertices, indices);

    return true;

}
void Game::Update(float deltaTime){

	//get instance of input manager
	auto& input = eng::Engine::GetInstance().GetInputManager();
	if (input.IsKeyPressed(GLFW_KEY_A)) {

        m_offsetX -= 0.01f;
		
	}
    else if(input.IsKeyPressed(GLFW_KEY_D)) {

        m_offsetX += 0.01f;

    }
    else if (input.IsKeyPressed(GLFW_KEY_W)) {

        m_offsetY += 0.01f;

    }
    else if (input.IsKeyPressed(GLFW_KEY_S)) {

        m_offsetY -= 0.01f;

    }

    m_material.SetParam("uOffset", m_offsetX, m_offsetY);

    eng::RenderCommand command;
    command.material = &m_material;
    command.mesh = m_mesh.get();

    auto& renderQueue = eng::Engine::GetInstance().GetRenderQueue();
    renderQueue.Submit(command);

}
void Game::Destroy(){


}