#pragma once
#include <vector>
#include "ParticleEmitter.h"
#include "GLHelpers/SSBO.h"
#include "GLHelpers/MVPMatrix.h"
#include <random>
#include "GLHelpers/ShaderProgram.h"
namespace spl
{
	class ParticleSystem
	{
	public:
		ParticleSystem();
		~ParticleSystem();
		
		void Initialize(size_t maximumParticles);
		void Draw(float delta);
		glm::vec2 randomPosition()
		{
			float x = xdist(eng);
			float y = xdist(eng);
			return glm::vec2(x, y);
		}
	private:
		

		std::vector<ParticleEmitter> emitters;
		size_t maxParticles;

		//Buffers
		spl::SSBO particleSSBO;

		//Shader Programs
		ShaderProgram renderProgram;
		ShaderProgram computeProgram;

		MVPMatrix mvpMatrix;

		std::default_random_engine eng;
		std::uniform_real_distribution<float> xdist;
		
	};
}

