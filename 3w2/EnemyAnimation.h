#pragma once

#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class EnemyAnimation
{
public:
	EnemyAnimation();
	void addFrame(sf::IntRect rect);
	void addRow(int x, int y, int width, int height, int maxframe);
	void ApplytoSprite(sf::Sprite& s);
	void Update(float dt, int maxframes);


private:
	void Advance();


private:
	static constexpr int nFrames = 8;
	static constexpr float holdtime = 0.1f;

	TextureHolder m_Textures;

	std::vector<sf::IntRect> m_frames;
	int iFrame = 0;
	float time = 0.0f;

	int mframe;

};
