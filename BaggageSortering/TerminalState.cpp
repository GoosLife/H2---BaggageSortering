#include "TerminalState.h"
#include "CheckInState.h"
#include "FlightState.h"
#include "MenuState.h"
#include "Game.h"
#include "MenuTabButton.h"
#include "TextureManager.h"

const std::string TerminalState::s_terminalID = "TERMINAL";

void TerminalState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void TerminalState::render()
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

bool TerminalState::onEnter()
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

	/*
	for (int i = 0; i < Airport::GetTerminals().size(); i++)
	{
		GameObject* terminal = new TerminalGameObject(new LoaderParams(0, 64 * (i + 1), 128, 64, "null"), Airport::GetTerminals()[i]);
		m_gameObjects.push_back(terminal);
	}
	*/

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	m_gameObjects.push_back(button3);

	static_cast<MenuTabButton*>(button2)->SetIsActive(true);

	return true;
}

bool TerminalState::onExit()
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

void TerminalState::changeCheckinDeskMenu()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new CheckInState);
}

void TerminalState::changeTerminalMenu()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new TerminalState);
}

void TerminalState::changeFlightMenu()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new FlightState);
}
