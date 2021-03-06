#include "stdafx.h"
#include "Window.h"

Wind::Wind(){ 
	Setup("3w2", sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
}

Wind::Wind(const std::string& title, const sf::Vector2u& size){ 
	Setup(title,size);
}

Wind::~Wind(){ m_window.close(); }

void Wind::Setup(const std::string& title, const sf::Vector2u& size)
{
	m_windowTitle = title;
	m_windowSize = size;
	m_isFullscreen = false;
	m_isDone = false;
	m_isFocused = true;

	m_eventManager.AddCallback(StateType(0), "Fullscreen_toggle", &Wind::ToggleFullscreen, this);
	m_eventManager.AddCallback(StateType(0), "Window_close", &Wind::Close, this);
	//m_eventManager.AddCallback(StateType(0), "Key_Escape" , &Wind::Close, this);

	Create();
}

void Wind::Destroy()
{
	m_window.close();
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

EventManager * Wind::GetEventManager()
{
	 return &m_eventManager; 
}


void Wind::Draw(sf::Drawable & l_drawable)
{
	m_window.draw(l_drawable);
}

bool Wind::IsFocused(){ return m_isFocused; }

void Wind::Close(EventDetails * l_details)
{
	m_isDone = true;
}

sf::RenderWindow* Wind::GetRenderWindow(){ return &m_window; }

sf::Vector2u Wind::GetWindowSize(){ return m_windowSize; }


void Wind::ToggleFullscreen(EventDetails* l_details)
{
	m_isFullscreen = !m_isFullscreen;
	m_window.close();
	Create();
}


void Wind::Update()
{
	sf::Event event;

	while (m_window.pollEvent(event))

	{
		if (event.type == sf::Event::LostFocus  )

		{
			m_isFocused = false;
			m_eventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			m_isFocused = true;
			m_eventManager.SetFocus(true);
		}
		m_eventManager.HandleEvent(event);
	}
	m_eventManager.Update();
}