#pragma once
#include "Window.h"
#include "EventManager.h"
#include "StateManager.h"
//#include "GUI_Manager.h"
#include "FontManager.h"



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
	TextureManager m_textureManager;
	FontManager m_fontManager;
	GUI_Manager m_guiManager;
	StateManager m_stateManager;
	
	

};