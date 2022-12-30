#pragma once
#include "ResourceManager.hpp"
#include "myMath.hpp"
#include <sstream>
#include <glad/glad.h>

namespace Resources
{
	struct Vertex
	{
		Maths::Vec3 position;
		Maths::Vec3 normal;
		Maths::Vec2 textureUV;
	};

	class Model : public IResource
	{
	private :
		void LoadOBJ(std::filesystem::path const& filename);

	public:
		unsigned int VBO, VAO, EBO;

		std::vector<Vertex> vertexBuffer;
		std::vector<uint32_t> indexBuffer;

		Model(const std::string& name, std::string const& path, 
			const unsigned int id);
		~Model();

		void Init();
		void Draw();

	};

}