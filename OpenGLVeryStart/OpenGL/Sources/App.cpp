#include "App.hpp"

namespace Core
{

	App::App(AppInitializer& p_init)
	{
		cam.screenWidth = p_init.width;
		cam.screenHeight = p_init.height;
		Init(p_init);
	}

	App::~App()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	int App::Init(AppInitializer& p_init)
	{
	
		InitWindow(p_init);
		InitIMGUI();
		scene.InitObjects(cam);
		scene.InitLights();

		return true;
	}

	void App::InitWindow(AppInitializer& p_init)
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, p_init.major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, p_init.minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);


		// glfw window creation
		// --------------------
		window = glfwCreateWindow(p_init.width, p_init.height, p_init.name, NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, p_init.frame_buffer_size_callback);

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}

		GLint flags = 0;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(p_init.glDebugOuput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}
		glEnable(GL_DEPTH_TEST);

	}

	void App::Update()
	{
		glfwPollEvents();
		ProcessInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		cam.Update(cam.inputs);
		scene.UpdateObjects(cam);
		UpdateIMGUI();

		glfwSwapBuffers(window);
	}

	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
	void App::ProcessInput(GLFWwindow* window )
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cam.inputs.moveForward = true;
		else
			cam.inputs.moveForward = false;

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cam.inputs.moveBackward = true;
		else
			cam.inputs.moveBackward = false;

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			cam.inputs.moveDown = true;
		else
			cam.inputs.moveDown = false;

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			cam.inputs.moveUp = true;
		else
			cam.inputs.moveUp = false;

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cam.inputs.moveLeft = true;
		else
			cam.inputs.moveLeft = false;

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cam.inputs.moveRight = true;
		else
			cam.inputs.moveRight = false;

		if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			if (initCam == 0)
			{
				glfwSetCursorPos(window, width / 2, height / 2);
			}
			initCam++;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwGetCursorPos(window, &newMouseX, &newMouseY);
			mouseDeltaX = (float)(newMouseX - mouseX);
			mouseDeltaY = (float)(newMouseY - mouseY);
			mouseX = newMouseX;
			mouseY = newMouseY;
			cam.inputs.deltaX = mouseDeltaX;
			cam.inputs.deltaY = mouseDeltaY;
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			initCam = 0;
			mouseDeltaX = 0;
			mouseDeltaY = 0;
			cam.inputs.deltaX = mouseDeltaX;
			cam.inputs.deltaY = mouseDeltaY;
		}
	}

	void App::InitIMGUI()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	void App::UpdateIMGUI()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Lights");
		for (unsigned int i = 0; i < scene.directionalLights.size(); i++)
		{
			if (ImGui::CollapsingHeader(("Directionals Lights " + std::to_string(i)).c_str(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::SliderFloat3(("Direction D" + std::to_string(i)).c_str(),
					&scene.directionalLights[i].direction.x, -1.f, 1.f, "%.1f", 0);
				ImGui::ColorEdit3(("Ambient D" + std::to_string(i)).c_str(), scene.directionalLights[i].ambientColor.e);
				ImGui::ColorEdit3(("Diffuse D" + std::to_string(i)).c_str(), scene.directionalLights[i].diffuseColor.e);
				ImGui::ColorEdit3(("Specular D" + std::to_string(i)).c_str(), scene.directionalLights[i].specularColor.e);
			}
		}
		if (ImGui::Button("Add directional light (Max 5)"))
		{
			if (scene.directionalLights.size() < 5)
			{
				LowRenderer::DirectionalLight dirLight({ -1.f, 0.f, 0.f }, { 0.1f, 0.1f, 0.1f },
					{ 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
				scene.directionalLights.push_back(dirLight);
			}
		}
		for (unsigned int i = 0; i < scene.pointLights.size(); i++)
		{
			if (ImGui::CollapsingHeader(("Points Lights " + std::to_string(i)).c_str(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::SliderFloat3(("Position P" + std::to_string(i)).c_str(),
					&scene.pointLights[i].position.x, -50.f, 50.f, "%.1f", 0);
				ImGui::ColorEdit3(("Ambient P" + std::to_string(i)).c_str(), scene.pointLights[i].ambientColor.e);
				ImGui::ColorEdit3(("Diffuse P" + std::to_string(i)).c_str(), scene.pointLights[i].diffuseColor.e);
				ImGui::ColorEdit3(("Specular P" + std::to_string(i)).c_str(), scene.pointLights[i].specularColor.e);
			}
		}
		if (ImGui::Button("Add point light (Max 5)"))
		{
			if (scene.pointLights.size() < 5)
			{
				LowRenderer::PointLight pointLight({ 1.f, 4.f, 1.f }, { 0.f, 0.f, 0.f },
					{ 1.f, 0.f, 0.f }, { 1.f, 1.f, 1.f }, 1.f, 0.09f, 0.032f);
				scene.pointLights.push_back(pointLight);
			}
		}
		for (unsigned int i = 0; i < scene.spotLights.size(); i++)
		{
			if (ImGui::CollapsingHeader(("Spots Lights " + std::to_string(i)).c_str(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::SliderFloat3(("Position S" + std::to_string(i)).c_str(),
					&scene.spotLights[i].position.x, -50.f, 50.f, "%.1f", 0);
				ImGui::SliderFloat3(("Direction S" + std::to_string(i)).c_str(),
					&scene.spotLights[i].direction.x, -1.f, 1.f, "%.1f", 0);
				ImGui::SliderFloat(("cutOff " + std::to_string(i)).c_str(),
					&scene.spotLights[i].cutOff, 0.f, 90.f, "%.1f", 0);
				ImGui::SliderFloat(("outerCutOff " + std::to_string(i)).c_str(),
					&scene.spotLights[i].outerCutOff, 0.f, 90.f, "%.1f", 0);
				ImGui::ColorEdit3(("Ambient S" + std::to_string(i)).c_str(), scene.spotLights[i].ambientColor.e);
				ImGui::ColorEdit3(("Diffuse S" + std::to_string(i)).c_str(), scene.spotLights[i].diffuseColor.e);
				ImGui::ColorEdit3(("Specular S" + std::to_string(i)).c_str(), scene.spotLights[i].specularColor.e);
			}
		}
		if (ImGui::Button("Add spot light (Max 5)"))
		{
			if (scene.spotLights.size() < 5)
			{
				LowRenderer::SpotLight spotLight({ 3.f, 3.f, 1.f }, { 0.f, -1.f, 0.f },
					15.f, 25.f, { 1.f,1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f },
					1.f, 0.09f, 0.032f);
				scene.spotLights.push_back(spotLight);
			}
		}
		ImGui::End();

		ImGui::Begin("Objects");
		for (unsigned int i = 0; i < scene.objects.size() ; i++)
		{
			if (ImGui::CollapsingHeader((scene.objects[i].name + " ID " + std::to_string(i)).c_str(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::SliderFloat3(("Position O" + std::to_string(i)).c_str(),
					&scene.objects[i].transform.pos.x, -50.f, 50.f, "%.1f", 0);
				ImGui::SliderFloat3(("Scale O" + std::to_string(i)).c_str(),
					&scene.objects[i].transform.scale.x, 0.f, 1.f, "%.1f", 0);
				ImGui::SliderFloat3(("Rotation O" + std::to_string(i)).c_str(),
					&scene.objects[i].transform.eulerRot.x, -180.f, 180.f, "%.1f", 0);
				ImGui::SliderFloat(("Shininess O" + std::to_string(i)).c_str(), &scene.objects[i].mesh->texture->shininess, 1.f, 64.f, "%.1f", 0);

				if (scene.objects[i].parent)
				{
					std::string parent = "Object's parent is " +scene.objects[i].parent->name;
					ImGui::TextColored(ImVec4(255.f,0.f,0.f,255.f),(parent).c_str());
					if (ImGui::Button(("Click to remove parent " + std::to_string(i)).c_str()))
						scene.RemoveParent(scene.objects[i].parentID, i);
				}
				else 
				{
					ImGui::SliderInt( ("Parent ID " + std::to_string(i)).c_str(), &scene.objects[i].parentID, 0, scene.objects.size() - 1, "%d", 0);
					if (ImGui::Button(("Click to valid parent ID " +std::to_string(i)).c_str()) & scene.objects[i].parentID > -1 )
						scene.AddParentID(scene.objects[i].parentID, i);
				}

			}
		}
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}


}