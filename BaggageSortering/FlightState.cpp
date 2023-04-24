#include "Game.h"
#include "Airport.h"
#include "MenuButton.h"
#include "MenuTabButton.h"
#include "FlightState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "TextGameObject.h"
#include "FlightTextGameObject.h"
#include "CheckInState.h"
#include "TerminalState.h"
#include <iostream>

const std::string FlightState::s_menuID = "FLIGHT";

void FlightState::update() 
{
	m_clock->SetText(Timer::GetRealTimeString());
	m_clock->update();

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void FlightState::render()
{
	// Select the color for drawing. It is set to white here.
	SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0, 0, 0, 255);

	// Clear the entire screen to our selected color.
	SDL_RenderClear(TheGame::Instance()->getRenderer());

	m_clock->draw();

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool FlightState::onEnter()
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

	GameObject* headers = new TextGameObject(new LoaderParams(0, 240, 128, 64, "null"), "Departure time Destination Flight Terminal Baggage");

	GameObject* button1 = new MenuTabButton(new LoaderParams(0, 0, 128, 64, "checkintab"), changeCheckInDeskMenu);
	GameObject* button2 = new MenuTabButton(new LoaderParams(128, 0, 128, 64, "terminaltab"), changeTerminalMenu);
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
	m_gameObjects.push_back(headers);

	m_clock = static_cast<TextGameObject*>(clock);

	std::cout << "Entering menu state...\n";

	static_cast<MenuTabButton*>(button3)->SetIsActive(true);

	return true;
}

bool FlightState::onExit()
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

void FlightState::changeCheckInDeskMenu()
{
	TheGame::Instance()->getGameStateMachine()->queueState(new CheckInState());
}

void FlightState::changeTerminalMenu()
{
	TheGame::Instance()->getGameStateMachine()->queueState(new TerminalState());
}

void FlightState::changeFlightMenu()
{
	TheGame::Instance()->getGameStateMachine()->queueState(new FlightState());
}