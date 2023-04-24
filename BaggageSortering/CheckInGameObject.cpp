#include "CheckInGameObject.h"
#include "TextGameObject.h"
#include "SDL.h"

#include <iostream>
#include <sstream>

CheckInGameObject::CheckInGameObject(const LoaderParams* pParams, CheckInDesk* desk) : TextGameObject(pParams)
{
	this->desk = desk;

	this->update(); // Update the text to the correct value on creation

	delete pParams;
}

void CheckInGameObject::draw()
{
	TextGameObject::draw();
}

void CheckInGameObject::update()
{
	std::stringstream ss;
	ss << "Check in desk " << desk->GetID() + 1 << " - " << desk->GetBaggageCount() << "/" << CheckInDesk::GetMaxBaggage() << " baggage";

	text = ss.str();
}

void CheckInGameObject::clean()
{
	// Clean the inherited class
	TextGameObject::clean();
}

// Return the inherited width from TextGameObject
int CheckInGameObject::GetWidth()
{
	return width;
}

// Return the inherited height from TextGameObject
int CheckInGameObject::GetHeight()
{
	return height;
}

void CheckInGameObject::SetX(int x)
{
	this->x = x;
}

void CheckInGameObject::SetY(int y)
{
	this->y = y;
}