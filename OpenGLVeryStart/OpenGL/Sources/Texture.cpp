#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <STB_Image/stb_image.h>

namespace Resources
{
	Texture::Texture(const std::string& name, std::string const& path, const unsigned int id)
	{
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

		glGenTextures(1, &texture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);

		// create a sampler and parameterize it
		// ------------------------------------
		glGenSamplers(1, &sampler);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.f);

		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);


		resourceID = id;
		resourceName = name;
		resourcePath = path;
		glBindTextureUnit(resourceID, texture);
		glBindSampler(resourceID, sampler);

	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &texture);
		glDeleteSamplers(1, &sampler);
	}
}