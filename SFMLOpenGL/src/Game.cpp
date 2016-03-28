
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

Game::Game()
{
    //ctors
	frameCountCache = 0;
	frameCount = 0;
	renderCurrentTime = std::chrono::high_resolution_clock::now();
	renderLastTime = renderCurrentTime;
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
	

	GLuint vertexBuffer;
	GLenum err = glewInit();

	glGenBuffers(1, &vertexBuffer);
	GLint errr = glGetError();



	

	//Load font
	bool fontload = mainFont.loadFromFile("fonts\\digital-7.ttf");
	mainText.setFont(mainFont);
	mainText.setCharacterSize(24); // in pixels, not points!
	mainText.setColor(sf::Color(255, 100, 100));
	mainText.setString("Mouse Position:");
	mainText.setPosition(5.0, 5.0);

	spl::ShaderType typee;
	GLuint sha;
	try{
		spl::Shader newShader;
		sha = newShader.loadFromFile("shaders\\move.cs");
		typee = newShader.GetType();
		
	}
	catch (std::exception& ex)
	{
		std::string t(ex.what());
		int a = 1;
	}
	int b = 1;

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

	if (particles != nullptr)
	{
		particles->Draw(dt);
	}

	
	GLUtility::ClearGLState();
	gameWindow->resetGLStates();
	
	gameWindow->draw(*circ, states);
	gameWindow->draw(mainText, states);
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
	ss << "Mouse Position:  X: " << mPos.x << "  Y: " << mPos.y <<
		"\n\nFrame time (1 second average): " << frameTime <<
		"\n\nFPS: " << fps <<
		"\n\nParticles to create: " << particlesToMake;
	mainText.setString(ss.str());

	if (particles != nullptr)
	{
		particles->UpdateParticles(dt,mPos.x,mPos.y);
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

void Game::renderParticle()
{

}

void Game::createParticleSystem(size_t count)
{
	if (particles != nullptr)
	{
		delete particles;
	}

	particles = new GLParticleSystem();
	particles->Initialize(count);
	particles->CreateTexture((char*)mTexture.getPixelsPtr(), mTexture.getSize().x, mTexture.getSize().y);
}
