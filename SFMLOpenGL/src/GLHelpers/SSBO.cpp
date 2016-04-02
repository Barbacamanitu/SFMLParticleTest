#include "stdafx.h"
#include "GLHelpers\SSBO.h"
#include "ErrorHandling\SPLException.h"
#include <string>

namespace spl
{
	SSBO::SSBO()
	{

	}


	SSBO::~SSBO()
	{
	}

	void SSBO::GenerateBuffer(size_t totalSize, void* data)
	{
		
		glGenBuffers(1, &id);
		Bind(GL_SHADER_STORAGE_BUFFER);

		//Buffer is bound. Now upload the data
		glBufferData(GL_SHADER_STORAGE_BUFFER, totalSize, data, GL_STREAM_DRAW);

		if (glGetError() != GL_NO_ERROR)
		{
			throw(spl::SPLException(spl::ErrorMessages::SSBO_GENERATION_ERROR));
		}
	}

	void SSBO::Bind(GLint target)
	{
		//Binds buffer to target
		glBindBuffer(target, id);
	}

}