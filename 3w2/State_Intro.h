#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include "SharedContext.h"
#include "ResourceIdentifiers.h"
#include "MusicPlayer.h"

class State_Intro : public BaseState{

public:
	State_Intro(StateManager* l_stateManager);
	~State_Intro();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

	void Continue(EventDetails* l_details);

private:
	TextureHolder m_introTexture;
	sf::Sprite  m_introBild;
	MusicPlayer  m_music;
};