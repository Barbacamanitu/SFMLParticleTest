#include "stdafx.h"
#include "Particles\ParticleBuffer.h"
#include "Particles\Particle.h"
#include "ErrorHandling\SPLException.h"


namespace spl
{
	ParticleBuffer::ParticleBuffer()
	{
		xdist = std::uniform_real_distribution<float>(-1.0f, 1.0f);
	}
	
	glm::vec2 ParticleBuffer::randomPosition()
	{
		float x = xdist(eng);
		float y = xdist(eng);
		return glm::vec2(x, y);
	}
	
	ParticleBuffer::~ParticleBuffer()
	{
	}



	void ParticleBuffer::ActivateVAO(BufferType bufferType)
	{
		GLuint bufferHandle;
		switch (bufferType)
		{
		case BufferType::Render:
			bufferHandle = renderVAO;
			break;
		case BufferType::Update:
			bufferHandle = updateVAO;
			break;
		}
		GLuint err = glGetError();
		glBindVertexArray(bufferHandle);
		err = glGetError();
	}
	void ParticleBuffer::DeactivateVAO()
	{
		glBindVertexArray(0);
	}

	void ParticleBuffer::BindBufferBase()
	{
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particleVBO);

	}



	void spl::ParticleBuffer::GenerateBuffer(size_t maximumParticles, spl::ShaderProgram &renderProgram)
	{
		//Create array of particles
		Particle * particleArray = new Particle[maximumParticles];
		for (int i = 0; i < maximumParticles; i++)
		{
			glm::vec2 pos = randomPosition();
			pos.x *= 700.0f;
			pos.y *= 400.0f;
				particleArray[i].Position = pos;
				particleArray[i].Velocity = glm::vec2(0.0f,0.0f);
		}
		bufferSize = sizeof(Particle)* maximumParticles;
	
		CreateUpdateVAO(particleArray);
		CreateRenderVAO(renderProgram);
		//Delete all particles in initial array
		delete[] particleArray;
	}
	
	void spl::ParticleBuffer::CreateUpdateVAO(void* data)
	{
		//Create VertexArrayObject
		glGenVertexArrays(1, &updateVAO);
		glBindVertexArray(updateVAO);
	
		glGenBuffers(1, &particleVBO);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, particleVBO);
		glBufferData(GL_SHADER_STORAGE_BUFFER, bufferSize, data, GL_STREAM_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particleVBO);

		glBindVertexArray(0); //End VAO



	
			
	
		if (glGetError() != GL_NO_ERROR)
		{
			throw(spl::SPLException(spl::ErrorMessages::SSBO_GENERATION_ERROR));
		}
	
	}
	
	void spl::ParticleBuffer::CreateRenderVAO(spl::ShaderProgram& renderProgram)
	{
		glGenVertexArrays(1, &renderVAO);
		glBindVertexArray(renderVAO);
		glBindBuffer(GL_ARRAY_BUFFER, particleVBO);
		
		//Add all attributes

		GLuint positionLoc = glGetAttribLocation(renderProgram.Id(),"position");
		GLuint velocityLoc = glGetAttribLocation(renderProgram.Id(),"velocity");
		glEnableVertexAttribArray(positionLoc);
		glEnableVertexAttribArray(velocityLoc);
		glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, sizeof(spl::Particle), (void*)0);
		glVertexAttribPointer(velocityLoc, 2, GL_FLOAT, GL_FALSE, sizeof(spl::Particle), (void*)sizeof(glm::vec2));

		GLint err = glGetError();
		glBindVertexArray(0); //End VAO1
	}
}
