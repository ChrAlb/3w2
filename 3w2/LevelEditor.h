#pragma once
#include <SFML\Graphics.hpp>
#include "BaseState.h"

#include "EventManager.h"
#include "SharedContext.h"
#include "ResourceIdentifiers.h"
#include <string>

using namespace sf;

class LevelEditor : public BaseState
{
public:

	LevelEditor(StateManager* l_stateManager);
	~LevelEditor();
	
	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

	void Continue(EventDetails* l_details);

	void read_Tileset();
	void create_initLevel();

private:

	int m_NumberofFiles;
	
	Vector2i   m_LevelDimension;
	View       m_TileView;
	View       m_DesignView;
	View       m_LevelView;

	Vector2f  m_TileLevelSize = { 4,8 };
	Vector2f  m_LevelSize = {40,21 };

	int     VERTS_IN_QUAD = 4;
	int     TILE_SIZE = 50;

	String     m_tileFile;
	String     m_LevelFile;

	VertexArray  m_TileArray;
	VertexArray  m_LevelArray;

	TextureHolder m_TileSheet;
	TextureHolder m_DefaultTile;
	

	

};
