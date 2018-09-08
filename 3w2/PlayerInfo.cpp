#include "stdafx.h"
#include "PlayerInfo.h"
#include <iostream>
#include <sstream>

PlayerInfo::PlayerInfo()
{
	m_fonts.load(Fonts::Arial, "graphics/arial.ttf");
	
}

void PlayerInfo::print(sf::RenderWindow & windowRef, Player& PlayerRef)
{
	// Titel
	m_title.setFont(m_fonts.get(Fonts::Arial));
	m_title.setCharacterSize(16);
	m_title.setPosition(0, 0);
	m_title.setFillColor(sf::Color::Black);
	m_title.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_title.setString("Player Information");

	
    // Player Position
	m_pos.setFont(m_fonts.get(Fonts::Arial));
	m_pos.setCharacterSize(14);
	m_pos.setFillColor(sf::Color::Black);
	m_pos.setPosition(0, 25);
	PlayerRef.getPosition();
	string = "Top: ";
	string = string + Convert(PlayerRef.getPosition().top);
	string = string + "    Left:  ";
	string = string + Convert(PlayerRef.getPosition().left);
	m_pos.setString(string);


	// Count Jump Loops
	m_jumpFrames.setFont(m_fonts.get(Fonts::Arial));
	m_jumpFrames.setCharacterSize(14);
	m_jumpFrames.setFillColor(sf::Color::Black);
	m_jumpFrames.setPosition(0, 50);
	string = "#Frames while jumping: ";
    std::stringstream ss;
	ss << PlayerRef.m_countJumpLoops;
	string = string + ss.str();
	m_jumpFrames.setString(string);

	//onslope
	m_onslope.setFont(m_fonts.get(Fonts::Arial));
	m_onslope.setCharacterSize(14);
	m_onslope.setFillColor(sf::Color::Black);
	m_onslope.setPosition(0, 75);
	string = "OnSlope: ";
	if (PlayerRef.get_m_on_slope())
		string = string + "     TRUE";
	else
		string = string + "     FALSE";
	m_onslope.setString(string);

	//slopeend
	m_slopeend.setFont(m_fonts.get(Fonts::Arial));
	m_slopeend.setCharacterSize(14);
	m_slopeend.setFillColor(sf::Color::Black);
	m_slopeend.setPosition(0, 100);
	string = "SlopeEnd: ";
	if (PlayerRef.get_m_end_slope())
		string = string + "     TRUE";
	else
		string = string + "     FALSE";
	m_slopeend.setString(string);
	
	windowRef.draw(m_jumpFrames);
	windowRef.draw(m_title);
	windowRef.draw(m_pos);
	windowRef.draw(m_onslope);
	windowRef.draw(m_slopeend);

}

void PlayerInfo::printEnemy(sf::RenderWindow & windowRef, Enemy & RefPlayer)
{
	// Titel
	m_title.setFont(m_fonts.get(Fonts::Arial));
	m_title.setCharacterSize(16);
	m_title.setPosition(300, 0);
	m_title.setFillColor(sf::Color::Black);
	m_title.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_title.setString("Enemy Information");


	// Enemy Position
	m_pos.setFont(m_fonts.get(Fonts::Arial));
	m_pos.setCharacterSize(14);
	m_pos.setFillColor(sf::Color::Black);
	m_pos.setPosition(300, 25);
	RefPlayer.getPosition();
	string = "Top: ";
	string = string + Convert(RefPlayer.getPosition().top);
	string = string + "    Left:  ";
	string = string + Convert(RefPlayer.getPosition().left);

	
	m_pos.setString(string);

	windowRef.draw(m_title);
	windowRef.draw(m_pos);

}

std::string PlayerInfo::Convert(float number)
{
	
		std::ostringstream buff;
		buff << number;
		return buff.str();
	
}

