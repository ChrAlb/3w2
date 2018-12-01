#pragma once
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;



class GUI_Manager
{
	
enum class GUI_ElementType{TextField,EditBox};

enum class GUI_EventType{None,Click,Release,Hover, Leave};
	
protected:
	
	RectangleShape g_window;
	Vector2f       g_pos;
	Vector2f       g_size;

	Color          g_backgroundcolor;
	Color          g_fontcolor;
	String         g_windowtext;

	GUI_ElementType g_type;
	GUI_EventType   g_eventType;


public:
	void virtual draw() = 0;
	void virtual update() = 0;
	void virtual activate() = 0;
	void virtual deactivate() = 0;

	
};