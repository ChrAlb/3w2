#include "stdafx.h"
#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager* l_stateManager)
	: BaseState(l_stateManager){}

State_MainMenu::~State_MainMenu(){}


void State_MainMenu::OnCreate() {
	GUI_Manager* gui = m_stateMgr->GetContext()->m_guiManager;
	gui->LoadInterface(StateType::MainMenu, "Test.interface", "MainMenu");
	gui->GetInterface(StateType::MainMenu, "MainMenu")->SetPosition(sf::Vector2f(250.f, 168.f));
	EventManager* eMgr = m_stateMgr->GetContext()->m_eventManager;
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_Play", &State_MainMenu::Play, this);
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_Quit", &State_MainMenu::Quit, this);
}

void State_MainMenu::OnDestroy(){
	EventManager* evMgr = m_stateMgr->
		GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::MainMenu, "Mouse_Left");
}

void State_MainMenu::Activate(){
	if (m_stateMgr->HasState(StateType::Game)
		&& m_labels[0].getString() != "RESUME")
	{
		m_labels[0].setString(sf::String("RESUME"));
	} else {
		m_labels[0].setString(sf::String("Hi chasch spilä"));
	}

	sf::FloatRect rect = m_labels[0].getLocalBounds();
		m_labels[0].setOrigin(rect.left + rect.width / 2.0f,
		rect.top + rect.height / 2.0f);
}

void State_MainMenu::MouseClick(EventDetails* l_details){
	SharedContext* context = m_stateMgr->GetContext();
	sf::Vector2i mousePos = l_details->m_mouse;

	float halfX = m_buttonSize.x / 2.0f;
	float halfY = m_buttonSize.y / 2.0f;
	for(int i = 0; i < 3; ++i){
		if(mousePos.x>=m_rects[i].getPosition().x - halfX &&
			mousePos.x<=m_rects[i].getPosition().x + halfX &&
			mousePos.y>=m_rects[i].getPosition().y - halfY &&
			mousePos.y<=m_rects[i].getPosition().y + halfY)
		{
			if(i == 0)
			{
				m_stateMgr->SwitchTo(StateType::Game);
				
			} else if(i == 1){
				m_stateMgr->SwitchTo(StateType::LevelEditor);
			} else if(i == 2){
				m_stateMgr->GetContext()->m_wind->Close(l_details);
			}
		}
	}
}

void State_MainMenu::Draw(){
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();
	m_BGSprite.setTexture(m_bgtexture.get(Textures::MenuBGScreen));
	window->draw(m_BGSprite);
	window->draw(m_text);
	for(int i = 0; i < 3; ++i){
		window->draw(m_rects[i]);
		window->draw(m_labels[i]);
	}
}

void State_MainMenu::Update(const sf::Time& l_time){}
void State_MainMenu::Deactivate(){}