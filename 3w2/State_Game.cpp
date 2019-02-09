#include "stdafx.h"
#include "State_Game.h"
#include "StateManager.h"
#include "LevelManager.h"
#include <iostream>
#include "LevelManager.h"
#include <list>
#include <string.h>

State_Game::State_Game(StateManager* l_stateManager)
	: BaseState(l_stateManager)
{

}

State_Game::~State_Game(){}

void State_Game::OnCreate(){
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;

	evMgr->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
	evMgr->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
	evMgr->AddCallback(StateType::Game, "Key_F1", &State_Game::Statistik,this);
	evMgr->AddCallback(StateType::Game, "Key_F2", &State_Game::Debug, this);
	evMgr->AddCallback(StateType::Game, "Key_F3", &State_Game::PlayerInfo, this);


	slopenumber = 0;
	//m_font.loadFromFile("graphics/Arial.ttf");
	// Dummy für Deco in Levels, später zu LevelManager zügeln!
	m_Textures.load(Textures::Tree, "graphics/Tree.png");

	m_justexploded = false;

	sf::Vector2u size = m_stateMgr->GetContext()->m_wind->GetWindowSize();
	m_view.setSize(size.x,size.y);
	m_view.setCenter(size.x/2,size.y/2);
	m_view.zoom(0.6f);
	m_stateMgr->GetContext()->m_wind->GetRenderWindow()->setView(m_view);

	
}

void State_Game::OnDestroy(){
	EventManager* evMgr = m_stateMgr->
		GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::Game, "Key_Escape");
	evMgr->RemoveCallback(StateType::Game, "Key_P");
	evMgr->RemoveCallback(StateType::Game, "Key_F1");
	evMgr->RemoveCallback(StateType::Game, "Key_F2");
	evMgr->RemoveCallback(StateType::Game, "Key_F3");
}




void State_Game::Update(const sf::Time& l_time)

//////////////////////////////////////////////////////////////////////////
{
	
	m_Playing = true;

	for (iter = objects.begin(); iter != objects.end(); ++iter)
	{
		if ((*iter)->handleInput())
		{
			;
		}
	}
/////////////////////////////////////////////////////////////////////////////	
	
	float newpos, move;

	float dt = l_time.asSeconds();

	//LevelManager lm;


	if ((m_LM.get_allLeveldone()) || (m_gameStats.nomorelives()))
	{
		m_stateMgr->Remove(StateType::Game);
		m_stateMgr->SwitchTo(StateType::MainMenu);
	}


	if (m_newlevelrequiered)
	{
		
		// Hier alle Objects löschen!?
		m_newlevelrequiered = false;
		loadLevel();

	}

	if (m_Playing)
	{



		if (player->get_isfiring())
			if (player->get_justfired())

			{
				Vector2f tt = player->getCenter();


				m_SoundPlayer.play(SoundEffect::Colt);
				bullet = new Bullet();

				Vector2f vel = player->getm_Vel();

				bullet->setm_vel(vel);
				if (vel.x > 0)
					tt.x = tt.x + TILE_SIZE;
				else
					tt.x = tt.x - TILE_SIZE;

				bullet->spawn(tt, 0);
				objects.push_back(bullet);
				player->set_justfired(false);

			}
			else
				player->set_justfired(false);


		detectCollisions_Objects();
		clean_objects();
		Vector2f tt;
		tt = getPlayer_position_putofList();
		spawnRandomEnemies();



		for (iter = objects.begin(); iter != objects.end(); ++iter)
		{


			{

				// DEBUG
				if (debug)
				{

					head_box.setSize(sf::Vector2f((*iter)->getHead().width, (*iter)->getHead().height));
					head_box.setOutlineColor(sf::Color::Red);
					head_box.setOutlineThickness(5);
					head_box.setPosition((*iter)->getHead().left, (*iter)->getHead().top);

					right_box.setSize(sf::Vector2f((*iter)->getRight().width, (*iter)->getRight().height));
					right_box.setOutlineColor(sf::Color::Green);
					right_box.setOutlineThickness(5);
					right_box.setPosition((*iter)->getRight().left, (*iter)->getRight().top);

					left_box.setSize(sf::Vector2f((*iter)->getLeft().width, (*iter)->getLeft().height));
					left_box.setOutlineColor(sf::Color::Blue);
					left_box.setOutlineThickness(5);
					left_box.setPosition((*iter)->getLeft().left, (*iter)->getLeft().top);

					feet_box.setSize(sf::Vector2f((*iter)->getFeet().width, (*iter)->getFeet().height));
					feet_box.setOutlineColor(sf::Color::Magenta);
					feet_box.setOutlineThickness(5);
					feet_box.setPosition((*iter)->getFeet().left, (*iter)->getFeet().top);

					center_box.setSize(sf::Vector2f((*iter)->get_Center().width, (*iter)->get_Center().height));
					center_box.setOutlineColor(sf::Color::Yellow);
					center_box.setOutlineThickness(5);
					center_box.setPosition((*iter)->get_Center().left, (*iter)->get_Center().top);

				}

				if (detectCollisions(*(*iter)))
				{
					if ((*iter)->get_objecttype() == t_Player)
					{
						m_newlevelrequiered = true;
						this->gameview.reset(sf::FloatRect(0, 0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));

					}
				}



				(*iter)->update(dt, tt);

				if ((*iter)->get_objecttype() == t_Player)
				{

					newpos = (*iter)->getCenter().x;


					if ((oldpos == newpos) || (newpos < (VideoMode::getDesktopMode().width / 2)) || (newpos >(m_VALevel.getBounds().width - (VideoMode::getDesktopMode().width / 2))))
					{
						move = 0;

					}
					else
					{
						move = newpos - oldpos;
					}
					oldpos = newpos;

					this->gameview.move(move, 0);
				}



			}

		}
	}


	return;

}

