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
	for (int i = 0; i < m_checkInDeskButtons.size(); i++)
	{
		m_checkInDeskButtons[i]->update();
	}

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void CheckInState::render()
{
	// Select the color for drawing. It is set to white here.
	SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0, 0, 0, 255);

	// Clear the entire screen to our selected color.
	SDL_RenderClear(TheGame::Instance()->getRenderer());

	for (int i = 0; i < m_checkInDeskButtons.size(); i++)
	{
		m_checkInDeskButtons[i]->draw();
	}

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
	if (!TheTextureManager::Instance()->load("Assets/CheckInDeskOpenClose/off-button.png", "checkin-off", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/CheckInDeskOpenClose/on-button.png", "checkin-on", TheGame::Instance()->getRenderer()))
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

	// Create toggles to turn the checkin desks on and off
	for (int i = 0; i < Airport::GetCheckInDesks().size(); i++)
	{
		std::string state = Airport::GetCheckInDesks()[i]->IsOpen() ? "checkin-on" : "checkin-off"; // Set the state of the toggle to on or off depending on the state of the checkin desk
		MenuButton* toggle = new MenuButton(new LoaderParams(static_cast<TextGameObject*>(m_gameObjects[i])->GetWidth() * 3, 64 * (i + 1) - 10, 64, 64, state), toggleCheckInDesk, i); // Create the toggle
		m_checkInDeskButtons.push_back(toggle); // Add the toggle to the gameobjects vector
	}

	std::cout << "Entering menu state...\n";

	return true;
}

bool CheckInState::onExit()
{
	for (int i = 0; i < m_checkInDeskButtons.size(); i++)
	{
		m_checkInDeskButtons[i]->clean();
	}
	
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("checkintab");
	TheTextureManager::Instance()->clearFromTextureMap("terminaltab");
	TheTextureManager::Instance()->clearFromTextureMap("flighttab");
	TheTextureManager::Instance()->clearFromTextureMap("checkin-off");
	TheTextureManager::Instance()->clearFromTextureMap("checkin-on");

	std::cout << "Exiting menu state...\n";

	return true;
}

void CheckInState::changeCheckinDeskMenu()
{
	TheGame::Instance()->getGameStateMachine()->queueState(new CheckInState);
}

void CheckInState::changeTerminalMenu()
{
	TheGame::Instance()->getGameStateMachine()->queueState(new TerminalState);
}

void CheckInState::changeFlightMenu()
{
	TheGame::Instance()->getGameStateMachine()->queueState(new FlightState);
}

void CheckInState::toggleCheckInDesk(int deskNumber)
{
	Airport::GetCheckInDesks()[deskNumber]->ToggleOpen();
}