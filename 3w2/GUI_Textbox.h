#pragma once
#include "GUI_Manager.h"

class GUI_Textbox : public GUI_Manager
{
public:
	void draw();
	void update();
	void acitvate(Vector2f pos, Vector2f size, String string);
	void deactivate();

private:
};