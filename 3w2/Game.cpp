#include "stdafx.h"
#include "Game.h"

Game::Game(): m_window("3w2", sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)), m_stateManager(&m_context)
	
{
	m_clock.restart();
	srand(time(nullptr));

	m_context.m_wind = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	
	m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game(){}

sf::Time Game::GetElapsed(){ return m_clock.getElapsedTime(); }

void Game::RestartClock(){ m_elapsed = m_clock.restart(); }

Wind* Game::GetWindow(){ return &m_window; }

/*
void Game::HandleInput()
{
}
*/

void Game::Update()
{
	m_window.Update();
	m_stateManager.Update(m_elapsed);
}

void Game::Render(){
	m_window.BeginDraw();
	m_stateManager.Draw();
	m_window.EndDraw();
}

void Game::LateUpdate(){
	
	m_stateManager.ProcessRequests();
	RestartClock();
}