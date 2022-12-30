#include "Shader.hpp"

namespace Resources
{
	Shader::Shader(const std::string& name, std::string const& path,
		const unsigned int id)
	{
		SetVertexShader("Resources/Shaders/VertexShader.vert");
		SetFragmentShader("Resources/Shaders/FragmentShader.frag");
		Link();
	}
	bool Shader::SetVertexShader(std::filesystem::path const& filename)
	{
		if (!fs.is_open())
			fs.open(filename);

		while (std::getline(fs, line))
		{
			stringVertexShader += "\n" + line;
		}
		vertexShaderSource = stringVertexShader.c_str();
		fs.close();

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		return true;
	}

	bool Shader::SetFragmentShader(std::filesystem::path const& filename)
	{
		line = "";
		if (!fs.is_open())
			fs.open(filename);

		while (std::getline(fs, line))
		{
			stringFragmentShader += "\n" + line;
		}
		fragmentShaderSource = stringFragmentShader.c_str();
		fs.close();

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		return true;
	}

	bool Shader::Link()
	{
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return true;
	}
	
}