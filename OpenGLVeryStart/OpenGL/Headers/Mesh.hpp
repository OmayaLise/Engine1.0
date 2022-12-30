#pragma once
#include "Model.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

namespace LowRenderer
{

	class Mesh
	{

	public:
		Maths::Mat4 modelMatrix;
		Maths::Mat4 mvpMatrix;
		Resources::Model* model;
		Resources::Texture* texture;
		Resources::Shader* shader;

		Mesh(Resources::Model* model, Resources::Texture* texture,
			Resources::Shader* shader);
		void Draw(Maths::Mat4 viewMatrix, Maths::Mat4 projectionMatrix);
		void SetTransformModel(const Maths::Vec3& translation, 
			const Maths::Vec3& scale, const Maths::Vec3& rotation);
	};

}