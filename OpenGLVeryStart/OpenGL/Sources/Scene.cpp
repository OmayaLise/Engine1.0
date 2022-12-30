#include "Scene.hpp"

namespace Resources
{

	Scene::~Scene()
	{
		for (LowRenderer::Object& object : objects)
		{
			delete object.mesh;
		}
	}

	void SetInt(int shaderProgram, const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
	}

	void SetFloat(int shaderProgram, const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
	}
	
	void SetVec3v(int shaderProgram, const std::string& name, const Maths::Vec3& value)
	{
		glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value.x);
	}

	void Scene::InitObjects(LowRenderer::Camera& cam)
	{
		manager.Create < Resources::Shader>("Shader", "");
		LowRenderer::Object ground("Ground", new LowRenderer::Mesh(manager.Create< Resources::Model>("CubeMod", "Resources/Obj/cube.obj"), 
			manager.Create < Resources::Texture>("GroundText","Resources/Textures/sample.png"), manager.GetResource<Resources::Shader>("Shader")),
			{ 0.f, -5.f, -25.f }, { 50.f, 1.f, 50.f }, { 0.f, 0.f,0.f });
		objects.push_back(ground);
		LowRenderer::Object potatOS("PotatOS", new LowRenderer::Mesh(manager.Create< Resources::Model>("PotatOMod", "Resources/Obj/potatOS.obj"),
			manager.Create < Resources::Texture>("PotatOSText","Resources/Textures/potatOS.png"), manager.GetResource<Resources::Shader>("Shader")),
			{ 10.f, -3.f, -20.f }, { 0.5f,0.5f,0.5f }, { 0.f, 0.f,0.f });
		objects.push_back(potatOS);
		LowRenderer::Object slime("Slime", new LowRenderer::Mesh(manager.Create< Resources::Model>("SlimeMod", "Resources/Obj/Slime.obj"),
			manager.Create < Resources::Texture>("SlimeText","Resources/Textures/Slime.png"), manager.GetResource<Resources::Shader>("Shader")),
			{ -13.f, -2.f, -18.f }, { 1.f,1.f,1.f }, { 0.f, -45.f,0.f });
		objects.push_back(slime);
		LowRenderer::Object companion("Companion", new LowRenderer::Mesh(manager.Create< Resources::Model>("CompanionMod", "Resources/Obj/companion.obj"),
			manager.Create < Resources::Texture>("CompanionText","Resources/Textures/companion.png"), manager.GetResource<Resources::Shader>("Shader")),
			{ 15.f, 2.f, -25.f }, { 0.2f,0.2f,0.2f }, { 0.f, 0.f,0.f });
		objects.push_back(companion);
		LowRenderer::Object chocobo("Chocobo", new LowRenderer::Mesh(manager.Create< Resources::Model>("ChocoboMod", "Resources/Obj/chocobo.obj"),
			manager.Create < Resources::Texture>("ChocoboText","Resources/Textures/chocobo.png"), manager.GetResource<Resources::Shader>("Shader")),
			{ -2.f, -2.f, -20.f }, { 0.1f,0.1f,0.1f }, {0.f, 0.f,180.f });
		objects.push_back(chocobo);

	}

	void Scene::UpdateObjects(LowRenderer::Camera& cam)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			objects[i].mesh->modelMatrix = objects[i].transform.modelMatrix;
			glUseProgram(objects[i].mesh->shader->shaderProgram);
			SetInt(objects[i].mesh->shader->shaderProgram, "texture1", objects[i].mesh->texture->GetResourceID());
			SetFloat(objects[i].mesh->shader->shaderProgram, "shininess", objects[i].mesh->texture->shininess);
			SetVec3v(objects[i].mesh->shader->shaderProgram, "viewPos", cam.position);
			glUniformMatrix4fv(glGetUniformLocation(objects[i].mesh->shader->shaderProgram, "mvpMatrix"), 1, GL_TRUE, &objects[i].mesh->mvpMatrix.mat[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(objects[i].mesh->shader->shaderProgram, "modelMatrix"), 1, GL_TRUE, &objects[i].mesh->modelMatrix.mat[0][0]);
			UpdateLights();
			objects[i].UpdateAll();
			objects[i].mesh->Draw(cam.viewMatrix, cam.projectionMatrix);
		}
	}

	void Scene::InitLights()
	{
		LowRenderer::DirectionalLight dirLight({ -1.f, 0.f, 0.f }, { 0.5f, 0.5f, 0.5f },
			{ 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		directionalLights.push_back(dirLight);

		LowRenderer::PointLight pointLight({ 1.f, 4.f, 1.f }, { 0.f, 0.f, 0.f },
			{ 1.f, 0.f, 0.f }, { 1.f, 1.f, 1.f }, 1.f, 0.09f, 0.032f);
		pointLights.push_back(pointLight);

		LowRenderer::SpotLight spotLight({ 3.f, 3.f, 1.f }, { 0.f, -1.f, 0.f },
			60.f, 90.f, { 0.1f,0.1f, 0.1f }, { 1.f, 0.f, 1.f }, { 1.f, 1.f, 1.f },
			1.f, 0.09f, 0.032f);

		spotLights.push_back(spotLight);
	}

	void Scene::UpdateLights()
	{
		UpdateDirLights();
		UpdatePointLights();
		UpdateSpotLights();
	}

	void Scene::UpdateDirLights()
	{
		for (unsigned int i = 0; i < directionalLights.size(); i++)
		{
			std::string arrayInfo = "directionalLights[" + std::to_string(i) + "].";
			SetInt(objects[i].mesh->shader->shaderProgram, "nbDirLight", directionalLights.size());
			SetVec3v(objects[i].mesh->shader->shaderProgram, (arrayInfo + "direction").c_str(), directionalLights[i].direction);
			SetVec3v(objects[i].mesh->shader->shaderProgram, (arrayInfo + "ambientColor").c_str(), directionalLights[i].ambientColor);
			SetVec3v(objects[i].mesh->shader->shaderProgram, (arrayInfo + "diffuseColor").c_str(),directionalLights[i].diffuseColor);
			SetVec3v(objects[i].mesh->shader->shaderProgram, (arrayInfo + "specularColor").c_str(),directionalLights[i].specularColor);
		}
	}

	void Scene::UpdatePointLights()
	{
		for (unsigned int i = 0; i < pointLights.size(); i++)
		{
			std::string arrayInfo = "pointLights[" + std::to_string(i) + "].";
			SetInt(objects[i].mesh->shader->shaderProgram, "nbPointLight", pointLights.size());
			SetVec3v(objects[i].mesh->shader->shaderProgram, (arrayInfo + "position").c_str(), pointLights[i].position);
			SetVec3v(objects[i].mesh->shader->shaderProgram, (arrayInfo + "ambientColor").c_str(), pointLights[i].ambientColor);
			SetVec3v(objects[i].mesh->shader->shaderProgram, (arrayInfo + "diffuseColor").c_str(), pointLights[i].diffuseColor);
			SetVec3v(objects[i].mesh->shader->shaderProgram, (arrayInfo + "specularColor").c_str(), pointLights[i].specularColor);
			SetFloat(objects[i].mesh->shader->shaderProgram, (arrayInfo + "constant").c_str(), pointLights[i].constant);
			SetFloat(objects[i].mesh->shader->shaderProgram, (arrayInfo + "linear").c_str(), pointLights[i].linear);
			SetFloat(objects[i].mesh->shader->shaderProgram, (arrayInfo + "quadratic").c_str(), pointLights[i].quadratic);
		}
	}

	void Scene::UpdateSpotLights()
	{
		for (unsigned int i = 0; i < spotLights.size(); i++)
		{
			std::string arrayInfo = "spotLights[" + std::to_string(i) + "].";
			SetInt(objects[i].mesh->shader->shaderProgram, "nbSpotLight", spotLights.size());
			SetVec3v(objects[i].mesh->shader->shaderProgram, (arrayInfo + "position").c_str(), spotLights[i].position);
			SetVec3v(objects[i].mesh->shader->shaderProgram, (arrayInfo + "direction").c_str(), spotLights[i].direction);
			SetVec3v(objects[i].mesh->shader->shaderProgram, (arrayInfo + "ambientColor").c_str(), spotLights[i].ambientColor);
			SetVec3v(objects[i].mesh->shader->shaderProgram, (arrayInfo + "diffuseColor").c_str(), spotLights[i].diffuseColor);
			SetVec3v(objects[i].mesh->shader->shaderProgram, (arrayInfo + "specularColor").c_str(), spotLights[i].specularColor);
			SetFloat(objects[i].mesh->shader->shaderProgram, (arrayInfo + "constant").c_str(), spotLights[i].constant);
			SetFloat(objects[i].mesh->shader->shaderProgram, (arrayInfo + "linear").c_str(), spotLights[i].linear);
			SetFloat(objects[i].mesh->shader->shaderProgram, (arrayInfo + "quadratic").c_str(), spotLights[i].quadratic);
			SetFloat(objects[i].mesh->shader->shaderProgram, (arrayInfo + "cutOff").c_str(), glm::cos(glm::radians(spotLights[i].cutOff)));
			SetFloat(objects[i].mesh->shader->shaderProgram, (arrayInfo + "outerCutOff").c_str(), glm::cos(glm::radians(spotLights[i].outerCutOff)));
		}
	}

	void Scene::AddParentID(const int idParent, const int idChild)
	{

		if (!objects[idChild].parent && &objects[idChild] != objects[idParent].parent && &objects[idChild] != &objects[idParent])
		{
			objects[idParent].children.push_back(&objects[idChild]);
			objects[idChild].parent = &objects[idParent];
			objects[idChild].childID += objects[idParent].children.size();
		}
	}

	void Scene::RemoveParent(const int idParent, const int idChild)
	{
		objects[idChild].parent = nullptr;
		objects[idParent].children.erase(objects[idParent].children.begin());
	}
}