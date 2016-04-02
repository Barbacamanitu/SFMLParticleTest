#pragma once
#include "GL/glew.h"
#include <string>
#include <map>

namespace spl
{
	class ParticleBuffer
	{
	public:
		ParticleBuffer();
		~ParticleBuffer();
		void GenerateBuffer(size_t maximumParticles);
	private:
		void CreateUpdateVAO(size_t bufferSize, void* data);
		void CreateRenderVAO(size_t bufferSize);
		GLuint updateVAO;
		GLuint renderVAO;
		//VBO
		GLuint particleVBO;
		std::map<std::string, GLint> particleAttributes;
	};
}

