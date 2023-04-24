#pragma once
#include "GameObject.h"
#include "GameState.h"
#include "TextGameObject.h"
#include <vector>

class FlightState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; }

private:
	static const std::string s_menuID;
	std::vector<GameObject*> m_gameObjects;
	TextGameObject* m_clock;

	static void changeCheckInDeskMenu();
	static void changeTerminalMenu();
	static void changeFlightMenu();
};

