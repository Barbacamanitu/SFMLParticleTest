// SFMLTemplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Game.h"
int _tmain(int argc, _TCHAR* argv[])
{

	Game* game = new Game();
	game->createWindow();
	game->mainLoop();
	int a = 1;
	//std::cin >> a;
	return 0;
}

