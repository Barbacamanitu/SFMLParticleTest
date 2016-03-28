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

GLParticleSystem::GLParticleSystem()
{
	srand(time(0));
	std::uniform_real_distribution<float> xxDist(-1.0, 1.0);
	xdist = xxDist;


}


GLParticleSystem::~GLParticleSystem()
{
}

void GLParticleSystem::Initialize(size_t pCount)
{
	mTimeStruct.currentTime = std::chrono::high_resolution_clock::now();
	particleCount = pCount;
	float lifetime = 3.0f;
	glEnable(GL_TEXTURE_2D);


	//Generate matrices
	

	glm::vec4 *vertices = new glm::vec4[particleCount];
	for (int i = 0; i < particleCount; i++)
	{
		glm::vec2 pos = randomPosition() * 800.0f;
		glm::vec2 vel = randomPosition() * 0.0f;

		vertices[i] = glm::vec4(pos.x, pos.y,vel.x,vel.y);		
	
	}
	err = glGetError();

	size_t s = sizeof(glm::vec4) * particleCount;
	glGenBuffers(1, &particlePosition);
	err = glGetError();

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, particlePosition);
	glBufferData(GL_SHADER_STORAGE_BUFFER,s, vertices, GL_STATIC_DRAW);
	
	delete vertices;
	CompileShaders();
	err = glGetError();

	glUseProgram(renderProgram);

	

	GLint uniTrans = glGetUniformLocation(renderProgram, "projMatrix");
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	err = glGetError();
	int aa = 1;

	//Matricies
	CreateMatrices();
}

void GLParticleSystem::Draw(float delta)
{

	glUseProgram(renderProgram);
	glBindBuffer(GL_ARRAY_BUFFER,particlePosition);
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
	glDisableVertexAttribArray(velAttrib);
	

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

	
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(computeProgram);


	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particlePosition);
	//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, particleVelocity);
	glUniform1f(glGetUniformLocation(computeProgram, "deltaTime"), delta);
	glm::vec2 mousePoss;
	mousePoss.x = mouseX;
	mousePoss.y = mouseY;
	glUniform2fv(mousePosLoc, 1, glm::value_ptr(mousePoss));


	glDispatchCompute(256, 10, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);


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
	projectionMatrix = glm::ortho(windowMin.x, windowMax.x, windowMin.y, windowMax.y, 10.f, -100.f);
	viewMatrix = glm::lookAt(
		glm::vec3(cameraPosition.x, cameraPosition.y, 4.f),
		glm::vec3(cameraPosition.x, cameraPosition.y, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 modelMatrix;
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

int GLParticleSystem::CreateTexture(char* imgData, int width, int height)
{
	glGenTextures(1, &particleTexture);
	glBindTexture(GL_TEXTURE_2D, particleTexture);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);




	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA,
		width, height,
		0,
		GL_RGBA, GL_UNSIGNED_BYTE, imgData
		);
	particleTexturePosition = glGetUniformLocation(renderProgram, "tex0");
	glUniform1i(renderProgram, particleTexturePosition);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, particleTexture);
	return glGetError();
}
