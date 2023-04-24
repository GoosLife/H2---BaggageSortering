#include "Game.h"
#include "Airport.h"
#include "CheckInDesk.h"
#include "CheckInState.h"
#include "CheckInGameObject.h"
#include "TerminalState.h"
#include "TerminalGameObject.h"
#include "FlightState.h"
#include "FlightTextGameObject.h"
#include "MenuButton.h"
#include "MenuTabButton.h"
#include "MenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "Timer.h"
#include <iostream>
#include <vector>

const std::string MenuState::s_menuID = "TABMENU";

void MenuState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void MenuState::render()
{
	// Select the color for drawing. It is set to white here.
	SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0, 0, 0, 255);

	// Clear the entire screen to our selected color.
	SDL_RenderClear(TheGame::Instance()->getRenderer());

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool MenuState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/menutabbuttons/tab_checkindesks.png", "checkintab", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/menutabbuttons/tab_terminals.png", "terminaltab", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/menutabbuttons/tab_flights.png", "flighttab", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuTabButton(new LoaderParams(0,       0, 128, 64, "checkintab"), changeCheckinDeskMenu);
	GameObject* button2 = new MenuTabButton(new LoaderParams(128,     0, 128, 64, "terminaltab"), changeTerminalMenu);
	GameObject* button3 = new MenuTabButton(new LoaderParams(128 * 2, 0, 128, 64, "flighttab"), changeFlightMenu);

	for (int i = 0; i < Airport::GetCheckInDesks().size(); i++)
	{
		GameObject* terminal = new FlightTextGameObject(new LoaderParams(0, 64 * (i + 1), 128, 64, "null"), Airport::GetTerminals()[i]);
		m_gameObjects.push_back(terminal);
	}

	GameObject* clock = new TextGameObject(new LoaderParams(128 * 3, 0, 128, 64, "null"));
	static_cast<TextGameObject*>(clock)->SetText(Timer::GetRealTimeString());

	// Position the clock at the upper right corner of the window
	static_cast<TextGameObject*>(clock)->SetPosition(TheGame::Instance()->getGameWidth() - (static_cast<TextGameObject*>(clock)->GetWidth()), 16);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	m_gameObjects.push_back(button3);

	m_gameObjects.push_back(clock);

	std::cout << "Entering menu state...\n";

	static_cast<MenuTabButton*>(button1)->SetIsActive(true);
	
	return true;
}

bool MenuState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("checkintab");
	TheTextureManager::Instance()->clearFromTextureMap("terminaltab");
	TheTextureManager::Instance()->clearFromTextureMap("flighttab");

	std::cout << "Exiting menu state...\n";
	return true;
}

void MenuState::changeCheckinDeskMenu()
{
	TheGame::Instance()->getGameStateMachine()->queueState(new CheckInState);
}

void MenuState::changeTerminalMenu()
{
	TheGame::Instance()->getGameStateMachine()->queueState(new TerminalState);
}

void MenuState::changeFlightMenu()
{
	TheGame::Instance()->getGameStateMachine()->queueState(new FlightState);
}