#include "stdafx.h"
#include "GLHelpers\Texture.h"
#include "ErrorHandling\SPLException.h"

namespace spl
{
	Texture::Texture(char* imgData, size_t width, size_t height)
	{
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA,
			width, height,
			0,
			GL_RGBA, GL_UNSIGNED_BYTE, imgData
			);

		if (glGetError() != GL_NO_ERROR)
		{
			throw spl::SPLException(spl::ErrorMessages::TEXTURE_ERROR);
		}

	}


	Texture::~Texture()
	{
	}
}
