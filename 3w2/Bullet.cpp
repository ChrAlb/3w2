#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
	m_otype = t_Bullets;
	
	
	m_Textures.load(Textures::Bullet, "graphics/bullet.png");
	m_Sprite = Sprite(m_Textures.get(Textures::Bullet));
	m_is_alive = true;
	m_iscollided = false;

	
}

bool Bullet::handleInput()
{
	return m_JustJumped;
}

void Bullet::update(float dt, Vector2f Plpos)
{
	if (m_vel.x > 0)
	{
        m_Position.x  += m_Speed * dt;
	}
	else
	{
		m_Position.x  -= m_Speed * dt;
	}
	
	FloatRect r = getPosition();

	// Feet
	m_Feet.left = r.left + 3;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width - 6;
	m_Feet.height = 1;
	 
	// Head
	m_Head.left = r.left;
	m_Head.top = r.top + (r.height *.3);
	m_Head.width = r.width;
	m_Head.height = 1;

	// Right
	m_Right.left = r.left + r.width;
	m_Right.top = r.top + r.height *.35;
	m_Right.width = 1;
	m_Right.height = r.height * .3;

	// Left
	m_Left.left = r.left;
	m_Left.top = r.top + r.height * .35;
	m_Left.width = 1;
	m_Left.height = r.height * .3;


	m_Sprite.setPosition(m_Position);

}

Vector2f Bullet::setm_vel(Vector2f vel)
{
	return m_vel = vel;
}

