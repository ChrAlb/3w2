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

private:

	int m_NumberofFiles;
	
	Vector2i   m_LevelDimension;
	View       m_TileView;
	View       m_DesignView;
	View       m_LevelView;

	String     m_tileFile;
	String     m_LevelFile;

	VertexArray  m_TileArray;
	VertexArray  m_LevelArray;  

	TextureHolder m_introTexture;
	Sprite m_introBild;

};
