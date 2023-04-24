#pragma once

#include "GameObject.h"

class TextGameObject : public GameObject
{
public:
	TextGameObject(const LoaderParams* pParams, std::string text = "") : GameObject(pParams), x(pParams->getX()), y(pParams->getY()), width(pParams->getWidth()), height(pParams->getHeight()), text(text) {}
	void draw();
	void update();
	void clean();

protected:
	int x;
	int y;
	int width;
	int height;
	std::string text;
};

