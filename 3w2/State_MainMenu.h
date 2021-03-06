#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include "SharedContext.h"
#include "ResourceIdentifiers.h"
#include "H_MakeTileSet.h"

class State_MainMenu : public BaseState{
public:
	State_MainMenu(StateManager* l_stateManager);
	~State_MainMenu();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

	
	void Play(EventDetails* l_details);
	void LevEdit(EventDetails* l_details);
	void Quit(EventDetails* l_details);
	void Start_TileMaker(EventDetails* l_details);
	void Start_SpriteSheetMaker(EventDetails* l_details);

private:
	TextureHolder m_bgtexture;
	sf::Sprite m_BGSprite;
	FontHolder m_font;
	sf::Text m_text;

	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPos;
	unsigned int m_buttonPadding;

	sf::RectangleShape m_rects[3];
	sf::Text m_labels[3];
};