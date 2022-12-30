#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "myMath.hpp"
#include "Camera.hpp"
#include "Scene.hpp"



namespace Core
{
	struct AppInitializer
	{
		unsigned int width;
		unsigned int height;
		unsigned int major;
		unsigned int minor;
		const char* name;
		void(*frame_buffer_size_callback)(GLFWwindow* window, int width, int height);
		void(*glDebugOuput)(GLenum source, GLenum type, GLuint id, GLenum severity, 
			GLsizei lengh, const GLchar* message, const void* userParam);
	};

	class App
	{
		private :
			int width; 
			int height;
			int initCam = 0;
			Resources::Scene scene;
			LowRenderer::Camera cam;

			double newMouseX = width/2;
			double newMouseY = height/2;
			double mouseX = 0.f;
			double mouseY = 0.f;
			float mouseDeltaX = 0.f;
			float mouseDeltaY = 0.f;

			void InitWindow(AppInitializer& p_init);
			void ProcessInput(GLFWwindow* window);

			void InitIMGUI();
			void UpdateIMGUI();

		public:
			GLFWwindow* window = nullptr;

			void Update();
			App(AppInitializer& p_init);
			int Init(AppInitializer& p_init);
			~App();

	};

}