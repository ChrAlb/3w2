#include "stdafx.h"
#include "GUI_Textbox.h"



void GUI_Textbox::draw()
{
	
	sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
}

void GUI_Textbox::update()
{
}

void GUI_Textbox::acitvate(Vector2f pos, Vector2f size, String string)
{
	g_type = TextField;
	g_window.setPosition(pos);
	g_window.setSize(size);
}

void GUI_Textbox::deactivate()
{
}




