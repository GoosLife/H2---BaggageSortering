#include "Game.h"
#include "MenuButton.h"
#include "FlightState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include <iostream>

const std::string FlightState::s_menuID = "FLIGHT";

void FlightState::update() 
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void FlightState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool FlightState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/btnPlay.png", "playbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load("assets/btnExit.png", "exitbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"), s_menuToPlay);
	GameObject* button2 = new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"), s_exitFromMenu);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "Entering menu state...\n";

	return true;
}

bool FlightState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

	std::cout << "Exiting menu state...\n";
	return true;
}

void FlightState::s_menuToPlay()
{
	TheGame::Instance()->getGameStateMachine()->changeState(new PlayState());
}

void FlightState::s_exitFromMenu()
{
	TheGame::Instance()->quit();
}
