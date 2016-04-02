#ifndef GAME_H
#define GAME_H


#include "Particles/GLParticleSystem.h"
#include "Particles/ParticleSystem.h"
#include <SFML/Graphics.hpp>


class Game
{
    public:
        Game();
        virtual ~Game();

        void createWindow();
        void mainLoop();
        void update(const float dt);
        void render(const float dt);
    protected:
    private:
		sf::CircleShape * circ;
		sf::RenderWindow* gameWindow;
		sf::Font mainFont;
		sf::Text mainText;
		sf::Text helpText;
		
        void processEvents();
		void createParticleSystem(size_t count);
		int particlesToMake;

		int frameCount;
		int frameCountCache;

		std::chrono::high_resolution_clock::time_point renderCurrentTime;
		std::chrono::high_resolution_clock::time_point renderLastTime;
		spl::ParticleSystem * nParticles;
		sf::Image mTexture;
		bool isPoints;
		float particleSize;
		int mouseDelta;

};

#endif // GAME_H
