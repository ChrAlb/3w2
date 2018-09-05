#pragma once
#include "Window.h"
#include "EventManager.h"
#include "StateManager.h"


#include <iostream>

class Game {
public:
	Game();
	~Game();

	void Update();
	void Render();
	void LateUpdate();

	sf::Time GetElapsed();

	Wind* GetWindow();
private:
	void RestartClock();

	sf::Clock m_clock;
	sf::Time m_elapsed;
	SharedContext m_context;
	Wind m_window;
	
	StateManager m_stateManager;
};