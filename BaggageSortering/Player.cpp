#include <SDL.h>

#include "InputHandler.h"
#include "Player.h"

#include <iostream>

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Player::draw() 
{
	SDLGameObject::draw();
}

void Player::update() 
{
	// Reset velocity on each frame
	m_velocity.setX(0);
	m_velocity.setY(0);
	
	// Get movement from input
	handleInput();

	m_currentFrame = (((SDL_GetTicks() / 100) % 3));
	SDLGameObject::update();
}

void Player::clean() 
{
	SDLGameObject::clean();
}

void Player::handleInput()
{
	Vector2D* target = TheInputHandler::Instance()->getMousePosition();
	
	m_velocity = *target - m_position;
	m_velocity /= 50;
}