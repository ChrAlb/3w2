#pragma once
#include <SFML\Graphics.hpp>



using namespace sf;

enum object_types { t_Player, t_Enemy, t_Bullets, t_Others };

class PlayableCharacter
	
{


public:

	const int TILE_SIZE = 50;

	PlayableCharacter();
	void spawn(Vector2f startPosition, float gravity);
	bool virtual handleInput() = 0;
	void virtual update(float dt, Vector2f Plpos) = 0;

	FloatRect getPosition();

	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();
	FloatRect get_Center();

	
	Sprite getSprite();
	 
	void stopFalling(float position);
	void stopRight(float position);
	void stopLeft(float position);
	void stopJump();

	
	//void set_objecttype(object_types otype);
	object_types get_objecttype();

	void resolve_slope(float position, int &slopenumber);
	
	Vector2f getCenter();
    Vector2f getm_Vel();

	bool get_m_on_slope();
	void set_m_on_slope(bool onslope);
	bool get_m_end_slope();
	void set_m_end_slope(bool endslope);
	Vector2i get_tilepos();
	void set_tilepos(Vector2i tpos);

	Vector2i CalculateTile_pos();

	void set_maxlevelsize(int mlevelsize);
	int get_maxlevelsize();

	
	bool get_isfiring();

	
	bool get_justfired();
	void set_justfired(bool jfired);
	

	void set_iscollided(bool iscollided);
	bool get_iscollided();

	void set_iscollidedwithobject(bool iscollided);

	void set_isalive(bool alive);
	bool get_isalive();
	

	void set_gravity(float gravity);

	

protected:
	Sprite m_Sprite;
	

	float m_JumpDuration;

	bool  m_isJumping;
	bool  m_isFalling;

	bool m_LeftPressed;
	bool m_RightPressed;

	bool m_on_slope;
	bool m_slope_end;

	
	float m_TimeThisJump;

	bool m_JustJumped;
	unsigned int m_id;

	float m_Gravity;
	float m_Speed = 300;
	

	Vector2i max_levelsize;
	Vector2i tile_pos;

	Vector2f m_Position;

	Vector2f m_vel;

	Texture m_Texture;

	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;
	FloatRect m_Center;

	object_types m_otype;

	int m_maxlevelsize;

	bool m_iscollided;
	bool m_iscollidedwithobject;

	bool m_isfiring;
	bool m_justfired;

	bool m_is_alive;

	
	
		
	Vector2f m_oldposition;
	
	
	sf::Vector2f dir = { 0.0f,0.0f };

	

};


