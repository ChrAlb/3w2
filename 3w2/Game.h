#pragma once
#include "Window.h"

#include <iostream>

class Game{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();
	void LateUpdate();

	sf::Time GetElapsed();

	Wind* GetWindow();
private:
	void RestartClock();

	sf::Clock m_clock;
	sf::Time m_elapsed;
	
	Wind m_window;

	sf::Texture bild;
	sf::Sprite sprite;

    sf::RenderWindow w;
	
};