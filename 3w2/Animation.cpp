#include "stdafx.h"
#include "Animation.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

Animation::Animation()
{
	m_Textures.load(Textures::Player, "graphics/joe_sheet1.png");
	
} 

void Animation::addFrame(sf::IntRect rect)
{
	m_frames.push_back(rect);
}

void Animation::addRow(int x, int y, int width,int height,int maxframe)
{
	for (int i = 0; i < maxframe; i++)
	{
		addFrame({ x + i*width, y,width, height });		
	}
}

void Animation::ApplytoSprite(sf::Sprite& s)
{
	s.setTexture(m_Textures.get(Textures::Player));
	s.setTextureRect(m_frames[iFrame]);
}

void Animation::Update(float dt, int maxframes)
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

	
void Animation::Advance()
{
	
	//if (++iFrame >= maxframes)   => hier geht es noch nicht
		if (++iFrame >= mframe)
	{
		iFrame = 0;
	}
	
}
