#include "MenuTabButton.h"

MenuTabButton::MenuTabButton(const LoaderParams* pParams, void(*callback)()) : MenuButton(pParams, callback) {}

void MenuTabButton::draw()
{
	MenuButton::draw();
}

void MenuTabButton::update()
{
	if (isActive)
	{
		if (m_currentFrame != CLICKED)
		{
			m_currentFrame = CLICKED;
		}
	}
	else
	{
		MenuButton::update();
	}
}

void MenuTabButton::clean()
{
	MenuButton::clean();
}