
#define  GLEW_STATIC
#include <GL\glew.h>
#include "Game.h"
#include <iostream>
#include <fstream>
#include "Particles/GLUtility.h"
#include <thread>
#include <chrono>
#include <sstream>
#include "GLHelpers/Shader.h"
#include "Particles/ParticleSystem.h"
#include "GLHelpers/TextureManager.h"
#include <algorithm>
#include "SFML/Graphics/Rect.hpp"

Game::Game()
{
    //ctors
	frameCountCache = 0;
	frameCount = 0;
	renderCurrentTime = std::chrono::high_resolution_clock::now();
	renderLastTime = renderCurrentTime;
	particleSize = 20.0f;
	mouseDelta = 0.0f;
	particlesToMake = 1000;
}

Game::~Game()
{
    //dtor


}

void Game::createWindow()
{
	

	glewInit();
	glewExperimental = GL_TRUE;

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 2;
	settings.attributeFlags = sf::ContextSettings::Default;

	sf::VideoMode dMode = sf::VideoMode::getDesktopMode();
	gameWindow = new sf::RenderWindow(dMode, "SFML window", sf::Style::Default, settings);
	//gameWindow->create(sf::VideoMode(1600, 900), "SFML window", sf::Style::Default, settings);
	gameWindow->setVerticalSyncEnabled(true);

	circ = new sf::CircleShape(10);
	circ->setFillColor(sf::Color::Red);
	circ->setOutlineColor(sf::Color::Green);
	circ->setPosition(sf::Vector2f(150, 150));
	circ->setRadius(25);
	
	spl::TextureManager::getInstance().addTexture(std::string("test"), std::string("textures\\particle.png"));

	GLuint vertexBuffer;
	GLenum err = glewInit();

	glGenBuffers(1, &vertexBuffer);
	GLint errr = glGetError();



	

	//Load font
	bool fontload = mainFont.loadFromFile("fonts\\digital-7.ttf");
	mainText.setFont(mainFont);
	mainText.setCharacterSize(18); // in pixels, not points!
	mainText.setColor(sf::Color(255, 100, 100));
	mainText.setString("Mouse Position:");
	mainText.setPosition(5.0, 5.0);

	helpText.setFont(mainFont);
	helpText.setCharacterSize(18); // in pixels, not points!
	helpText.setColor(sf::Color(255, 100, 100));
	std::stringstream ss;
	ss << "Controls: \n\n" <<
		"\n\nSpacebar: Create particles" <<
		"\n\nScroll wheel: Change particle size" <<
		"\n\nScroll wheel (click): Change particle type" <<
		"\n\nUp/Down arrows: Change number of particles to create" <<
		"\n\n(Tip: Hold Left shift while using arrow keys)" <<
		"\n\nMouse buttons: Attract or repel particles.";
	
	helpText.setString(ss.str());
	sf::FloatRect fr = helpText.getLocalBounds();
	helpText.setPosition(10.0f, (float)gameWindow->getSize().y - (fr.height * 1.5f));

	
	

	
}

void Game::mainLoop()
{





	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	mTexture.loadFromFile("sprites\\particle.png");
	double t = 0.0;
	const double dt = 1.0 / 60.f;
	std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
	double accumulator = 0.0;
	std::chrono::high_resolution_clock::time_point newTime;
	std::chrono::duration<double> frameTime;

	while (gameWindow->isOpen())
    {
		newTime = std::chrono::high_resolution_clock::now();
		frameTime = std::chrono::duration_cast<std::chrono::duration<double>>(newTime - currentTime);
		currentTime = newTime;
		accumulator += frameTime.count();

		while (accumulator >= dt)
		{
			update(dt);
			accumulator -= dt;
			t += dt;
		}
		processEvents();

		render(dt);
    }

	delete gameWindow;


}

void Game::render(const float dt)
{
	//Calculate frames drawn in the last second
	//Get elapsed time
	renderCurrentTime = std::chrono::high_resolution_clock::now();
	double elapsed = std::chrono::duration_cast<std::chrono::seconds>(renderCurrentTime - renderLastTime).count();
	if (elapsed >= 1.0)
	{
		renderLastTime = renderCurrentTime;
		frameCountCache = frameCount;
		frameCount = 0;
	}
	frameCount++;

	if (!gameWindow->isOpen())
	{
		return;
	}
	
	gameWindow->clear();
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	sf::RenderStates states;
	
	
	if (nParticles != nullptr)
	{
		nParticles->Draw(dt,particleSize);
	}



	
	GLUtility::ClearGLState();
	gameWindow->resetGLStates();
	
	//gameWindow->draw(*circ, states);
	gameWindow->draw(mainText, states);
	gameWindow->draw(helpText, states);
	gameWindow->display();
	
}





void Game::update(const float dt)
{
	float speed = 200.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		circ->move(speed * dt, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		circ->move(-speed * dt, 0.0f);
	}


	sf::Vector2i mPos = sf::Mouse::getPosition(*gameWindow);
	sf::Vector2i wSize = (sf::Vector2i)gameWindow->getSize();
	mPos = mPos - (wSize / 2);
	mPos.y *= -1;
	double frameTime = 1000.0 / double(frameCountCache);
	double fps = frameCountCache;
	std::stringstream ss;
	ss <<"Frame time (1 second average): " << frameTime <<
		"\n\nFPS: " << fps <<
		"\n\nNext particle count: " << particlesToMake <<
		"\n\nNext particle type: " << ((isPoints) ? "Points" : "Sprites") << 
		"\n\nParticle size: " << particleSize;
	mainText.setString(ss.str());
	float mouseForce = 0.0f;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mouseForce = 1.0f;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		mouseForce = -1.0f;
	}



	if (nParticles != nullptr)
	{
		nParticles->Update(dt, mPos.x, mPos.y,mouseForce);
	}
}



void Game::processEvents()
{
	
     sf::Event event;
        while (gameWindow->pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
            {
                gameWindow->close();
				//Cleanup all open gl
            }

			if (event.type == sf::Event::EventType::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle)
			{
				isPoints = !isPoints;
			}
			mouseDelta = 0;
			if (event.type == sf::Event::EventType::MouseWheelScrolled && mouseDelta == 0)
			{
				mouseDelta = glm::sign(event.mouseWheelScroll.delta);
				float amount = 1.0f;
				float maxx = 100.0f;
				particleSize += mouseDelta  * amount;
				particleSize = std::max(0.0f, std::min(particleSize, maxx));
				
				
			}

			if (event.type == sf::Event::EventType::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					gameWindow->close();
				}

				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
				{
					int amountToIncrease = 5000;
					if (event.key.code == sf::Keyboard::Down)
					{
						amountToIncrease *= -1;
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					{
						amountToIncrease *= 10;
					}

					particlesToMake += amountToIncrease;
					if (particlesToMake < 1000)
					{
						particlesToMake = 1000;
					}
				}

				if (event.key.code == sf::Keyboard::Space)
				{
					createParticleSystem(particlesToMake);
				}
			}




            if (event.type == sf::Event::EventType::MouseButtonPressed)
            {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
				}
            }
        }
}



void Game::createParticleSystem(size_t count)
{
	
	if (nParticles != nullptr)
	{
		delete nParticles;
	}


	nParticles = new spl::ParticleSystem();
	nParticles->Initialize(count,isPoints);
	//nParticles->CreateTexture((char*)mTexture.getPixelsPtr(), mTexture.getSize().x, mTexture.getSize().y);
}


