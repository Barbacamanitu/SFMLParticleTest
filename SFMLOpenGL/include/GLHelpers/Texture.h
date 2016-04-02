#pragma once
#include "GL/glew.h"
namespace spl 
{
	class Texture
	{
	public:
		Texture(char* imgData, size_t width, size_t height);
		~Texture();
		GLint Id() const { return id; }
	private:
		GLuint id;


	};
}

