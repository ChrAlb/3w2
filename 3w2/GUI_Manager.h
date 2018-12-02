#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "SharedContext.h"
 

using namespace sf;



class GUI_Manager
{
	

	
protected:
	
	enum GUI_ElementType { TextField, EditBox };

	enum  GUI_EventType { None, Click, Release, Hover, Leave };

	GUI_ElementType g_type;
	GUI_EventType   g_eventType;

	RectangleShape g_window;
	Vector2f       g_pos;
	Vector2f       g_size;

	Color          g_backgroundcolor;
	Color          g_fontcolor;
	String         g_windowtext;

	


public:
	
	
	void virtual draw() = 0;
	void virtual update() = 0;
	
	void virtual deactivate() = 0;

	void update_GUI();
	void draw_GUI(RenderWindow& window);
	
};