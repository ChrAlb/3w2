#pragma once
#include "Window.h"

#include <iostream>

class Game{
public:
	Game();
	~Game();

	void Update();
	void Render();
	void LateUpdate();

	sf::Time GetElapsed();

	Window* GetWindow();
private:
	void RestartClock();

	sf::Clock m_clock;
	sf::Time m_elapsed;
	
	Window m_window;
	
};