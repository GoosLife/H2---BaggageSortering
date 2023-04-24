#pragma once
#include "GameState.h"
#include "GameObject.h"
#include <vector>

class CheckInState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	
	static void changeCheckinDeskMenu();
	static void changeTerminalMenu();
	static void changeFlightMenu();

	virtual std::string getStateID() const { return s_checkInID; }

private:
	static const std::string s_checkInID;
	std::vector<GameObject*> m_gameObjects;
};

