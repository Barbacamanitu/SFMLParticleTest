#include "stdafx.h"
#include "Particles\ParticleBuffer.h"
#include "Particles\Particle.h"
#include "ErrorHandling\SPLException.h"


namespace spl
{
	ParticleBuffer::ParticleBuffer()
	{
	}
	
	
	ParticleBuffer::~ParticleBuffer()
	{
	}
	
	void spl::ParticleBuffer::GenerateBuffer(size_t maximumParticles)
	{
		//Create array of particles
		Particle * particleArray = new Particle[maximumParticles];
		size_t bufferSize = sizeof(Particle)* maximumParticles;
	
		CreateUpdateVAO(bufferSize, particleArray);
		//Delete all particles in initial array
		delete[] particleArray;
	}
	
	void spl::ParticleBuffer::CreateUpdateVAO(size_t bufferSize, void* data)
	{
		//Create VertexArrayObject
		glGenVertexArrays(1, &updateVAO);
		glBindVertexArray(updateVAO);
	
		glGenBuffers(1, &particleVBO);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, particleVBO);
		glBufferData(GL_SHADER_STORAGE_BUFFER, bufferSize, data, GL_STREAM_DRAW);
		glBindVertexArray(0); //End VAO
	
			
	
		if (glGetError() != GL_NO_ERROR)
		{
			throw(spl::SPLException(spl::ErrorMessages::SSBO_GENERATION_ERROR));
		}
	
	}
	
	void spl::ParticleBuffer::CreateRenderVAO(size_t bufferSize)
	{
		glGenVertexArrays(1, &renderVAO);
		glBindVertexArray(renderVAO);
		glBindBuffer(GL_ARRAY_BUFFER, particleVBO);
		glEnableVertexAttribArray(particleAttributes["position"]);
		glEnableVertexAttribArray(particleAttributes["velocity"]);
		glVertexAttribPointer(particleAttributes["position"], 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);
		glVertexAttribPointer(particleAttributes["velocity"], 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void *) sizeof(glm::vec2));
		GLint err = glGetError();
		glBindVertexArray(0); //End VAO1
	}
}
