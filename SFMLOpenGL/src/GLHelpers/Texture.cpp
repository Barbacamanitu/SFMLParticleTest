#include "stdafx.h"
#include "GLHelpers\Texture.h"
#include "ErrorHandling\SPLException.h"
#include "GLHelpers\LodePNG.h"
#include <iostream>

namespace spl
{


	Texture::~Texture()
	{
	}

	void Texture::createFromFile(std::string filename)
	{
		GLint err = glGetError();
		std::vector<unsigned char> pixelData;
		size_t width, height;
		unsigned error = lodepng::decode(pixelData, width, height, filename);
		if (error)
		{
			throw spl::SPLException(spl::ErrorMessages::TEXTURE_ERROR, lodepng_error_text(error));
		}
		
		glGenTextures(1, &id);
		err = glGetError();
		glBindTexture(GL_TEXTURE_2D, id);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);




		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA,
			width, height,
			0,
			GL_RGBA, GL_UNSIGNED_BYTE, &pixelData[0]
			);


		if (glGetError() != GL_NO_ERROR)
		{
			throw spl::SPLException(spl::ErrorMessages::TEXTURE_ERROR);
		}
	}

}
