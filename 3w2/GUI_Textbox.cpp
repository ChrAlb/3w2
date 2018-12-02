#include "stdafx.h"
#include "GUI_Textbox.h"



void GUI_Textbox::draw(RenderWindow& window)
{
	
	window.draw(g_window);
}

void GUI_Textbox::update()
{
}

void GUI_Textbox::acitvate(Vector2f pos, Vector2f size, String string)
{
	g_type = TextField;
	g_pos = pos;
	g_size = size;
	g_window.setPosition(g_pos);
	g_window.setSize(g_size);

	g_backgroundcolor = sf::Color(255, 106, 0);;
	g_fontcolor = sf::Color(0, 0, 0);
	g_windowtext = string;

}

void GUI_Textbox::deactivate()
{
}




