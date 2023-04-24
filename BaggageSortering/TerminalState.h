#pragma once

#include "GameState.h"
#include "GameObject.h"

#include <string>
#include <vector>

class TerminalState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_terminalID; }
private:
	static const std::string s_terminalID;
	std::vector<GameObject*> m_gameObjects;

	static void changeCheckinDeskMenu();
	static void changeTerminalMenu();
	static void changeFlightMenu();
};

