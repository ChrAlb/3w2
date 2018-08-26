#pragma once

#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


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
	bool IsFocused();

	void ToggleFullscreen();
	void Close();

	sf::RenderWindow* GetRenderWindow();
	
	sf::Vector2u GetWindowSize();
	

private:
	void Setup(const std::string& title, const sf::Vector2u& size);
	void Create();

	sf::RenderWindow m_window;
	
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;
	bool m_isFocused;
};