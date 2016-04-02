#include "stdafx.h"
#include "Particles\GLParticleSystem.h"
#include <Particles\GLUtility.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>
#include <time.inl>
#include <random>
#include <assert.h>
#include <chrono>
#include "Particles/Particle.h"

GLParticleSystem::GLParticleSystem()
{
	


}


GLParticleSystem::~GLParticleSystem()
{
}

void GLParticleSystem::Initialize(size_t pCount)
{
	srand(time(0));
	std::uniform_real_distribution<float> xxDist(-1.0, 1.0);
	xdist = xxDist;
	mTimeStruct.currentTime = std::chrono::high_resolution_clock::now();
	particleCount = pCount;


	//Generate matrices
	

	glm::vec4 *vertices = new glm::vec4[particleCount];
	spl::Particle * particleArray = new spl::Particle[particleCount];
	for (int i = 0; i < particleCount; i++)
	{
		glm::vec2 pos = randomPosition() * 800.0f;
		glm::vec2 vel = randomPosition() * 0.0f;

		vertices[i] = glm::vec4(pos.x, pos.y,vel.x,vel.y);		
		particleArray[i].Position = pos;
	
	}

	



	//Generate VAO
	glGenVertexArrays(1, &computeVAO); // Create our Vertex Array Object  
	glBindVertexArray(computeVAO);

	size_t particleSize = sizeof(spl::Particle);
	size_t bufferSize = particleSize * particleCount;
	glGenBuffers(1, &particlePosition);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, particlePosition);
	glBufferData(GL_SHADER_STORAGE_BUFFER, bufferSize, particleArray, GL_STREAM_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particlePosition);
	glBindVertexArray(0); //End VAO1
	
	CompileShaders();

	glGenVertexArrays(1, &renderVAO);
	glBindVertexArray(renderVAO);
	glBindBuffer(GL_ARRAY_BUFFER, particlePosition);
	
	glEnableVertexAttribArray(velAttrib);
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(spl::Particle), 0);
	glVertexAttribPointer(velAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(spl::Particle), (void *) sizeof(glm::vec2));
	glBindVertexArray(0); //End VAO1


	delete vertices;
	
	err = glGetError();

	glUseProgram(renderProgram);

	

	
	err = glGetError();
	int aa = 1;

	//Matricies
	CreateMatrices();
}

void GLParticleSystem::Draw(float delta)
{

	err = glGetError();
	glUseProgram(renderProgram);
	glBindVertexArray(renderVAO);
	err = glGetError();
	
	//Texture stuff
	glBindTexture(GL_TEXTURE_2D, 1);
	err = glGetError();
	//Draw
	//glBlendFunc(GL_SOURCE0_ALPHA, GL_ONE);
	glDrawArrays(GL_POINTS, 0, particleCount);

	glBindVertexArray(0);
	glUseProgram(0);



}

void GLParticleSystem::GenerateBuffers()
{
	
}

void GLParticleSystem::CompileShaders()
{
	try
	{

		GLuint renderVS = GLUtility::createShaderFromFile("shaders\\render.vs");
		GLuint renderFS = GLUtility::createShaderFromFile("shaders\\render.fs");
		GLuint renderGS = GLUtility::createShaderFromFile("shaders\\render.gs");
		renderProgram = glCreateProgram();
		glAttachShader(renderProgram, renderVS);
		glAttachShader(renderProgram, renderFS);
		glAttachShader(renderProgram, renderGS);
		glLinkProgram(renderProgram);
		glUseProgram(renderProgram);
		velAttrib = glGetAttribLocation(renderProgram, "velocity");

		posAttrib = glGetAttribLocation(renderProgram, "position");




		GLuint computer = GLUtility::createShaderFromFile("shaders\\move.cm");
		computeProgram = glCreateProgram();
		glAttachShader(computeProgram, computer);
		glLinkProgram(computeProgram);
		GLint status;
		glGetProgramiv(computeProgram, GL_LINK_STATUS, &status);
		
		if (status != GL_TRUE)
		{
			char buffer[512];
			glGetProgramInfoLog(computeProgram, 512, NULL, buffer);
			int a = 1;
		}
		mousePosLoc = glGetUniformLocation(computeProgram, "mousePos");

	}
	catch (char* ex)
	{
		int a = 1;
	}
}

void GLParticleSystem::UpdateParticles(float delta, int mouseX, int mouseY)
{


	//glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(computeProgram);
	glBindVertexArray(computeVAO);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particlePosition);

	glm::vec2 mousePoss;
	mousePoss.x = mouseX;
	mousePoss.y = mouseY;
	glUniform1f(glGetUniformLocation(computeProgram, "deltaTime"), delta);
	glUniform2fv(mousePosLoc, 1, glm::value_ptr(mousePoss));


	glDispatchCompute(256, 10, 1);

	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	glBindVertexArray(0);
	glUseProgram(0);


	glUseProgram(2);
	glBindVertexArray(1);

	
	glUniform1f(glGetUniformLocation(2, "deltaTime"), delta);
	glUniform2fv(mousePosLoc, 1, glm::value_ptr(mousePoss));


	glDispatchCompute(256, 10, 1);

	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	glBindVertexArray(0);
	glUseProgram(0);


}

glm::vec2 GLParticleSystem::randomPosition()
{
	float x = xdist(eng);
	float y = xdist(eng);
	return glm::vec2(x, y);
}

void GLParticleSystem::CreateMatrices()
{
	glm::vec2 cameraPosition(-800.0f,-450.0f);
	glm::vec2 windowMax(1600.f, 900.0f);
	glm::vec2 windowMin(0.0f, 0.0f);
	projectionMatrix = glm::ortho(windowMin.x, windowMax.x, windowMin.y, windowMax.y, -.1f, 100.f);
	viewMatrix = glm::lookAt(
		glm::vec3(cameraPosition.x, cameraPosition.y, 4.f),
		glm::vec3(cameraPosition.x, cameraPosition.y, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	//Apply to the shader program
	glUseProgram(renderProgram);
	//Set up the uniforms
	GLuint modelViewMatLoc = glGetUniformLocation(renderProgram, "modelViewMatrix");
	GLuint projMatLoc = glGetUniformLocation(renderProgram, "projectionMatrix");
	err = glGetError();
	glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	
	err = glGetError();
	int aaa = 1;


}


