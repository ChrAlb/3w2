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

	LevelEditor::set_const();
	
	m_TileView.reset(sf::FloatRect(0,0,400, VideoMode::getDesktopMode().height));
	m_DesignView.reset(sf::FloatRect(400,0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
	m_LevelView.reset(sf::FloatRect(400, 0,(m_LevelSize.y*TILE_SIZE) , (m_LevelSize.x*TILE_SIZE) ));
	m_LayerView.reset(sf::FloatRect(0, 0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));

	m_TileSheet.load(Textures::Tileset1, "graphics/tiles_sheet.png");
	m_DefaultTile.load(Textures::LevelEditorSet,"graphics/default_tile.png");
	
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::LevelEditor, "Finish_LevelEditor", &LevelEditor::Continue, this);
    evMgr->AddCallback(StateType::LevelEditor, "Mouse_Left", &LevelEditor::MouseClick, this);


	LevelEditor::read_Tileset();
	LevelEditor::create_initLevel();

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
	m_TileArray.resize(m_TileLevelSize.x*m_TileLevelSize.y*VERTS_IN_QUAD);

	int currentVertex = 0;
	int verticalOffset = 0;
	int verticalcounter = 0;
	
	
	for (int y = 0; y < m_TileLevelSize.y; y++)
	{
		for (int x = 0; x < m_TileLevelSize.x; x++)
		{		
			m_TileArray[currentVertex + 0].position = Vector2f(m_pos_TileArray.x+x*TILE_SIZE, m_pos_TileArray.y+y* TILE_SIZE);
			m_TileArray[currentVertex + 1].position = Vector2f(m_pos_TileArray.x +x*TILE_SIZE + TILE_SIZE, m_pos_TileArray.y +y* TILE_SIZE);
			m_TileArray[currentVertex + 2].position = Vector2f(m_pos_TileArray.x +x*TILE_SIZE + TILE_SIZE, m_pos_TileArray.y +y* TILE_SIZE + TILE_SIZE);
			m_TileArray[currentVertex + 3].position = Vector2f(m_pos_TileArray.x +x*TILE_SIZE, m_pos_TileArray.y +y* TILE_SIZE + TILE_SIZE);
			
			verticalOffset = verticalcounter * TILE_SIZE;
			

			m_TileArray[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
			m_TileArray[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
			m_TileArray[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
			m_TileArray[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			currentVertex = currentVertex + VERTS_IN_QUAD;
			verticalcounter++;
		}
		
	}

}

void LevelEditor::create_initLevel()
{

	m_LevelArray.setPrimitiveType(Quads);
	m_LevelArray.resize(m_LevelSize.x*m_LevelSize.y*VERTS_IN_QUAD);

	int currentVertex = 0;
	int verticalOffset = 0;
	int verticalcounter = 0;

	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			m_LevelArray[currentVertex + 0].position = Vector2f(m_pos_DesingArray.x+x*TILE_SIZE, y* TILE_SIZE);
			m_LevelArray[currentVertex + 1].position = Vector2f(m_pos_DesingArray.x +x*TILE_SIZE + TILE_SIZE, y* TILE_SIZE);
			m_LevelArray[currentVertex + 2].position = Vector2f(m_pos_DesingArray.x +x*TILE_SIZE + TILE_SIZE, y* TILE_SIZE + TILE_SIZE);
			m_LevelArray[currentVertex + 3].position = Vector2f(m_pos_DesingArray.x +x*TILE_SIZE, y* TILE_SIZE + TILE_SIZE);

			verticalOffset = 0;


			m_LevelArray[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
			m_LevelArray[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
			m_LevelArray[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
			m_LevelArray[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			currentVertex = currentVertex + VERTS_IN_QUAD;
			verticalcounter++;
		}
	}
}

void LevelEditor::set_const()
{
	m_TileLevelSize.x = 6;
	m_TileLevelSize.y = 5;
	
	m_LevelSize.x = 41;
	m_LevelSize.y = 21;

	m_pos_TileArray.x = 50 ;
	m_pos_TileArray.y = 400 ;

	m_pos_DesingArray.x = 400;
	m_pos_DesingArray.y = 0;

	TileFl�che = { m_pos_TileArray.x,m_pos_TileArray.y, m_TileLevelSize.x * TILE_SIZE,   m_TileLevelSize.y * TILE_SIZE };
	DesignFl�che = { m_pos_DesingArray.x, m_pos_DesingArray.y,m_LevelSize.x*TILE_SIZE, m_LevelSize.y*TILE_SIZE };

	m_inTileView = false;
	m_inDesignView = false;
}

bool LevelEditor::mouse_pos_in(FloatRect Fl�che, Vector2f pos)
{
	if ( 
		(pos.x > Fl�che.left) &&  (pos.x < Fl�che.left + Fl�che.width) &&
		(pos.y > Fl�che.top) && (pos.y < Fl�che.top + Fl�che.height)
	   )
		return true;
	else
		return false;
}

void LevelEditor::draw_mousepose_inTileView(FloatRect field)
{
	sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	window->setView(m_LayerView);
	sf::RectangleShape rectangle;
	rectangle.setPosition(field.left,field.top);
	rectangle.setSize(sf::Vector2f(field.width,field.height));
	rectangle.setOutlineThickness(3);
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setFillColor(sf::Color::Transparent);
	window->draw(rectangle);
}

FloatRect LevelEditor::calculateActualTile(Vector2f mouspos)
{
	FloatRect Tile;

	Tile.left = ((int) mouspos.x / TILE_SIZE) * TILE_SIZE;
	Tile.top = ((int) mouspos.y / TILE_SIZE ) * TILE_SIZE ;
	Tile.width = TILE_SIZE;
	Tile.height = TILE_SIZE;

	return Tile;
}

void LevelEditor::MouseClick(EventDetails * l_details)
{
	SharedContext* context = m_stateMgr->GetContext();
	sf::Vector2i mousePos = l_details->m_mouse;

	if (m_inTileView)
	{


	}

	if (m_inDesignView)
	{

	}

}

void LevelEditor::Update(const sf::Time & l_time) 

{
	mouseposition = static_cast <sf::Vector2f> (sf::Mouse::getPosition());
	//printf("%f\n", mouseposition.x);
	//printf("%f\n", mouseposition.y);
	if (mouse_pos_in(TileFl�che, mouseposition))
	{
		m_ActualTile = LevelEditor::calculateActualTile(mouseposition);
		m_inTileView = true;
    }
	else m_inTileView = false;
	
}

void LevelEditor::Draw()
{
	
	sf::RenderWindow* window = m_stateMgr->	GetContext()->m_wind->GetRenderWindow();
	window->clear(sf::Color::Yellow);

	window->setView(m_DesignView);
	m_DesignView.setViewport(sf::FloatRect(0.2, 0, 1, 1));
	window->draw(m_LevelArray, &m_DefaultTile.get(Textures::LevelEditorSet));
	
    
	window->setView(m_TileView);
	m_TileView.setViewport(sf::FloatRect(0, 0, 0.2, 1));
    window->draw(m_TileArray, &m_TileSheet.get(Textures::Tileset1));

	//window->setView(m_LevelView);
	//m_LevelView.setViewport(sf::FloatRect(0, 0, 0.2, 0.2));
	//window->draw(m_LevelArray, &m_DefaultTile.get(Textures::LevelEditorSet));
	
	if (m_inTileView)
	   LevelEditor::draw_mousepose_inTileView(m_ActualTile);
	
	
}
