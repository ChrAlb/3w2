#include "stdafx.h"
#include "LevelEditor.h"
#include "StateManager.h"


LevelEditor::LevelEditor(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

LevelEditor::~LevelEditor()  {}

void LevelEditor::OnCreate()
{
	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();

	m_introTexture.load(Textures::TitleScreen, "graphics/Title.png");
}

void LevelEditor::OnDestroy()
{
	;
}

void LevelEditor::Activate()
{
	;
}

void LevelEditor::Deactivate()
{
	;
}

void LevelEditor::Update(const sf::Time & l_time) {}

void LevelEditor::Draw()
{
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();
	m_introBild.setTexture(m_introTexture.get(Textures::TitleScreen));
	window->draw(m_introBild);
}
