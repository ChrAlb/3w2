#include "stdafx.h"
#include "Player.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include <iostream>




Player::Player()
{
	
	m_otype = t_Player;
	m_iscollided = false;
	m_is_alive = true;


    animations[int(AnimationIndex::WalkingRight)].addRow(0, 0, 80, 100,4);
	animations[int(AnimationIndex::WalkingLeft)].addRow(0, 100, 80, 100,4);
	animations[int(AnimationIndex::JumpingLeft)].addRow(0, 200, 80, 100, 9);
	animations[int(AnimationIndex::JumpingRight)].addRow(0, 300, 80, 100, 9);
	animations[int(AnimationIndex::Stoping)].addRow(0, 000, 80, 100, 1);
	animations[int(AnimationIndex::StopingRight)].addRow(0, 0, 80, 100, 1);
	animations[int(AnimationIndex::StopingLeft)].addRow(0, 100, 80, 100, 1);
	animations[int(AnimationIndex::ShootingLeft)].addRow(0, 400, 80, 100, 5);
	animations[int(AnimationIndex::ShootingRight)].addRow(0, 500, 80, 100, 5);
	animations[int(AnimationIndex::Explode)].addRow(0, 600, 80, 100, 1);

	max_frames[int(AnimationIndex::WalkingRight)] = 4;
	max_frames[int(AnimationIndex::WalkingLeft)] = 4;
	max_frames[int(AnimationIndex::JumpingLeft)] = 9;
	max_frames[int(AnimationIndex::JumpingRight)] = 9;
	max_frames[int(AnimationIndex::Stoping)] = 1;
	max_frames[int(AnimationIndex::StopingLeft)] = 1;
	max_frames[int(AnimationIndex::StopingRight)] = 1;
	max_frames[int(AnimationIndex::ShootingLeft)] = 5;
	max_frames[int(AnimationIndex::ShootingRight)] = 5;
	max_frames[int(AnimationIndex::ShootingRight)] = 1;

	m_countJumpLoops = 0;
	
	m_JumpDuration = .25;

	m_justfired = true;


	m_explosion_counter = 0;

	dir.x = 1;

	//Player::
	
}

bool Player::handleInput()
{
	

	m_JustJumped = false;
	
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
       m_isfiring = true;
	  

	}
		
	else
	{
		m_isfiring = false;
		m_justfired = true;
		
	}
		

	if ( (Keyboard::isKeyPressed(Keyboard::Space)) )
	{
		//m_anykeypressed = true;
		if (!m_isJumping && !m_isFalling)
		{
			m_isJumping = true;
			m_TimeThisJump = 0;
			m_JustJumped = true;
		}
	}
	else
	{
		//m_anykeypressed = false;
		m_isJumping = false;
		m_isFalling = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		m_LeftPressed = true;
		dir.x = -1.0f;
		
			
	}
	else
	{
        m_LeftPressed = false;
	}
		

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		m_RightPressed = true;
		dir.x = 1.0f;
	}
	else
	{
		m_RightPressed = false;
	}
	Player::SetDirection(dir);
	return m_JustJumped;

}



void Player::update(float elapsedTime, Vector2f Plpos)
{
	int mlevelsize;

	
	if (m_RightPressed)
	{
		m_oldposition = m_Position;
		m_Position.x += m_Speed * elapsedTime;
		
		
	}

	if (m_LeftPressed)
	{
		m_oldposition = m_Position;
		m_Position.x -= m_Speed * elapsedTime;
		
	}

	if (m_isJumping)
	{
	
		
		m_TimeThisJump += elapsedTime;

		if (m_TimeThisJump < m_JumpDuration)
		{
			m_Position.y -= m_Gravity * 2 * elapsedTime;
			m_countJumpLoops = m_countJumpLoops + 1;

			if (m_JustJumped)
			{
				m_SoundPlayer.play(SoundEffect::Jump);
				m_JustJumped = false;
			}
			
		}
		else
		{
			m_isJumping = false;
			m_isFalling = true;
			
		}
	}
	
		

	if  (m_isFalling)
	{
		m_Position.y += m_Gravity * elapsedTime;
		m_countJumpLoops = 0;
	} 

  
	if (Player::m_Position.x < 0)
	   {
		Player::m_Position.x = 0;
       }
	
	mlevelsize = Player::get_maxlevelsize();

	if (Player::m_Position.x > mlevelsize)
	{
		Player::m_Position.x = mlevelsize;
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
	m_Right.left = r.left + r.width ;
	m_Right.top = r.top + r.height *.35;
	m_Right.width = 1;
	m_Right.height = r.height * .3;

	// Left
	m_Left.left = r.left;
	m_Left.top = r.top + r.height * .35;
	m_Left.width = 1;
	m_Left.height = r.height * .3;

	// Center
	m_Center.left = r.left + (r.width / 2) - 1;
	m_Center.top = r.top + (r.height *.3);
	m_Center.width = 2;
	m_Center.height = r.height - (r.height *.3) ;

	animations[int(curAnimation)].Update(elapsedTime, max_frames[int(curAnimation)]);

	
	animations[int(curAnimation)].ApplytoSprite(m_Sprite);
	
	m_Sprite.setPosition(m_Position);

	
}
 

void Player::SetDirection(const sf::Vector2f & dir)
{
	m_vel = dir * m_Speed;
	if (dir.x > 0.0f)
		
		{
			curAnimation = AnimationIndex::WalkingRight;
		}
	else if (dir.x < 0.0f)
		
		{
			curAnimation = AnimationIndex::WalkingLeft;
		}

	
	if ((!m_LeftPressed) && (!m_RightPressed))
	{

      if (dir.x > 0.0f)
              curAnimation = curAnimation = AnimationIndex::StopingRight;
	  else if (dir.x < 0.0f)
		      curAnimation = curAnimation = AnimationIndex::StopingLeft;
	}
	

	if (m_isJumping)
	{

		if (dir.x > 0.0f)
			curAnimation = curAnimation = AnimationIndex::JumpingLeft;
		else if (dir.x < 0.0f)
			curAnimation = curAnimation = AnimationIndex::JumpingRight;
	}


	if (m_isfiring)
	{
		 
		if (dir.x > 0.0f)
			curAnimation = AnimationIndex::ShootingLeft;
		else if (dir.x < 0.0f)
			curAnimation = AnimationIndex::ShootingRight;
	}

	if (m_iscollided)
	{
		
		temp = curAnimation;

		if (m_explosion_counter < m_explosion_time)
		{
		 
		  if (m_explosion_counter == 1)
		       m_SoundPlayer.play(SoundEffect::Explosion);
          curAnimation = AnimationIndex::Explode;
		  temp = curAnimation;
		  m_explosion_counter++;

		}
		else
		{
           curAnimation = temp;
		   m_explosion_counter = 0;
		   m_iscollided =false;
		}
        
		
		
	}
		

}

