#include "Model.hpp"

#include <string>

namespace Resources
{
	Model::Model(const std::string& name, std::string const& path, 
		const unsigned int id)
	{
		resourcePath = path;
		resourceName = name;
		LoadOBJ(path);
	}

	Model::~Model()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Model::LoadOBJ(std::filesystem::path const& filename)
	{
		Vertex vertexTemp;
		std::ifstream fs;

		std::vector<Maths::Vec3> tempPosition;
		std::vector<Maths::Vec3> tempNormal;
		std::vector<Maths::Vec2> tempTextCoor;

		std::vector<unsigned int> tempPositionIndices;
		std::vector<unsigned int> tempNormalIndices;
		std::vector<unsigned int> tempTextCoorIndices;

		std::string line = "";
		std::string prefix = "";
		std::stringstream ss;
		Maths::Vec3 tempV3;
		Maths::Vec2 tempV2;

		if (!fs.is_open())
			fs.open(filename);

		while (std::getline(fs, line))
		{
			ss.clear();
			ss.str(line);
			ss >> prefix;

			if (prefix == "v")
			{
				ss >> tempV3.x >> tempV3.y >> tempV3.z;
				tempPosition.push_back(tempV3);
			}
			else if (prefix == "vt")
			{
				ss >> tempV2.x >> tempV2.y;
				tempTextCoor.push_back(tempV2);
			}
			else if (prefix == "vn")
			{
				ss >> tempV3.x >> tempV3.y >> tempV3.z;
				tempNormal.push_back(tempV3);
			}
			else if (prefix == "f")
			{
				char slash;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				ss >> vertexIndex[0] >> slash >> uvIndex[0] >> slash >> normalIndex[0] >> vertexIndex[1] >> slash >> uvIndex[1] >> slash >> normalIndex[1] >> vertexIndex[2] >> slash >> uvIndex[2] >> slash >> normalIndex[2];

				tempPositionIndices.push_back(vertexIndex[0]);
				tempPositionIndices.push_back(vertexIndex[1]);
				tempPositionIndices.push_back(vertexIndex[2]);

				tempTextCoorIndices.push_back(uvIndex[0]);
				tempTextCoorIndices.push_back(uvIndex[1]);
				tempTextCoorIndices.push_back(uvIndex[2]);

				tempNormalIndices.push_back(normalIndex[0]);
				tempNormalIndices.push_back(normalIndex[1]);
				tempNormalIndices.push_back(normalIndex[2]);
			}
		
		}
		for (unsigned int i = 0; i < tempPositionIndices.size(); i++)
		{
			vertexTemp.position = tempPosition[tempPositionIndices[i] - 1];
			vertexTemp.normal = tempNormal[tempNormalIndices[i] - 1];
			vertexTemp.textureUV = tempTextCoor[tempTextCoorIndices[i] - 1];
			vertexBuffer.push_back(vertexTemp);
			indexBuffer.push_back(i);
	
		}
		fs.close();
	}

	void Model::Init()
	{
		Core::Debug::Log::Print(resourceName +" Init is called\n");
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(Vertex), vertexBuffer.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,indexBuffer.size() * sizeof(uint32_t), indexBuffer.data(), GL_STATIC_DRAW);


		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Resources::Vertex), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Resources::Vertex), (void*)(sizeof(Maths::Vec3)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Resources::Vertex), (void*)(2 * sizeof(Maths::Vec3)));
		glEnableVertexAttribArray(2);
	}

	void Model::Draw()
	{
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_INT, 0);
	}

}