#include "stdafx.h"
#include "State_Intro.h"
#include "StateManager.h"

State_Intro::State_Intro(StateManager* l_stateManager)
	: BaseState(l_stateManager){}

State_Intro::~State_Intro(){}

void State_Intro::OnCreate(){
	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();

	m_introTexture.load(Textures::TitleScreen, "graphics/Title.png");

	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::Intro, "Intro_Continue",&State_Intro::Continue,this);
}

void State_Intro::OnDestroy(){
	
	EventManager* evMgr = m_stateMgr->
		GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::Intro,"Intro_Continue");
}

void State_Intro::Draw(){
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();
	m_introBild.setTexture(m_introTexture.get(Textures::TitleScreen));


	window->draw(m_introBild);
	
}

void State_Intro::Continue(EventDetails* l_details){
	//m_stateMgr->SwitchTo(StateType::MainMenu);
	m_stateMgr->Remove(StateType::Intro);
}

void State_Intro::Update(const sf::Time& l_time){}
void State_Intro::Activate(){}
void State_Intro::Deactivate(){}