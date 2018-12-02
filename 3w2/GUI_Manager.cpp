#include "stdafx.h"
#include "GUI_Manager.h"


GUI_Manager::GUI_Manager()
{
sf:Color none = sf::Color(0, 0, 0);


g_eventType = None;
g_type = TextField;

g_pos = { 0,0 };
g_size = {0, 0};
g_backgroundcolor = none;
g_fontcolor = none;
g_windowtext = "";

	GUI_ElementType g_type;
	GUI_EventType   g_eventType;

	RectangleShape g_window;
	Vector2f       g_pos;
	Vector2f       g_size;

	Color          g_backgroundcolor;
	Color          g_fontcolor;
	String         g_windowtext;


}

GUI_Manager::~GUI_Manager()
{

	for (iter = GUI_objects.begin(); iter != GUI_objects.end();)
	{
		delete (*iter);
		iter = GUI_objects.erase(iter);
	}
}

void GUI_Manager::update_GUI()
{
	for (iter = GUI_objects.begin(); iter != GUI_objects.end(); ++iter)
		(*iter)->update();

}

void GUI_Manager::draw_GUI(RenderWindow & window)
{
	RenderWindow  twindow;
	
	for (iter = GUI_objects.begin(); iter != GUI_objects.end(); ++iter)
		(*iter)->draw(twindow);
}