void State_Game::Draw()

{
	m_BackgroundSprite.setTexture(m_Textures.get(m_leveldaten.m_bg_texture));


	m_Tree_Sprite.setTexture(m_Textures.get(Textures::Tree));
	m_Tree_Sprite.setPosition(Vector2f(1000, 700));

	sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	
	window->clear(sf::Color::White);
	
    window->setView(bgview);
	window->draw(m_BackgroundSprite);

	if (stats)
	{
		window->setView(PlInfo);
		m_PlayerInfo.print(*window, *player);
		m_PlayerInfo.printEnemy(*window, *enemy);
	}

	if (gamestat)
	{
		window->setView(PlInfo);
		m_gameStats.print(*window, *player);
	}

	window->setView(gameview);

	window->draw(m_Tree_Sprite);

	window->draw(m_VALevel, &m_Textures.get(m_leveldaten.m_tileset));


	for (iter = objects.begin(); iter != objects.end(); ++iter)
	{
		window->draw((*iter)->getSprite());
	}


	window->draw(text);

	// DEBUG
	if (debug)
	{
		window->draw(center_box);
		window->draw(head_box);
		window->draw(right_box);
		window->draw(left_box);
		window->draw(feet_box);

		window->draw(box);

		window->draw(box_position);
		// DEBUNG End
	}
	//window->display();
	return;

}

void State_Game::MainMenu(EventDetails* l_details){
	m_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails* l_details){
	m_stateMgr->SwitchTo(StateType::Paused);
}

void State_Game::Activate(){}
void State_Game::Deactivate(){}


void State_Game::set_gamestats(bool stat)
{
	gamestat = stat;
}

Vector2f State_Game::getPlayer_position_putofList()
{

	for (iter = objects.begin(); iter != objects.end(); ++iter)

		if ((*iter)->get_objecttype() == t_Player)
			return (*iter)->getCenter();

}

void State_Game::spawnRandomEnemies()
{
	//unschön!
	int maxlevelsize = (m_LM.getLevelSize().x * TILE_SIZE) - TILE_SIZE;


	int random = rand() % 3000 + 1;
	if (random == 3000)
	{
		enemy = new Enemy();

		float newx = rand() % m_LM.getLevelSize().x*TILE_SIZE + 1;
		float newy = rand() % 15 * TILE_SIZE + 1;

		Vector2f spawnpos;


		spawnpos.x = newx;
		spawnpos.y = newy;



		enemy->spawn(spawnpos, GRAVITY);
		//unschön!
		enemy->set_maxlevelsize(maxlevelsize);
		objects.push_back(enemy);

	}

}

void State_Game::Statistik(EventDetails* l_details)
{
if ( (gamestat)  && (!stats) )
gamestat = false;
else
gamestat = true;
}


void State_Game::Debug(EventDetails* l_details)
{
if (debug)
	debug = false;
else
	debug = true;

}


void State_Game::PlayerInfo(EventDetails* l_details)
{
if  ( (stats) && (!gamestat) )
	stats = false;
else
	stats = true;

}

