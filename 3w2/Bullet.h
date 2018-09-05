#pragma once

#include "PlayableCharacter.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"


class Bullet : public PlayableCharacter

{
public:
	Bullet();
    bool handleInput();
	void update(float dt, Vector2f Plpos);
	Vector2f setm_vel(Vector2f vel);

	
private:

	Vector2f m_vel;
	TextureHolder m_Textures;

};
