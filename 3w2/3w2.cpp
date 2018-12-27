// 3w2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"

int main()
{
	Game game;

	while (!game.GetWindow()->IsDone())
    {
		//game.HandleInput();
		game.Update();
		game.Render();
		game.LateUpdate();
	}
	return 0;
	
}


