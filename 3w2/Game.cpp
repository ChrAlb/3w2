#include "stdafx.h"
#include "Game.h"

Game::Game(): m_window("3w2", sf::Vector2u(800, 600))
	
{
	m_clock.restart();
	srand(time(nullptr));

	bild.loadFromFile("graphics/bg.png");
	sprite.setTexture(bild);
	
	//m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game(){}

sf::Time Game::GetElapsed(){ return m_clock.getElapsedTime(); }

void Game::RestartClock(){ m_elapsed = m_clock.restart(); }

Wind* Game::GetWindow(){ return &m_window; }


void Game::HandleInput()
{
}

void Game::Update()
{
	m_window.Update();
	
}

void Game::Render(){
	m_window.BeginDraw();
	w.draw(sprite);
	m_window.EndDraw();
}

void Game::LateUpdate(){
	
	RestartClock();
}