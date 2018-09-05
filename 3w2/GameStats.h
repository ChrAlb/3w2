#pragma once

#include <SFML\Graphics.hpp>
#include "Player.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"


class GameStats

{
public:
	GameStats();
	void print(sf::RenderWindow& windowRef, Player& RefPlayer);

	void addpointfordeadeney();

	void subtractlive();

	void print_lives(int lives, sf::RenderWindow& windowRef);

	bool nomorelives();
	

private:

	const int m_pointsperdeathenemy = 50;
	int m_lives;
	int m_points;


	FontHolder m_fonts;
	TextureHolder m_Textures;
	Sprite m_hufeisen;

	sf::Text m_Title;
	sf::Text m_Points;
	sf::Text m_Lives;
	
	sf::Font m_font;
	String string;

	std::string Convert(float number);


};

