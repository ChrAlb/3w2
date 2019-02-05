#pragma once

#include <SFML/Graphics.hpp>
#include "SharedContext.h"
#include "ResourceIdentifiers.h"
#include <vector>

using namespace sf;
using namespace std;

struct leveldate
{
	string BGFileName;
	string TilSetName;
	string LevelName;
	
	string m_bg_texture;
	string m_tileset;

	Vector2f m_PlayerStartPosition;
	Vector2f m_EnenemyStartPosition;

    //int MaxInt;
};

 
class LevelManager
{
private:
	
	int m_NumofLevels;
	Vector2i m_LevelSize;
	
	float m_TimeModifier = 1;
	int m_CurrentLevel = 0;
	
	bool m_allLevel = false;
	
	leveldate m_leveldata;

	string m_GameName;

	vector<leveldate> m_levelinfo;
	
	
public:

	LevelManager();
	~LevelManager();
	
	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;
	
	float getTimeLimit();
    Vector2f getStartPosition();
	int** nextLevel(VertexArray& rVaLevel, leveldate& m_leveldaten);
	Vector2i getLevelSize();
	
	
	int getCurrentLevel();
	bool get_allLeveldone();
	void set_allLeveldone(bool allLeveldone);

	bool readin_game(leveldate *level, string filename);

	
	
};


