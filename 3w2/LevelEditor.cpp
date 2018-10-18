#include "stdafx.h"
#include "LevelEditor.h"
#include "StateManager.h"
#include <sstream>
#include <fstream>
#include "LevelManager.h"
#include <iostream>


LevelEditor::LevelEditor(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

LevelEditor::~LevelEditor()  {}

void LevelEditor::OnCreate()
{
	sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();

	m_introTexture.load(Textures::TitleScreen, "graphics/Title.png");
	m_introBild.setTexture(m_introTexture.get(Textures::TitleScreen));

	m_TileView.reset(sf::FloatRect(0,0,300, VideoMode::getDesktopMode().height));
	m_DesignView.reset(sf::FloatRect(-300,0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
	m_LevelView.reset(sf::FloatRect(0, 0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));

	m_TileSheet.load(Textures::Test, "graphics/tiles_sheet.png");

	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::LevelEditor, "Finish_LevelEditor", &LevelEditor::Continue, this);

	LevelEditor::read_Tileset();
}

void LevelEditor::OnDestroy()
{
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::LevelEditor, "Finish_LevelEditor");
}

void LevelEditor::Activate()
{
	;
}

void LevelEditor::Deactivate()
{
	;
}


void LevelEditor::Continue(EventDetails* l_details) {
	m_stateMgr->SwitchTo(StateType::MainMenu);
	m_stateMgr->Remove(StateType::LevelEditor);
}

void LevelEditor::read_Tileset()
{
	m_TileArray.setPrimitiveType(Quads);
	m_TileArray.resize(m_LevelSize.x*m_LevelSize.y*VERTS_IN_QUAD);

	int currentVertex = 0;
	int verticalOffset = 0;

	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			m_TileArray[currentVertex + 0].position = Vector2f(x*TILE_SIZE, y* TILE_SIZE);
			m_TileArray[currentVertex + 1].position = Vector2f(x*TILE_SIZE + TILE_SIZE, y* TILE_SIZE);
			m_TileArray[currentVertex + 2].position = Vector2f(x*TILE_SIZE + TILE_SIZE, y* TILE_SIZE + TILE_SIZE);
			m_TileArray[currentVertex + 3].position = Vector2f(x*TILE_SIZE, y* TILE_SIZE + TILE_SIZE);
			
			verticalOffset = verticalOffset * TILE_SIZE;
			

			m_TileArray[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
			m_TileArray[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
			m_TileArray[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
			m_TileArray[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			currentVertex = currentVertex + VERTS_IN_QUAD;
			verticalOffset++;
		}
	}

	
	
		

}

void LevelEditor::Update(const sf::Time & l_time) {}

void LevelEditor::Draw()
{
	sf::RenderWindow* window = m_stateMgr->	GetContext()->m_wind->GetRenderWindow();
	window->clear(sf::Color::White);

	window->setView(m_DesignView);
	window->draw(m_introBild);

	window->setView(m_TileView);
	m_TileView.setViewport(sf::FloatRect(0, 0, 0.14, 1));
	
	
	window->draw(m_TileArray, &m_TileSheet.get(Textures::Test));
	


	window->setView(m_LevelView);
	m_LevelView.setViewport(sf::FloatRect(0.8f, 0, 0.2f, 0.2f));
	window->draw(m_introBild);

}
