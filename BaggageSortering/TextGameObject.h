#pragma once

#include "GameObject.h"

class TextGameObject : public GameObject
{
public:
	TextGameObject(const LoaderParams* pParams, std::string text = "") : GameObject(pParams), x(pParams->getX()), y(pParams->getY()), width(pParams->getWidth()), height(pParams->getHeight()), text(text) {}
	void draw();
	void update();
	void clean();

	int GetWidth() { return width; }
	int GetHeight() { return height; }

	void SetX(int x) { this->x = x; }
	void SetY(int y) { this->y = y; }
	void SetPosition(int x, int y) { this->x = x; this->y = y; }

	void SetText(std::string text) { this->text = text; }

protected:
	int x;
	int y;
	int width;
	int height;
	std::string text;
};