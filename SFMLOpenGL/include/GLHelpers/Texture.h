#pragma once
#include "GL/glew.h"
#include <string>
namespace spl 
{
	class Texture
	{
	public:
		Texture(char* imgData, size_t width, size_t height);
		Texture(){};

		void createFromFile(std::string filename);
		~Texture();
		GLint Id() const { return id; }
	private:
		GLuint id;


	};
}

