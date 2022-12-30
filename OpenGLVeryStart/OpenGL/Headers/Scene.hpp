#pragma once
#include "ResourceManager.hpp"
#include "Light.hpp"
#include "Object.hpp"
#include "Camera.hpp"

#include <glm/trigonometric.hpp>

namespace Resources
{
	class Scene
	{
		public:
			~Scene();
			Resources::ResourceManager manager;
			std::vector <LowRenderer::Object> objects;
			std::vector<LowRenderer::DirectionalLight> directionalLights;
			std::vector<LowRenderer::PointLight> pointLights;
			std::vector<LowRenderer::SpotLight> spotLights;

			void InitObjects(LowRenderer::Camera& cam);
			void UpdateObjects(LowRenderer::Camera& cam);

			void InitLights();
			void UpdateLights();
			void UpdateDirLights();
			void UpdatePointLights();
			void UpdateSpotLights();

			void AddParentID(const int idParent, const int idChild);
			void RemoveParent(const int idParent, const int idChild);

	};

}
