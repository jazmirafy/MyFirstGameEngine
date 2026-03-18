#include "Engine.h"
#include "Application.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace eng {

	void keyCallback(GLFWwindow* window, int key, int, int action, int) {

		auto& inputManager = eng::Engine::GetInstance().GetInputManager();
		if (action == GLFW_PRESS) {

			inputManager.SetKeyPressed(key, true);

		}
		else if (action == GLFW_RELEASE) {

			inputManager.SetKeyPressed(key, false);
		}
	}
	Engine& Engine::GetInstance() {
		static Engine instance;
		return instance;
	}

	bool Engine::Init(int width, int height) {
		
		//check for valid application instance
		if (!m_application) {
			return false;
		}
		//if application instance is valid, create a window
		//initialize library

		//if we failed to initialize the glfw library stop the program
		if (!glfwInit())
		{
			std::cout << "Error initializing GLFW" << std::endl;
			return false;
		}

		//let glfw know which open gl context is intended to use
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//attempt to create a window
		//check whether the window was successfully created
		// if failed notify the user, terminate the glfw library and exit the program
		m_window = glfwCreateWindow(width, height, "Egypt's Game Engine <3", nullptr, nullptr);
		if (m_window == nullptr)
		{
			std::cout << "Error creating window" << std::endl;
			glfwTerminate();
			return false;
		}

		glfwSetKeyCallback(m_window, keyCallback);

		glfwMakeContextCurrent(m_window);

		//if we fail to initialize glew library terminate the program
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Error initializing GLEW" << std::endl;
			glfwTerminate();
			return false;
		}

		return m_application->Init();
	}

	
	void Engine::Run() {
		//check for valid application
		if (!m_application) {
			return;
		}

		m_lastTimePoint = std::chrono::high_resolution_clock::now();

		while (!glfwWindowShouldClose(m_window) && !m_application->NeedsToBeClosed()) {
			//process input
			glfwPollEvents();
			
			auto now = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(now - m_lastTimePoint).count();
			m_lastTimePoint = now;

			//update game/application logic
			m_application->Update(deltaTime);

		
			//render
			m_graphicsAPI.SetClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			m_graphicsAPI.ClearBuffers();

			
			m_renderQueue.Draw(m_graphicsAPI);


			glfwSwapBuffers(m_window);

		}
	}

	void Engine::Destroy() {

		if (m_application) {
			m_application->Destroy();
			m_application.reset();
			glfwTerminate();
			m_window = nullptr;
		}
	}
	void Engine::SetApplication(Application * app) {

		m_application.reset(app);
	}
	Application* Engine::GetApplication() {
		return m_application.get();
	}

	InputManager& Engine::GetInputManager() {

		return m_inputManager;
	}
	GraphicsAPI& Engine::GetGraphicsAPI() {

		return m_graphicsAPI;
	}
	RenderQueue& Engine::GetRenderQueue() {

		return m_renderQueue;
	}

}