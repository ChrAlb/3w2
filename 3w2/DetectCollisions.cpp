#include "stdafx.h"
#include "game.h"
#include <iostream>
#include "Game_state_game.h"

bool GameStateGame::detectCollisions(PlayableCharacter& character)

{



bool reachedGoal = false;
FloatRect detecionZone = character.getPosition();

int counter = 0;


	
//Debug
if (debug)
{
    box_position.setSize(sf::Vector2f(detecionZone.width, detecionZone.height));
    box_position.setOutlineColor(sf::Color::Black);
    box_position.setOutlineThickness(3);
    box_position.setFillColor(sf::Color(255, 0, 0, 0));
    box_position.setPosition(detecionZone.left, detecionZone.top);
}

FloatRect block;

block.width = TILE_SIZE;
block.height = TILE_SIZE;

int startX = (int)(detecionZone.left / TILE_SIZE - 1);
int startY = (int)(detecionZone.top / TILE_SIZE - 1);
int endX = (int)(detecionZone.left / TILE_SIZE + 3);
int endY = (int)(detecionZone.top / TILE_SIZE + 3);

		
if (startX < 0)startX = 0;
if (startY < 0)startY = 0;
if (endX >= m_LM.getLevelSize().x)endX = m_LM.getLevelSize().x;
if (endY >= m_LM.getLevelSize().y)endY = m_LM.getLevelSize().y;

FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE, m_LM.getLevelSize().y * TILE_SIZE);


