
#include "stdafx.h"
#include "Enemy.h"
#include "SharedContext.h"
#include "ResourceIdentifiers.h"
#include <iostream>



Enemy::Enemy() : m_hasDestination(false)
{

	m_Textures.load(Textures::Enemy, "graphics/enemysheet.png");
	m_Sprite = Sprite(m_Textures.get(Textures::Enemy));

	animations[int(EnemyAnimationIndex::WalkingRight)].addRow(0, 000, 100, 100, 33);
	animations[int(EnemyAnimationIndex::WalkingLeft)].addRow(0, 100, 100, 100, 33);
	animations[int(EnemyAnimationIndex::DyingRight)].addRow(0, 200, 100, 100, 33);
	animations[int(EnemyAnimationIndex::Dead)].addRow(3200, 200, 100, 100, 1);

	max_frames[int(EnemyAnimationIndex::WalkingRight)] = 33;
	max_frames[int(EnemyAnimationIndex::WalkingLeft)] = 33;
	max_frames[int(EnemyAnimationIndex::DyingRight)] = 33;
	max_frames[int(EnemyAnimationIndex::Dead)] = 1;

	m_otype = t_Enemy;
	m_iscollided = false;
	m_is_alive = true;
	m_destination.x = 1;
	m_JustJumped = false;
	m_isFalling = true;

	m_LeftPressed = true;
	m_RightPressed = true;

	m_dying_counter = 0;
	m_hit = 0;


}


bool Enemy::handleInput()
{
	m_isFalling = true;
	m_vel = m_destination;
	return m_JustJumped;
}

void Enemy::update(float dt, Vector2f Plpos)
{
	m_oldposition = m_Position;

	if (m_isFalling)
	{
		m_Position.y += m_Gravity/2 * dt;
	}

	if (m_iscollided)
	{
		m_iscollided = false;
	}

	if (fabs(m_Position.x - m_initialPosition.x) < m_enenyRange)
	{
		m_Position.x += EnemySpeed * m_destination.x * dt;
	}

	if (m_Position.x >= m_initialPosition.x + m_enenyRange)
	{
		m_Position.x = m_initialPosition.x + m_enenyRange -10;
		m_destination.x = -m_destination.x;
	}
	
	if (m_Position.x <= m_initialPosition.x - m_enenyRange)
	{
		m_Position.x = m_initialPosition.x - m_enenyRange + 10;
		m_destination.x = -m_destination.x;
	}


	if (m_destination.x < 0)
		curAnimation = EnemyAnimationIndex::WalkingLeft;
	else
		curAnimation = EnemyAnimationIndex::WalkingRight;

	if (m_iscollidedwithobject)
	{
		if (m_hit < max_frames[int(EnemyAnimationIndex::DyingRight)])
		{
			curAnimation = EnemyAnimationIndex::DyingRight;
			m_hit++;
		}
		else
		{
			if (m_dying_counter < m_dying_time)
			{
				curAnimation = EnemyAnimationIndex::Dead;
				m_dying_counter++;
			}
			else
			{
				m_is_alive = false;
				m_dying_counter = 0;
				m_hit = 0;
			}


		}

	}

	FloatRect r = getPosition();

	// Feet
	m_Feet.left = r.left + 3;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width - 6;
	m_Feet.height = 1;

	// Head
	m_Head.left = r.left;
	m_Head.top = r.top + (r.height * .3);
	m_Head.width = r.width;
	m_Head.height = 1;

	// Right
	m_Right.left = r.left + r.width;
	m_Right.top = r.top + r.height * .35;
	m_Right.width = 1;
	m_Right.height = r.height * .3;

	// Left
	m_Left.left = r.left;
	m_Left.top = r.top + r.height * .35;
	m_Left.width = 1;
	m_Left.height = r.height * .3;

	// Center
	m_Center.left = r.left + (r.width / 2) - 1;
	m_Center.top = r.top + (r.height * .3);
	m_Center.width = 2;
	m_Center.height = r.height - (r.height * .3);



	animations[int(curAnimation)].Update(dt, max_frames[int(curAnimation)]);

	animations[int(curAnimation)].ApplytoSprite(m_Sprite);

	m_Sprite.setPosition(m_Position);

}




