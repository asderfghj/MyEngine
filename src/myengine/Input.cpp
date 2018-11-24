#include "Input.h"
#include "Core.h"
#include <iostream>



namespace frontier
{
	Input::Input()
	{
		if (SDL_NumJoysticks() < 1)
		{
			std::cout << "No Joysticks connected" << std::endl;
			m_joystickConnected = false;
		}
		else
		{
			m_joystickConnected = true;
			m_joystick = SDL_JoystickOpen(0);
			if (m_joystick == NULL)
			{
				std::cout << "Warning: unable to read controller. SDL error: " << SDL_GetError() << std::endl;
			}
			else
			{
				std::cout << "Joystick found" << std::endl;
			}
		}
	}



	bool Input::GetKey(ListedButtons _keycode)
	{
		return m_keys[_keycode];
	}

	bool Input::GetMouseButton(MouseButtonStates _btn)
	{
		return m_mouseBtnStates[_btn];
	}

	glm::vec2 Input::GetMousePos()
	{
		return m_mousePos;
	}

	bool Input::GetJoystickButton(ControllerButtons _btn)
	{
		return m_controllerBtns[_btn];
	}

	bool Input::GetJoystickDpadState(DpadStates _state)
	{
		return m_dpadStates[_state];
	}

	glm::vec2 Input::GetJoystickAxis(ControllerAxes _axis)
	{
		if (_axis == LEFTSTICK)
		{
			return m_leftStickAxes;
		}
		else
		{
			return m_rightStickAxes;
		}

	}

	void Input::SetCorePtr(std::weak_ptr<Core> _core)
	{
		_corePtr = _core;
	}

	bool Input::IsJoystickConnected()
	{
		return m_joystickConnected;
	}

	void Input::FreeJoystick()
	{
		if (m_joystickConnected)
		{
			SDL_JoystickClose(m_joystick);
			m_joystick = NULL;
		}
	}

	void Input::UpdateLeftJoystick(glm::vec2 _axes)
	{
		m_leftStickAxes = _axes;
	}

	void Input::UpdateRightJoystick(glm::vec2 _axes)
	{
		m_rightStickAxes = _axes;
	}

	void Input::Tick()
	{
		if (!m_queueKeyboardUpdate && !m_queueJoystickUpdate && !m_queueJoystickButtonUpdate && !m_queueDpadUpdate && !m_queueMouseMovementUpdate && !m_queueMouseButtonUpdate)
		{
			return;
		}


		if (m_queueKeyboardUpdate)
		{
			m_queueKeyboardUpdate = false;

			m_sdlKeyboardState = SDL_GetKeyboardState(NULL);

			m_keys[FORWARD] = m_sdlKeyboardState[SDL_SCANCODE_W];

			m_keys[LEFT] = m_sdlKeyboardState[SDL_SCANCODE_A];

			m_keys[BACK] = m_sdlKeyboardState[SDL_SCANCODE_S];

			m_keys[RIGHT] = m_sdlKeyboardState[SDL_SCANCODE_D];

			m_keys[SHOOT] = m_sdlKeyboardState[SDL_SCANCODE_Q];

			m_keys[ESC] = m_sdlKeyboardState[SDL_SCANCODE_ESCAPE];

		}

		if (m_queueMouseMovementUpdate)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			m_mousePos = glm::vec2(x, y);
		}

		if (m_queueMouseButtonUpdate)
		{
			m_mouseBtnStates[LEFT_MOUSE_BUTTON] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
			m_mouseBtnStates[RIGHT_MOUSE_BUTTON] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		}

		if(m_joystickConnected)
		{
			if (m_queueJoystickUpdate)
			{
				m_queueJoystickUpdate = false;

				m_leftStickAxes.x = SDL_JoystickGetAxis(m_joystick, 0);
				m_leftStickAxes.y = SDL_JoystickGetAxis(m_joystick, 1);
				m_leftTrigger = SDL_JoystickGetAxis(m_joystick, 2);
				m_rightStickAxes.x = SDL_JoystickGetAxis(m_joystick, 3);
				m_rightStickAxes.y = SDL_JoystickGetAxis(m_joystick, 4);
				m_rightTrigger = SDL_JoystickGetAxis(m_joystick, 5);
			}

			if (m_queueJoystickButtonUpdate)
			{
				m_controllerBtns[A_BUTTON] = SDL_JoystickGetButton(m_joystick, 0);
				m_controllerBtns[B_BUTTON] = SDL_JoystickGetButton(m_joystick, 1);
				m_controllerBtns[X_BUTTON] = SDL_JoystickGetButton(m_joystick, 2);
				m_controllerBtns[Y_BUTTON] = SDL_JoystickGetButton(m_joystick, 3);
				m_controllerBtns[LB_BUTTON] = SDL_JoystickGetButton(m_joystick, 4);
				m_controllerBtns[RB_BUTTON] = SDL_JoystickGetButton(m_joystick, 5);
				m_controllerBtns[BACK_BUTTON] = SDL_JoystickGetButton(m_joystick, 6);
				m_controllerBtns[START_BUTTON] = SDL_JoystickGetButton(m_joystick, 7);
			}

			if (m_queueDpadUpdate)
			{
				m_dpadStates[DPAD_LEFTUP] = SDL_JoystickGetHat(m_joystick, SDL_HAT_LEFTUP);
				m_dpadStates[DPAD_UP] = SDL_JoystickGetHat(m_joystick, SDL_HAT_UP);
				m_dpadStates[DPAD_RIGHTUP] = SDL_JoystickGetHat(m_joystick, SDL_HAT_RIGHTUP);
				m_dpadStates[DPAD_LEFT] = SDL_JoystickGetHat(m_joystick, SDL_HAT_LEFT);
				m_dpadStates[DPAD_CENTER] = SDL_JoystickGetHat(m_joystick, SDL_HAT_CENTERED);
				m_dpadStates[DPAD_RIGHT] = SDL_JoystickGetHat(m_joystick, SDL_HAT_RIGHT);
				m_dpadStates[DPAD_LEFTDOWN] = SDL_JoystickGetHat(m_joystick, SDL_HAT_LEFTDOWN);
				m_dpadStates[DPAD_DOWN] = SDL_JoystickGetHat(m_joystick, SDL_HAT_DOWN);
				m_dpadStates[DPAD_RIGHTDOWN] = SDL_JoystickGetHat(m_joystick, SDL_HAT_RIGHTDOWN);
			}
		}
	}

	void Input::QueueMouseMovementUpdate()
	{
		m_queueMouseMovementUpdate = true;
	}

	void Input::QueueMouseButtonUpdate()
	{
		m_queueMouseButtonUpdate = true;
	}

	void Input::QueueKeyboardUpdate()
	{
		m_queueKeyboardUpdate = true;
	}

	void Input::QueueControllerJoystickUpdate()
	{
		m_queueJoystickUpdate = true;
	}

	void Input::QueueControllerButtonUpdate()
	{
		m_queueJoystickButtonUpdate = true;
	}

	void Input::QueueControllerDpadUpdate()
	{
		m_queueDpadUpdate = true;
	}

}