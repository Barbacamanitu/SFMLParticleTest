#include "stdafx.h"
#include "Particles\ParticleSystem.h"
#include "Particles\Particle.h"
#include "GL\glew.h"
#include "GLHelpers\ShaderProgram.h"
#include "glm\gtc\type_ptr.inl"
#include "glm\gtc\matrix_transform.inl"
#include "GLHelpers\TextureManager.h"

namespace spl
{
	ParticleSystem::ParticleSystem()
	{
		xdist = std::uniform_real_distribution<float>(-1.0f, 1.0f);
		obstacles = new float[4];
	}

	

	ParticleSystem::~ParticleSystem()
	{
	}

	void ParticleSystem::Initialize(size_t maximumParticles, bool isPoints)
	{
		maxParticles = maximumParticles;

		glEnable(GL_PROGRAM_POINT_SIZE);

		//Create Shader programs
		computeProgram = spl::ShaderProgram::CreateComputeProgram();
		if (isPoints)
		{
			renderProgram = spl::ShaderProgram::CreateRenderProgramPoints();
		}
		else
		{
			renderProgram = spl::ShaderProgram::CreateRenderProgram();
		}
		renderProgram.addAttribute("position", 0, sizeof(glm::vec2), 2);
		renderProgram.addAttribute("velocity", 2, sizeof(glm::vec2), 2);

		mvpMatrix.setOrthographicProjection(1600.0f, 900.0f, 1.0f, 100.0f);
		mvpMatrix.setCameraPosition(-800.0f, -450.f, 0.0f, -4.f);

		particleBuffer.GenerateBuffer(maximumParticles,renderProgram);

		GLuint modelViewMatLoc = glGetUniformLocation(renderProgram.Id(), "modelViewMatrix");
		GLuint projMatLoc = glGetUniformLocation(renderProgram.Id(), "projectionMatrix");
		CreateMatrices();
	}


	void ParticleSystem::Draw(float delta,float particleSize)
	{
		renderProgram.makeActive();
		particleBuffer.ActivateVAO(ParticleBuffer::Render);
		//Texture stuff
		glBindTexture(GL_TEXTURE_2D, spl::TextureManager::getInstance().lookupTexture("test")->Id());
		glUniform1f(glGetUniformLocation(renderProgram.Id(), "particleSize"), particleSize);


		//Draw
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
		glDrawArrays(GL_POINTS, 0, maxParticles);
		particleBuffer.DeactivateVAO();
	}



	void ParticleSystem::CreateMatrices()
	{
		glm::vec2 cameraPosition(-800.0f, -450.0f);
		glm::vec2 windowMax(1600.f, 900.0f);
		glm::vec2 windowMin(0.0f, 0.0f);
		glm::mat4 projectionMatrix = glm::ortho(windowMin.x, windowMax.x, windowMin.y, windowMax.y, -.1f, 100.f);
		glm::mat4 viewMatrix = glm::lookAt(
			glm::vec3(cameraPosition.x, cameraPosition.y, 4.f),
			glm::vec3(cameraPosition.x, cameraPosition.y, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));

		//Apply to the shader program
		glUseProgram(renderProgram.Id());
		//Set up the uniforms
		GLuint modelViewMatLoc = glGetUniformLocation(renderProgram.Id(), "modelViewMatrix");
		GLuint projMatLoc = glGetUniformLocation(renderProgram.Id(), "projectionMatrix");
		err = glGetError();
		glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		err = glGetError();
		int a = 1;
	}

	void ParticleSystem::Update(float delta, float mouseX, float mouseY, float mouseForce)
	{
		obstacles[0] = mouseX;
		obstacles[1] = mouseY;
		
		obstacles[2] = mouseXX;
		obstacles[3] = mouseYY;

		mouseXX = mouseX;
		mouseYY = mouseY;
		glClear(GL_COLOR_BUFFER_BIT);
		computeProgram.makeActive();
		particleBuffer.ActivateVAO(ParticleBuffer::Update);
		particleBuffer.BindBufferBase();

		glm::vec2 mousePoss;
		mousePoss.x = mouseX;
		mousePoss.y = mouseY;
		err = glGetError();
		glUniform1f(glGetUniformLocation(computeProgram.Id(), "deltaTime"), delta);

		glUniform1f(glGetUniformLocation(computeProgram.Id(), "mouseForce"), mouseForce);
		glUniform2fv(glGetUniformLocation(computeProgram.Id(), "mousePos"), 1, glm::value_ptr(mousePoss));
		glUniform4fv(glGetUniformLocation(computeProgram.Id(), "obstacles"), 1, obstacles);
		err = glGetError();

		glDispatchCompute(256, 10, 1);

		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
		particleBuffer.DeactivateVAO();

	}





	

}