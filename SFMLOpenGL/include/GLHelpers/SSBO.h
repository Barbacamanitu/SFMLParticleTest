#pragma once
#include "GL/glew.h"

//Simple wrapper for the SSBO buffer
//SSBO is what holds all of the particle data on the GPU
namespace spl
{
	class SSBO
	{
	public:
		SSBO();
		~SSBO();
		void GenerateBuffer(size_t totalSize, void* data);
		void Bind(GLint target);

		//Getters
		GLuint Id() const { return id; }
		GLuint UpdateVAO;
		GLuint RenderVAO;
	private:
		GLuint id;
		

	};
}

