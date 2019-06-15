#include "stdafx.h"
#include "game.h"
#include "State_Game.h"
#include <iostream>


void State_Game::loadLevel()

{
	 
	m_Playing = false;
	


// Delete alle Objekte und ArrayLevel

	for (iter = objects.begin(); iter != objects.end();)
	{
		delete (*iter);
		iter = objects.erase(iter);
		
	}
	

	
	for (int i = 0; i < m_LM.getLevelSize().y; ++i)
	{
		delete[] m_ArrayLevel[i];
	}
	delete[] m_ArrayLevel;
// EndDelete


	m_ArrayLevel = m_LM.nextLevel(m_VALevel, m_leveldaten);

	
	

    player = new Player();
    player->spawn(m_LM.getStartPosition(), GRAVITY); 
	

	int maxlevelsize = (m_LM.getLevelSize().x * TILE_SIZE) - TILE_SIZE;

	
	player->set_maxlevelsize(maxlevelsize);
	objects.push_back(player);

	
	for (int i = 0; i < m_leveldaten.m_NumofEnemies; i++)
	{
		if (m_leveldaten.enemydat[i].enemytype == first_enemy)
		{
          enemy = new Enemy();
		  enemy->spawn(m_leveldaten.enemydat[i].enemypos, GRAVITY);
          enemy->set_maxlevelsize(maxlevelsize);
	      objects.push_back(enemy);
		}
	}
	
	this->PlInfo.reset(sf::FloatRect(0, 0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
	this->bgview.reset(sf::FloatRect(0, 0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
	this->gameview.reset(sf::FloatRect(0, 0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));


	m_newlevelrequiered = false;

}