#include "stdafx.h"
#include "Window.h"

Wind::Wind(){ 
	Setup("3w2", sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
}

Wind::Wind(const std::string& title, const sf::Vector2u& size){ 
	Setup(title,size);
}

Wind::~Wind(){ m_window.close(); }

void Wind::Setup(const std::string& title, const sf::Vector2u& size){
	m_windowTitle = title;
	m_windowSize = size;
	m_isFullscreen = false;
	m_isDone = false;
	m_isFocused = true;

	Create();
}

void Wind::Create(){
	sf::Uint32 style = sf::Style::Default;
	if(m_isFullscreen){ style = sf::Style::Fullscreen; }

	m_window.create(sf::VideoMode(m_windowSize.x,m_windowSize.y,32),m_windowTitle,style);
}

void Wind::BeginDraw(){ m_window.clear(sf::Color::Black); }
void Wind::EndDraw(){ m_window.display(); }

bool Wind::IsDone(){ return m_isDone; }
bool Wind::IsFullscreen(){ return m_isFullscreen; }
void Wind::Draw(sf::Drawable & l_drawable)
{
	m_window.draw(l_drawable);
}
bool Wind::IsFocused(){ return m_isFocused; }

sf::RenderWindow* Wind::GetRenderWindow(){ return &m_window; }

sf::Vector2u Wind::GetWindowSize(){ return m_windowSize; }


void Wind::ToggleFullscreen(){
	m_isFullscreen = !m_isFullscreen;
	m_window.close();
	Create();
}


void Wind::Update()
{
	sf::Event event;

	while (m_window.pollEvent(event))

	{
		if (event.type == sf::Event::Closed)

		{
			m_isDone = true;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
		{
			ToggleFullscreen();
		}

	}
}