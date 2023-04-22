#pragma once
#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);
	void draw();
	void update();
	void clean();

private:
	void handleInput();
};

