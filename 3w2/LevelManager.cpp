#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
//#include "TextureHolder.h"
#include <sstream>
#include <fstream>
#include "LevelManager.h"
#include <iostream>


using namespace sf;
using namespace std;

int** LevelManager::nextLevel(VertexArray& rVaLevel, leveldate& m_leveldaten)
{
	

	m_LevelSize.x = 0;
	m_LevelSize.y = 0;

	m_CurrentLevel++;
	
	if (m_CurrentLevel > NUM_LEVELS)
	{
	LevelManager::set_allLeveldone(true);
	}

	string levelToLoad;
	
	switch (m_CurrentLevel)
	{
	case 1:
		m_leveldata.LevelName = "levels/level1.txt";
		m_leveldata.BGFileName = "graphics/bg.png";
		m_leveldata.TilSetName = "graphics/tiles_sheet.png";
		m_leveldata.m_bg_texture = Textures::Level1Bg;
		m_leveldata.m_tileset = Textures::Tileset1;
			
		levelToLoad = m_leveldata.LevelName;
        m_StartPosition.x = 350;
		m_StartPosition.y = 750;
		// Korrektur Kommas aus level.txt
		m_leveldata.MaxInt = 47;
		
		break;
	
	case 2:
		m_leveldata.LevelName = "levels/level2.txt";
		m_leveldata.BGFileName = "graphics/bg2.png";
		m_leveldata.TilSetName = "graphics/tiles_sheet.png";
		m_leveldata.m_bg_texture = Textures::Level2Bg;
		m_leveldata.m_tileset = Textures::Tileset2;

		levelToLoad = m_leveldata.LevelName;
		m_StartPosition.x = 150;
		m_StartPosition.y = 750;
		m_leveldata.MaxInt = 45;
		
		break;
		
	}
	
	m_leveldaten = m_leveldata;

	ifstream inputFile(levelToLoad);
	string s;

	while (getline(inputFile, s))
	{
		++m_LevelSize.y;
	}
	
	m_LevelSize.x = m_leveldata.MaxInt;
	
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	int** arrayLevel = new int*[m_LevelSize.y];
	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		arrayLevel[i] = new int[m_LevelSize.x];
	}
	
	string row;
	int y = 0;
	std::string delimiter = ",";
	

	while (inputFile >> row)
	{
		int x = 0;
		std::string token;
		size_t pos = 0;
			
			while ((pos = row.find(delimiter)) != std::string::npos)
			{
				token = row.substr(0, pos);
				arrayLevel[y][x] = std::stoi(token);
				row.erase(0, pos + delimiter.length());
				x++;
			}
		
		y++;
	}
	
	

	inputFile.close();

	rVaLevel.setPrimitiveType(Quads);
	rVaLevel.resize(m_LevelSize.x*m_LevelSize.y*VERTS_IN_QUAD);

	int currentVertex = 0;

	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			rVaLevel[currentVertex + 0].position = Vector2f(x*TILE_SIZE, y* TILE_SIZE);
			rVaLevel[currentVertex + 1].position = Vector2f(x*TILE_SIZE+TILE_SIZE, y* TILE_SIZE);
			rVaLevel[currentVertex + 2].position = Vector2f(x*TILE_SIZE+TILE_SIZE, y* TILE_SIZE+TILE_SIZE);
			rVaLevel[currentVertex + 3].position = Vector2f(x*TILE_SIZE, y* TILE_SIZE+TILE_SIZE);

			int verticalOffset = arrayLevel[y][x] * TILE_SIZE;
 
			rVaLevel[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
			rVaLevel[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
			rVaLevel[currentVertex + 2].texCoords = Vector2f(TILE_SIZE,TILE_SIZE + verticalOffset);
			rVaLevel[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}
	return arrayLevel;
}

Vector2i LevelManager::getLevelSize()
{
	return m_LevelSize;


}

int LevelManager::getCurrentLevel()
{
	return m_CurrentLevel;
}

float LevelManager::getTimeLimit()
{
	return 0;
}

Vector2f LevelManager::getStartPosition()
{
	return m_StartPosition;
}

bool LevelManager::get_allLeveldone()
{
	return m_allLevel;
}

void LevelManager::set_allLeveldone(bool allLeveldone)
{
	m_allLevel = allLeveldone;
}

