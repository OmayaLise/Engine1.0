#include "Mesh.hpp"

namespace LowRenderer
{

	Mesh::Mesh(Resources::Model* model, Resources::Texture* texture,
		Resources::Shader* shader)
		: model{ model }, texture{ texture }, shader{ shader }
	{
		this->model->Init();
	}

	void Mesh::Draw(Maths:: Mat4 viewMatrix, Maths::Mat4 projectionMatrix)
	{
		mvpMatrix = projectionMatrix* viewMatrix * modelMatrix;
		model->Draw();
	}

	void Mesh::SetTransformModel(const Maths::Vec3 & translation, 
		const Maths::Vec3 & scale, const Maths::Vec3 & rotation)
	{
		modelMatrix = Maths::Mat4::CreateTransformationMatrix(translation, scale, rotation);
	}

}