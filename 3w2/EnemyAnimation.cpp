#include "stdafx.h"
#include "EnemyAnimation.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

EnemyAnimation::EnemyAnimation()
{
	m_Textures.load(Textures::Enemy, "graphics/enemysheet.png");

}

void EnemyAnimation::addFrame(sf::IntRect rect)
{
	m_frames.push_back(rect);
}

void  EnemyAnimation::addRow(int x, int y, int width, int height, int maxframe)
{
	for (int i = 0; i < maxframe; i++)
	{
		addFrame({ x + i*width, y,width, height });
	}
}

void  EnemyAnimation::ApplytoSprite(sf::Sprite& s)
{
	s.setTexture(m_Textures.get(Textures::Enemy));
	s.setTextureRect(m_frames[iFrame]);
}

void  EnemyAnimation::Update(float dt, int maxframes)
{
	mframe = maxframes;
	time += dt;
	while (time >= holdtime)
	{
		time -= holdtime;
		//if (!animation_stop)
		Advance();
	}
}


void  EnemyAnimation::Advance()
{

	//if (++iFrame >= maxframes)   => hier geht es noch nicht
	if (++iFrame >= mframe)
	{
		iFrame = 0;
	}

}
