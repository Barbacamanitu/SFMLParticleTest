#pragma once
#include <vector>
#include "ParticleEmitter.h"
#include "GLHelpers/MVPMatrix.h"
#include <random>
#include "GLHelpers/ShaderProgram.h"
#include "ParticleBuffer.h"
namespace spl
{
	class ParticleSystem
	{
	public:
		ParticleSystem();
		~ParticleSystem();
		
		void Initialize(size_t maximumParticles, bool isPoints);
		void Draw(float delta, float particleSize);
		void Update(float delta, float mouseX, float mouseY, float mouseForce);
		glm::vec2 randomPosition()
		{
			float x = xdist(eng);
			float y = xdist(eng);
			return glm::vec2(x, y);
		}
		void UpdateParticleSize(int direction);

	private:
		float* obstacles;
		GLuint err;
		GLuint particleTexture;
		std::vector<ParticleEmitter> emitters;
		size_t maxParticles;

		//Buffers
		spl::ParticleBuffer particleBuffer;

		//Shader Programs
		ShaderProgram renderProgram;
		ShaderProgram computeProgram;

		MVPMatrix mvpMatrix;

		std::default_random_engine eng;
		std::uniform_real_distribution<float> xdist;

		void CreateMatrices();
		float noiseRot;
		float mouseXX;
		float mouseYY;

	};
}

