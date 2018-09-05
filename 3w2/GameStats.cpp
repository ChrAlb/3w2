#include "stdafx.h"
#include "GameStats.h"
#include <iostream>
#include <sstream>

GameStats::GameStats()
{
	m_fonts.load(Fonts::ComicS, "graphics/Comics.ttf");
	m_Textures.load(Textures::Hufeisen, "graphics/Hufeisen.png");
	
	m_lives = 3;
	m_points = 0;
}
 
void GameStats::print(sf::RenderWindow & windowRef, Player& PlayerRef)
{
	// Titel
	/*
	m_Title.setFont(m_fonts.get(Fonts::ComicS));
	m_Title.setCharacterSize(16);
	m_Title.setPosition(0, 0);
	m_Title.setFillColor(sf::Color::Black);
	m_Title.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_Title.setString("Spielstand:");
   */

	// Player Points
	m_Points.setFont(m_fonts.get(Fonts::ComicS));
	m_Points.setCharacterSize(22);
	m_Points.setFillColor(sf::Color::Black);
	m_Points.setPosition(0, 60);
	
	string = "";
	string = string + Convert(m_points);
	m_Points.setString(string);

	// Player Lives
	/*
	m_Lives.setFont(m_fonts.get(Fonts::ComicS));
	m_Lives.setCharacterSize(14);
	m_Lives.setFillColor(sf::Color::Black);
	m_Lives.setPosition(0, 50);
	
	//string = "";
	//string = string + Convert(m_lives);
	//m_Lives.setString(string);
	*/

	windowRef.draw(m_Title);
	windowRef.draw(m_Points);
	windowRef.draw(m_Lives);
	print_lives(m_lives,windowRef);
	

}

void GameStats::addpointfordeadeney()
{
	m_points = m_points + m_pointsperdeathenemy;
}

void GameStats::subtractlive()
{
	m_lives = m_lives - 1;
}

void GameStats::print_lives(int lives, sf::RenderWindow& windowRef)
{

	m_hufeisen.setTexture(m_Textures.get(Textures::Hufeisen));

	for (int i = 0; i < lives; i++)
	{
		m_hufeisen.setPosition(Vector2f(i*45,0));
		windowRef.draw(m_hufeisen);
	}
	
}

bool GameStats::nomorelives()
{
	if (m_lives <= 0)
		return true;
	else
		return false;
}



std::string GameStats::Convert(float number)
{

	std::ostringstream buff;
	buff << number;
	return buff.str();

}

