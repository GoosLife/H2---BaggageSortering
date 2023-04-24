#pragma once
#include "MenuButton.h"

class MenuTabButton : public MenuButton
{
public:
	MenuTabButton(const LoaderParams* pParams, void (*callback)());
	virtual void draw();
	virtual void update();
	virtual void clean();

	void SetIsActive(bool state) { isActive = state; }

private:
	bool isActive;
};

