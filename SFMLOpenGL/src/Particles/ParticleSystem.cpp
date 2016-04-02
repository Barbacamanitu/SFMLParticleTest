#include "stdafx.h"
#include "Particles\ParticleSystem.h"
#include "Particles\Particle.h"
#include "GL\glew.h"
#include "GLHelpers\ShaderProgram.h"

namespace spl
{
	ParticleSystem::ParticleSystem()
	{
		xdist = std::uniform_real_distribution<float>(-1.0f, 1.0f);
	}


	ParticleSystem::~ParticleSystem()
	{
	}

	void ParticleSystem::Initialize(size_t maximumParticles)
	{
		maxParticles = maximumParticles;

		

		//Create Shader programs
		computeProgram = spl::ShaderProgram::CreateComputeProgram();
		renderProgram = spl::ShaderProgram::CreateRenderProgram();
		mvpMatrix.setOrthographicProjection(1600.0f, 900.0f, 1.0f, 100.0f);
		mvpMatrix.setCameraPosition(-800.0f, -450.f, 0.0f, -4.f);
	}


	void ParticleSystem::Draw(float delta)
	{
		/*renderProgram.makeActive();
		glBindBuffer(GL_ARRAY_BUFFER, particlePosition);
		glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(velAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void *) sizeof(glm::vec2));
		glEnableVertexAttribArray(velAttrib);

		//Texture stuff
		glBindTexture(GL_TEXTURE_2D, particleTexture);
		glUniform1i(renderProgram, particleTexturePosition);
		err = glGetError();
		//Draw
		//glBlendFunc(GL_SOURCE0_ALPHA, GL_ONE);
		glDrawArrays(GL_POINTS, 0, particleCount);
		err = glGetError();
		glDisableVertexAttribArray(posAttrib);
		glDisableVertexAttribArray(velAttrib);*/
	}



	

}