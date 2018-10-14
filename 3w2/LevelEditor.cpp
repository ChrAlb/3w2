#include "stdafx.h"
#include "LevelEditor.h"
#include "StateManager.h"


LevelEditor::LevelEditor(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

LevelEditor::~LevelEditor()  {}

void LevelEditor::OnCreate()
{
	sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();

	m_TileView.reset(sf::FloatRect(0,0,100, VideoMode::getDesktopMode().height));
	m_DesignView.reset(sf::FloatRect(100,0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
	m_LevelView.reset(sf::FloatRect(0, 0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));

	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::LevelEditor, "Finish_LevelEditor", &LevelEditor::Continue, this);

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

void LevelEditor::Update(const sf::Time & l_time) {}

void LevelEditor::Draw()
{
	sf::RenderWindow* window = m_stateMgr->	GetContext()->m_wind->GetRenderWindow();
	window->clear(sf::Color::White);
	window->setView(m_TileView);
	window->clear(sf::Color::Blue);
	//window->draw();
}
