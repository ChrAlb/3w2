#pragma once
#include <SFML\Graphics.hpp>
#include "BaseState.h"
#include "StateManager.h"
#include <string>

using namespace sf;

class LevelEditor : public BaseState
{
public:

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();


private:

	const int m_NumberofFiles;
	
	Vector2i   m_LevelDimension;
	View       m_TileView;
	View       m_DesignView;
	View       m_LevelViel;

	String     m_tileFile;
	String     m_LevelFile;

	VertexArray  m_TileArray;
	VertexArray  m_LevelArray;  

};