if (!character.getPosition().intersects(level))
{
	if (character.get_objecttype() == t_Player)
	{
		m_justexploded = false;
		character.spawn(m_LM.getStartPosition(), GRAVITY);
		this->gameview.reset(sf::FloatRect(0, 0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
	}
	if (character.get_objecttype() == t_Enemy)
	{
		character.set_isalive(false);
	}
	if (character.get_objecttype() == t_Bullets)
	{
		character.set_isalive(false);
	}
}




for (int x = startX; x < endX; x++)
{
	for (int y = startY; y < endY; y++)
	{

		block.left = x * TILE_SIZE;
		block.top = y * TILE_SIZE;

		//********** DEBUG

		if (debug)
		{
			box.setSize(sf::Vector2f((endX - startX)*TILE_SIZE, (endY - startY)*TILE_SIZE));
			box.setFillColor(sf::Color(255, 0, 255, 50));
			box.setPosition(block.left - ((endX - startX)*TILE_SIZE) + 2 * TILE_SIZE, block.top - ((endY - startY)*TILE_SIZE) + TILE_SIZE);
		}
		//**************

		if (character.get_m_end_slope())
		    {
			character.set_m_end_slope(false);
			}
		else
		{
		
			if (!character.get_m_on_slope())
			{
				if ((m_ArrayLevel[y][x] == 10) || (m_ArrayLevel[y][x] == 28))
				{
					if (character.get_Center().intersects(block))
					{

						switch (m_ArrayLevel[y][x])
						{
						case 10:  // Tile # 10
							slopenumber = 10;
							break;
						case 28:  // Tile #28
							slopenumber = 28;
							break;
						}

						character.set_m_on_slope(true);
						character.set_tilepos(character.CalculateTile_pos());
						character.resolve_slope(0, slopenumber);

						if (checkNextTile(character.getm_Vel(), character.get_tilepos(), slopenumber))
							character.set_m_on_slope(true);
						else
						{
							character.set_m_end_slope(true);
							character.set_m_on_slope(false);
							
													}

					}
				}
			}
		}
		if (character.get_m_on_slope())
		{
			if (counter < 1)
			{

				counter = counter + 1;
				character.set_tilepos(character.CalculateTile_pos());
				character.resolve_slope(0,slopenumber);
			}

			
			if (checkNextTile(character.getm_Vel(), character.get_tilepos(),slopenumber))  
				
				character.set_m_on_slope(true);
			else
			{
				character.set_m_end_slope(true);
				character.set_m_on_slope(false);
				
			}

		}


		if (!character.get_m_on_slope())
		{

				if (

					(m_ArrayLevel[y][x] == 0) ||
					(m_ArrayLevel[y][x] == 1) ||
					(m_ArrayLevel[y][x] == 7) ||
					(m_ArrayLevel[y][x] == 8) ||
					(m_ArrayLevel[y][x] == 9) ||
					(m_ArrayLevel[y][x] == 14) ||
					(m_ArrayLevel[y][x] == 15) ||
					(m_ArrayLevel[y][x] == 16) ||
					(m_ArrayLevel[y][x] == 17) ||
					(m_ArrayLevel[y][x] == 18) ||
					(m_ArrayLevel[y][x] == 19) ||
					(m_ArrayLevel[y][x] == 23) ||
					(m_ArrayLevel[y][x] == 24)
					)

				{
					if (character.getRight().intersects(block))
					{
                      character.stopRight(block.left);

                          if (character.get_objecttype() == t_Bullets)
                             {
	                             character.set_iscollided(true);
	                             character.set_isalive(false);
                             }

                        if (character.get_objecttype() == t_Enemy)
                             character.set_iscollided(true);

					}
					else
						if (character.getLeft().intersects(block))
						{
							character.stopLeft(block.left + TILE_SIZE);



							if (character.get_objecttype() == t_Bullets)
							{
								character.set_iscollided(true);
								character.set_isalive(false);
							}


							if (character.get_objecttype() == t_Enemy)
								character.set_iscollided(true);

						}

						if (character.getFeet().intersects(block))
						{
							if (m_ArrayLevel[y][x] == 1)
							{
								if (!m_justexploded)
									if (character.get_objecttype() == t_Player)
								{
									m_SoundPlayer.play(SoundEffect::Explosion);
									m_justexploded = true;
									m_gameStats.subtractlive();
								}
							}
							else
							{
								character.stopFalling(block.top);

							}

						}
						else
							if (character.getHead().intersects(block))
							{
								character.stopJump();
							}

				}


				// LevelEnd Reached (Tile #2)
				if (m_ArrayLevel[y][x] == 2)
				{
					reachedGoal = true;
				}
			}
		} // end for
	}  // end for
	return reachedGoal;
}

void GameStateGame::clean_objects()
{


	for (iter = objects.begin(); iter != objects.end();)
	{
		if (!(*iter)->get_isalive())
		{
			delete (*iter);
			iter = objects.erase(iter);
		}
		else
			iter++;


	}


}

void GameStateGame::detectCollisions_Objects()
{
	for (iter = objects.begin(); iter != objects.end(); ++iter)
	{
		for (iter2 = iter; iter2 != objects.end(); ++iter2)
		{
			if ((*iter)->getPosition().intersects((*iter2)->getPosition()))
			{
				
				if (iter == iter2)
				{
					;
				}
				else
				{

					if ((*iter)->get_objecttype() == t_Bullets)
						if ((*iter2)->get_objecttype() == t_Enemy)
						{
							(*iter2)->set_iscollidedwithobject(true);
						    (*iter)->set_isalive(false);
							int t;
							
							m_gameStats.addpointfordeadeney();
						}
							

					if ((*iter2)->get_objecttype() == t_Bullets)
						if ((*iter)->get_objecttype() == t_Enemy)
						{
							(*iter2)->set_isalive(false);
							(*iter)->set_iscollidedwithobject(true);
							int t;
							
							m_gameStats.addpointfordeadeney();
						}

					if ((*iter)->get_objecttype() == t_Player)
						if ((*iter2)->get_objecttype() == t_Enemy)
						{
							(*iter)->set_iscollided(true);
                            (*iter2)->set_isalive(false);
							
							m_gameStats.subtractlive();
							
						}

					if ((*iter2)->get_objecttype() == t_Player)
						if ((*iter)->get_objecttype() == t_Enemy)
						{
							(*iter2)->set_iscollided(true);
							(*iter)->set_isalive(false);
							
							m_gameStats.subtractlive();
						}

					
				}
					
			}
				        
		} // for
	} //for
} //end

bool GameStateGame::checkNextTile(Vector2f &vel, Vector2i &tile_pos, int &slopenumber)
{
	
	if (slopenumber == 10)
	{
		if (vel.x > 0)
		{
			{
				if (m_ArrayLevel[tile_pos.y - 1][tile_pos.x + 1] == slopenumber)
					return true;
				else
					return false;
			}
		}
		else
		{
			if (vel.x < 0)
			{
				{
					if (m_ArrayLevel[tile_pos.y + 1][tile_pos.x - 1] == slopenumber)
						return true;
					else
						return false;
				}
			}
			else
				return false;

		}
	}

	
	if (slopenumber == 28)
	{
		if (vel.x > 0)
		{
			{
				if (m_ArrayLevel[tile_pos.y + 1][tile_pos.x + 1] == slopenumber)
					return true;
				else
					return false;
			}
		}
		else
		{
			if (vel.x < 0)
			{
				{
					if (m_ArrayLevel[tile_pos.y + 1][tile_pos.x - 1] == slopenumber)
						return true;
					else
						return false;
				}
			}
			else
				return false;

		}
	}


}



