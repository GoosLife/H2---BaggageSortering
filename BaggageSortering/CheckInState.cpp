#include "Game.h"
#include "Airport.h"
#include "CheckInDesk.h"
#include "CheckInState.h"
#include "CheckInGameObject.h"
#include "TerminalState.h"
#include "FlightState.h"
#include "MenuButton.h"
#include "MenuTabButton.h"
#include "MenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include <iostream>
#include <vector>

const std::string CheckInState::s_checkInID = "CHECKIN";

void CheckInState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void CheckInState::render()
{
	// Select the color for drawing. It is set to red here.
	SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0, 0, 0, 255);

	// Clear the entire screen to our selected color.
	SDL_RenderClear(TheGame::Instance()->getRenderer());

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool CheckInState::onEnter()
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

	GameObject* button1 = new MenuTabButton(new LoaderParams(0, 0, 128, 64, "checkintab"), changeCheckinDeskMenu);
	GameObject* button2 = new MenuTabButton(new LoaderParams(128, 0, 128, 64, "terminaltab"), changeTerminalMenu);
	GameObject* button3 = new MenuTabButton(new LoaderParams(128 * 2, 0, 128, 64, "flighttab"), changeFlightMenu);

	for (int i = 0; i < Airport::GetCheckInDesks().size(); i++)
	{
		GameObject* desk = new CheckInGameObject(new LoaderParams(0, 64 * (i + 1), 128, 64, "null"), Airport::GetCheckInDesks()[i]);
		m_gameObjects.push_back(desk);
	}

	static_cast<MenuTabButton*>(button1)->SetIsActive(true);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	m_gameObjects.push_back(button3);

	std::cout << "Entering menu state...\n";

	return true;
}

bool CheckInState::onExit()
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

void CheckInState::changeCheckinDeskMenu()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new CheckInState);
}

void CheckInState::changeTerminalMenu()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new TerminalState);
}

void CheckInState::changeFlightMenu()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new FlightState);
}