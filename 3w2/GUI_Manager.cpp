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

	



}

GUI_Manager::~GUI_Manager()
{

	for (iter = GUI_objects.begin(); iter != GUI_objects.end();)
	{
		delete (*iter);
		iter = GUI_objects.erase(iter);
	}
}

void GUI_Manager::register_GUI()
{
	textbox = new GUI_Textbox();
	textbox->acitvate({ 0,0 }, { 50,20 }, "Test");
	GUI_objects.push_back(textbox);

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
