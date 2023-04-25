#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams* pParams, void (callback)()) : SDLGameObject(pParams), m_callback(callback)
{
	m_currentFrame = MOUSE_OUT;
}

MenuButton::MenuButton(const LoaderParams* pParams, void(callback)(int), int parameter) : SDLGameObject(pParams), m_callback_param(callback), m_parameter(parameter)
{
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
	SDLGameObject::draw();
}

void MenuButton::update()
{
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

	if (pMousePos->getX() > (m_position.getX()) &&
		pMousePos->getX() < (m_position.getX() + m_width) &&
		pMousePos->getY() > (m_position.getY()) &&
		pMousePos->getY() < (m_position.getY() + m_height))
	{
		m_currentFrame = MOUSE_OVER;

		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;

			if (m_callback != NULL)
			{
				m_callback();
			}
			else
			{
				m_callback_param(m_parameter);
			}

			m_bReleased = false;
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}