#pragma once
#include "ResourceManager.hpp"
#include <Model.hpp>
#include <Light.hpp>

namespace Resources 
{
	class Shader : public IResource
	{
	private :
		std::ifstream fs;
		std::string line = "";
		std::string stringVertexShader;
		std::string stringFragmentShader;
		const char* vertexShaderSource;
		const char* fragmentShaderSource;
		int success;
		char infoLog[512];
		int vertexShader;
		int fragmentShader;

		bool SetVertexShader(std::filesystem::path const& filename);
		bool SetFragmentShader(std::filesystem::path const& filename);
		bool Link();

	public:
		int shaderProgram; 

		Shader(const std::string& name, std::string const& path,
			const unsigned int id);
	};

}