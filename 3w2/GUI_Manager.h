#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "SharedContext.h"
#include "GUI_Textbox.h"
 

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

	std::list<GUI_Manager*> GUI_objects;
	std::list<GUI_Manager*>::iterator iter;
	std::list <GUI_Manager* >::iterator iter2;

	GUI_Textbox  *textbox;


public:
	GUI_Manager();
	~GUI_Manager();

	void virtual draw(RenderWindow& window) = 0;
	void virtual update() = 0;
	
	void virtual deactivate() = 0;

	void register_GUI();

	void update_GUI();
	void draw_GUI(RenderWindow& window);
	
};