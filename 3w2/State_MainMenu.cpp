#include "stdafx.h"
#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager* l_stateManager)
	: BaseState(l_stateManager){}

State_MainMenu::~State_MainMenu(){}


void State_MainMenu::OnCreate() {

	m_bgtexture.load(Textures::MenuBGScreen, "graphics/BG3.png");

    GUI_Manager* gui = m_stateMgr->GetContext()->m_guiManager;
	gui->LoadInterface(StateType::MainMenu, "MainMenu.interface", "MainMenu");
	gui->GetInterface(StateType::MainMenu, "MainMenu")->SetPosition(sf::Vector2f(250.f, 168.f));
	
	EventManager* eMgr = m_stateMgr->GetContext()->m_eventManager;
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_Play", &State_MainMenu::Play, this);
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_LevEdit", &State_MainMenu::LevEdit, this);
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_Quit", &State_MainMenu::Quit, this);
	eMgr->AddCallback(StateType::MainMenu, "Key_F1", &State_MainMenu::Start_TileMaker, this);
}

void State_MainMenu::OnDestroy() {
	m_stateMgr->GetContext()->m_guiManager->RemoveInterface(StateType::MainMenu, "MainMenu");
	EventManager* eMgr = m_stateMgr->GetContext()->m_eventManager;
	eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_Play");
	eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_LevEdit");
	eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_Quit");
}

void State_MainMenu::Activate() {
	auto& play = *m_stateMgr->GetContext()->m_guiManager->
		GetInterface(StateType::MainMenu, "MainMenu")->GetElement("Play");
	if (m_stateMgr->HasState(StateType::Game)) {
		// Resume
		play.SetText("Pausä");
	}
	else {
		// Play
		play.SetText("Spilä");
	}
}


void State_MainMenu::Play(EventDetails* l_details) { m_stateMgr->SwitchTo(StateType::Game); }
void State_MainMenu::LevEdit(EventDetails * l_details) {m_stateMgr->SwitchTo(StateType::LevelEditor);} 
void State_MainMenu::Quit(EventDetails* l_details) 
{ 
	    // Das ist Scheisse (Weihnachten 2018)
	    //m_stateMgr->Remove(StateType::MainMenu); 
		//m_stateMgr->Remove(StateType::LevelEditor);
     	m_stateMgr->GetContext()->m_wind->Close()   ; 
}

void State_MainMenu::Start_TileMaker(EventDetails * l_details)
{
	MakeTileSet maketileset;
	maketileset.create_TilSetFile();
}

void State_MainMenu::Draw()
{
	
	sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	m_BGSprite.setTexture(m_bgtexture.get(Textures::MenuBGScreen));
	window->draw(m_BGSprite);
	
	
}
void State_MainMenu::Update(const sf::Time& l_time){}
void State_MainMenu::Deactivate(){}