#pragma once
#include "GL/glew.h"
#include <chrono>
#include <glm/glm.hpp>
#include <vector>
#include <random>
#include "SFML/Graphics/Texture.hpp"
class GLParticleSystem
{
	struct Particle
	{
		float x;
		float y;
	};

public:
	GLParticleSystem();
	~GLParticleSystem();
	void Draw(float alpha);
	void Initialize(size_t particleCount);
	void UpdateParticles(float delta, sf::Vector2i mousePos);

private:
	struct TimeStruct {
		std::chrono::high_resolution_clock::time_point currentTime;
		std::chrono::high_resolution_clock::time_point newTime;
		std::chrono::duration<double> elapsedTime;
	};

	TimeStruct mTimeStruct;
	std::vector<Particle> particles;
	void CreateMatrices();
	void GenerateBuffers();
	void CompileShaders();
	void DrawParticles();
	bool firstHit;
	glm::vec2 randomPosition();
	GLint err;
	GLuint particlePosition;
	GLuint particleVelocity;
	GLuint particleTexturePosition;
	GLuint mousePosLoc;
	GLint posAttrib;
	GLint velAttrib;
	//Shader Handlers
	GLuint renderProgram,computeProgram;
	size_t particleCount;
	std::default_random_engine eng;
	std::uniform_real_distribution<float> xdist;
	GLuint particleTexture;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	


};

