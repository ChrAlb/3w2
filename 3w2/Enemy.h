#pragma once
#include "PlayableCharacter.h"
#include "EnemyAnimation.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"


class Enemy : public PlayableCharacter
{

private:

	enum class EnemyAnimationIndex
	{
		WalkingLeft,
		WalkingRight,
		DyingRight,
		Dead,
		Count
	};
	  
	sf::Vector2f m_destination;
	bool m_hasDestination;

	int m_dying_counter;
	const int m_dying_time = 190;

	

	TextureHolder m_Textures;

public:
	Enemy();
	bool handleInput();
	void update(float dt, Vector2f Plpos);

	const int EnemySpeed = 75;

	EnemyAnimation animations[int(EnemyAnimationIndex::Count)];
	EnemyAnimationIndex curAnimation = EnemyAnimationIndex::WalkingRight;
	int max_frames[int(EnemyAnimationIndex::Count)];

	




};
