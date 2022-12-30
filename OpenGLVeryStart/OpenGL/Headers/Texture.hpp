#pragma once
#include <filesystem>
#include <glad/glad.h>
#include <STB_Image/stb_image.h>
#include "ResourceManager.hpp"


namespace Resources
{
	class Texture : public IResource
	{
	private :
		GLenum format{};
		int width = 0;
		int height = 0;
		int nrChannels = 0;
		GLuint texture = 0;
		unsigned char* data = nullptr;
		GLuint sampler = 0;
		GLint max = 0;

	public:
		float shininess = 32;
		Texture(const std::string& name, std::string const& path, 
			const unsigned int id);
		~Texture();
	};
}