#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
//#include "TextureHolder.h"
#include <sstream>
#include <fstream>
#include "LevelManager.h"
#include <iostream>


using namespace sf;
using namespace  std;

LevelManager::LevelManager()
{
	m_GameName = "Default.gam";
	if (readin_game(&m_leveldata, m_GameName))
	{
		;
	}
}
 
LevelManager::~LevelManager()
{
}


int** LevelManager::nextLevel(VertexArray& rVaLevel, leveldate& m_leveldaten)
{
	

	m_LevelSize.x = 0;
	m_LevelSize.y = 0;

	
	
	if (m_CurrentLevel > m_NumofLevels)
	{
	LevelManager::set_allLeveldone(true);
	}

	
	
	
	if (m_CurrentLevel < m_NumofLevels)
	{
        m_leveldaten = m_levelinfo[m_CurrentLevel];
		m_CurrentLevel++;
	}
	    


	ifstream inputFile(m_leveldaten.LevelName);
	
	string s;

	while (getline(inputFile, s))
	{
		++m_LevelSize.y;
	}
	

	m_LevelSize.x = (s.length())/3;
	
	
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
	return m_leveldata.m_PlayerStartPosition; 
}

bool LevelManager::get_allLeveldone()
{
	return m_allLevel;
}

void LevelManager::set_allLeveldone(bool allLeveldone)
{
	m_allLevel = allLeveldone;
}

bool LevelManager::readin_game(leveldate *level, string filename)
{
	string row;
	string path;
	path = Utils::GetWorkingDirectory();
	path = path + "\\Games\\";
    std::fstream os(path +filename, std::ios::in);

	getline(os, row);
	m_NumofLevels = std::stoi(row); 

	for (int i = 0; i < m_NumofLevels; i++)

	{
		getline(os, row);
		level->BGFileName = row;

		getline(os, row);
		level->TilSetName = row;

		getline(os, row);
		level->LevelName = row;

		getline(os, row);
		level->m_bg_texture = parseRow(row);

		getline(os, row);
		level->m_tileset = parseRow(row);

		string delimiter = ",";
		
		size_t pos=0;
		getline(os, row);

		pos = row.find(delimiter);
        level->m_PlayerStartPosition.x = std::stoi(row.substr(0, pos));
		level->m_PlayerStartPosition.y = std::stoi(row.substr(pos + 1, std::string::npos));

	    pos = 0;
		getline(os, row);
		pos = row.find(delimiter);
		level->m_EnenemyStartPosition.x = std::stoi(row.substr(0, pos));
		level->m_EnenemyStartPosition.y = std::stoi(row.substr(pos + 1, std::string::npos));

		getline(os, row);
		
		m_levelinfo.push_back(*level);


	}

	
	return true;
}

Textures::ID LevelManager::parseRow(string row)
{
	if (row == "Textures::TitleScreen")
		return Textures::TitleScreen;
	if (row == "Textures::MenuBGScreen")
		return Textures::MenuBGScreen;
	if (row == "Textures::Player")
		return Textures::Player;
	if (row == "Textures::Enemy")
		return Textures::Enemy;
	if (row == "Textures::Level1Bg")
		return Textures::Level1Bg;
	if (row == "Textures::Level2Bg")
		return Textures::Level2Bg;
	if (row == "Textures::Tileset1")
		return Textures::Tileset1;
	if (row == "Textures::Tileset2")
		return Textures::Tileset2;
	if (row == "Textures::Tree")
		return Textures::Tree;
	if (row == "Textures::Bullet")
		return Textures::Bullet;
	if (row == "Textures::FinishLine")
		return Textures::FinishLine;
	if (row == "Textures::Hufeisen")
		return Textures::Hufeisen;
	if (row == "Textures::LevelEditorSet")
		return Textures::LevelEditorSet;

	
}
