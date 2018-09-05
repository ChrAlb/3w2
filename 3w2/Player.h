#pragma once
#include "PlayableCharacter.h"
#include "Animation.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SoundPlayer.h"


class Player : public PlayableCharacter 

{
	 
private:
	enum class AnimationIndex
	{
		WalkingLeft,
		WalkingRight,
		StopingLeft,
		StopingRight,
		Stoping,
		JumpingLeft,
		JumpingRight,
		ShootingLeft,
	    ShootingRight,
		Explode,
		Count
	};

	SoundPlayer m_SoundPlayer;

	
	AnimationIndex temp;

public:

	
	void SetDirection(const sf::Vector2f& dir);
	Player::Player();
	
	bool handleInput();
	void update(float dt, Vector2f Plpos);

	Animation animations[int(AnimationIndex::Count)];
	AnimationIndex curAnimation = AnimationIndex::Stoping;
	int max_frames[int(AnimationIndex::Count)];
	int m_countJumpLoops;

	int m_explosion_counter;
	const int m_explosion_time = 90;

	
	

};
