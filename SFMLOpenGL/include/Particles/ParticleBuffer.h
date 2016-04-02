#pragma once
#include "GL/glew.h"
#include <string>
#include <map>
#include "GLHelpers/ShaderProgram.h"
#include "glm/detail/type_vec.hpp"
#include <random>

namespace spl
{
	class ParticleBuffer
	{
		
	public:
		enum BufferType
		{
			Update,
			Render
		};
		ParticleBuffer();
		~ParticleBuffer();
		void GenerateBuffer(size_t maximumParticles, spl::ShaderProgram &renderProgram);
		void ActivateVAO(BufferType bufferType);
		void DeactivateVAO();
		void BindBufferBase();
		GLuint updateVAO;
		GLuint renderVAO;

	private:
		void CreateUpdateVAO(void* data);
		void CreateRenderVAO(spl::ShaderProgram &renderProgram);
		glm::vec2 randomPosition();

		//VBO
		GLuint particleVBO;
		size_t bufferSize;

		std::default_random_engine eng;
		std::uniform_real_distribution<float> xdist;
	};
}

