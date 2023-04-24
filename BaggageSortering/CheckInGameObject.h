#pragma once

#include "TextGameObject.h"
#include "CheckInDesk.h"

class CheckInGameObject : public TextGameObject
{
public:
	CheckInGameObject(const LoaderParams* pParams, CheckInDesk* desk);
	void draw();
	void update();
	void clean();

	int GetWidth();
	int GetHeight();

	void SetX(int x);
	void SetY(int y);

private:
	CheckInDesk* desk;
};