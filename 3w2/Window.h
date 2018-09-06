#pragma once

#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "EventManager.h"


class Wind

{
public:
	Wind();
	Wind(const std::string& title, const sf::Vector2u& size);
	~Wind();

	void BeginDraw();
	void EndDraw();

	void Update();

	bool IsDone();
	bool IsFullscreen();
	
	EventManager* GetEventManager() ;

	void Draw(sf::Drawable& l_drawable);
	
	bool IsFocused();

	void ToggleFullscreen(EventDetails* l_details);
	void Close(EventDetails* l_details);
	
	sf::RenderWindow* GetRenderWindow();
	
	sf::Vector2u GetWindowSize();
	

private:
	
	EventManager m_eventManager;
	bool m_isFocused;
	
	void Setup(const std::string& title, const sf::Vector2u& size);
	void Create();
	void Destroy();

	m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();
	
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;
	
};