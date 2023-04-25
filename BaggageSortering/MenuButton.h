#pragma once
#include "SDLGameObject.h"

class MenuButton : public SDLGameObject
{
public:
	MenuButton(const LoaderParams* pParams, void (*callback)());

	// Create a constructor that takes a callback function with an int parameter
	MenuButton(const LoaderParams* pParams, void (*callback)(int), int parameter);

	virtual void draw();
	virtual void update();
	virtual void clean();

protected:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	void (*m_callback)();
	void (*m_callback_param)(int);
	int m_parameter;
	bool m_bReleased;
};