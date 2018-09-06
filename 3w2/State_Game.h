#pragma once
#include "BaseState.h"
#include <SFML\Graphics.hpp>
#include <list>

#include "EventManager.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerInfo.h"
#include "GameStats.h"
#include "Bullet.h"
#include "Levelmanager.h"

class State_Game : public BaseState{
public:
	State_Game(StateManager* l_stateManager);
	~State_Game();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

	void MainMenu(EventDetails* l_details);
	void Pause(EventDetails* l_details);
	void ToggleOverlay(EventDetails* l_details);

	void set_gamestats(bool stat);

	Vector2f getPlayer_position_putofList();

	void spawnRandomEnemies();

	

private:
	bool debug = false;
	bool stats = false;

	bool gamestat = true;

	sf::View gameview;
	sf::View bgview;
	sf::View PlInfo;

	Sprite m_BackgroundSprite;
	Sprite m_Tree_Sprite;

	TextureHolder m_Textures;

	leveldate m_leveldaten;


	LevelManager m_LM;

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	const int GRAVITY = 300;

	bool m_newlevelrequiered = true;
	bool m_Playing = false;


	VertexArray m_VALevel;

	float oldpos;

	int** m_ArrayLevel = NULL;

	void loadLevel();

	bool detectCollisions(PlayableCharacter& character);

	void clean_objects();

	void detectCollisions_Objects();

	bool checkNextTile(Vector2f &vel, Vector2i &tile_pos, int &slopenumber);

	bool m_justexploded;

	
	int slopenumber;


	sf::RectangleShape  head_box;
	sf::RectangleShape  feet_box;
	sf::RectangleShape  left_box;
	sf::RectangleShape  right_box;
	sf::RectangleShape  center_box;
	sf::RectangleShape  box;
	sf::RectangleShape  box_position;

	std::list<PlayableCharacter*> objects;
	std::list<PlayableCharacter*>::iterator iter;
	std::list <PlayableCharacter* >::iterator iter2;

	Player *player;
	Enemy *enemy;
	Bullet *bullet;

	sf::Text text;

	bool m_onSlope = false;


	float m_Gravity;

	PlayerInfo m_PlayerInfo;
	GameStats m_gameStats;

	SoundPlayer m_SoundPlayer;

};


