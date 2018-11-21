#include "Input.h"
#include "Core.h"
#include <iostream>



namespace myengine
{
	Input::Input()
	{
		if (SDL_NumJoysticks() < 1)
		{
			std::cout << "No Joysticks connected" << std::endl;
			joystickConnected = false;
		}
		else
		{
			joystickConnected = true;
			Joystick = SDL_JoystickOpen(0);
			if (Joystick == NULL)
			{
				std::cout << "Warning: unable to read controller. SDL error: " << SDL_GetError() << std::endl;
			}
			else
			{
				std::cout << "Joystick found" << std::endl;
			}
		}
	}

	void Input::FreeJoystick()
	{
		if (joystickConnected)
		{
			SDL_JoystickClose(Joystick);
			Joystick = NULL;
		}
	}


	bool Input::getKey(ListedButtons _keycode)
	{
		return keys[_keycode];
	}

	bool Input::getMouseButton(MouseButtonStates _btn)
	{
		return mouseBtnStates[_btn];
	}

	void Input::setCorePtr(std::weak_ptr<Core> _core)
	{
		_corePtr = _core;
	}


	glm::vec2 Input::getMousePos()
	{
		return _mousePos;
	}

	bool Input::isJoystickConnected()
	{
		return joystickConnected;
	}

	void Input::UpdateLeftJoystick(glm::vec2 axes)
	{
		leftStickAxes = axes;
	}

	void Input::UpdateRightJoystick(glm::vec2 axes)
	{
		rightStickAxes = axes;
	}

	void Input::Tick()
	{
		if (!_queueKeyboardUpdate && !_queueJoystickUpdate && !_queueJoystickButtonUpdate && !_queueDpadUpdate && !_queueMouseMovementUpdate && !QueueMouseButtonUpdate)
		{
			return;
		}


		if (_queueKeyboardUpdate)
		{
			_queueKeyboardUpdate = false;

			SDL_KEYBOARDSTATE = SDL_GetKeyboardState(NULL);

			keys[FORWARD] = SDL_KEYBOARDSTATE[SDL_SCANCODE_W];

			keys[LEFT] = SDL_KEYBOARDSTATE[SDL_SCANCODE_A];

			keys[BACK] = SDL_KEYBOARDSTATE[SDL_SCANCODE_S];

			keys[RIGHT] = SDL_KEYBOARDSTATE[SDL_SCANCODE_D];

			keys[ESC] = SDL_KEYBOARDSTATE[SDL_SCANCODE_ESCAPE];

		}

		if (_queueMouseMovementUpdate)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			_mousePos = glm::vec2(x, y);
		}

		if (_queueMouseButtonUpdate)
		{
			mouseBtnStates[LEFT_MOUSE_BUTTON] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
			mouseBtnStates[RIGHT_MOUSE_BUTTON] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		}

		if(joystickConnected)
		{
			if (_queueJoystickUpdate)
			{
				_queueJoystickUpdate = false;

				leftStickAxes.x = SDL_JoystickGetAxis(Joystick, 0);
				leftStickAxes.y = SDL_JoystickGetAxis(Joystick, 1);
				leftTrigger = SDL_JoystickGetAxis(Joystick, 2);
				rightStickAxes.x = SDL_JoystickGetAxis(Joystick, 3);
				rightStickAxes.y = SDL_JoystickGetAxis(Joystick, 4);
				rightTrigger = SDL_JoystickGetAxis(Joystick, 5);
			}

			if (_queueJoystickButtonUpdate)
			{
				controllerBtns[A_BUTTON] = SDL_JoystickGetButton(Joystick, 0);
				controllerBtns[B_BUTTON] = SDL_JoystickGetButton(Joystick, 1);
				controllerBtns[X_BUTTON] = SDL_JoystickGetButton(Joystick, 2);
				controllerBtns[Y_BUTTON] = SDL_JoystickGetButton(Joystick, 3);
				controllerBtns[LB_BUTTON] = SDL_JoystickGetButton(Joystick, 4);
				controllerBtns[RB_BUTTON] = SDL_JoystickGetButton(Joystick, 5);
				controllerBtns[BACK_BUTTON] = SDL_JoystickGetButton(Joystick, 6);
				controllerBtns[START_BUTTON] = SDL_JoystickGetButton(Joystick, 7);
			}

			if (_queueDpadUpdate)
			{
				dpadStates[DPAD_LEFTUP] = SDL_JoystickGetHat(Joystick, SDL_HAT_LEFTUP);
				dpadStates[DPAD_UP] = SDL_JoystickGetHat(Joystick, SDL_HAT_UP);
				dpadStates[DPAD_RIGHTUP] = SDL_JoystickGetHat(Joystick, SDL_HAT_RIGHTUP);
				dpadStates[DPAD_LEFT] = SDL_JoystickGetHat(Joystick, SDL_HAT_LEFT);
				dpadStates[DPAD_CENTER] = SDL_JoystickGetHat(Joystick, SDL_HAT_CENTERED);
				dpadStates[DPAD_RIGHT] = SDL_JoystickGetHat(Joystick, SDL_HAT_RIGHT);
				dpadStates[DPAD_LEFTDOWN] = SDL_JoystickGetHat(Joystick, SDL_HAT_LEFTDOWN);
				dpadStates[DPAD_DOWN] = SDL_JoystickGetHat(Joystick, SDL_HAT_DOWN);
				dpadStates[DPAD_RIGHTDOWN] = SDL_JoystickGetHat(Joystick, SDL_HAT_RIGHTDOWN);
			}
		}
	}

	void Input::QueueKeyboardUpdate()
	{
		_queueKeyboardUpdate = true;
	}

	void Input::QueueControllerJoystickUpdate()
	{
		_queueJoystickUpdate = true;
	}

	void Input::QueueControllerButtonUpdate()
	{
		_queueJoystickButtonUpdate = true;
	}

	void Input::QueueControllerDpadUpdate()
	{
		_queueDpadUpdate = true;
	}

	void Input::QueueMouseMovementUpdate()
	{

	}

	void Input::QueueMouseButtonUpdate()
	{
		_queueMouseButtonUpdate = true;
	}


	glm::vec2 Input::GetJoystickAxis(ControllerAxes _axis)
	{
		if (_axis == LEFTSTICK)
		{
			return leftStickAxes;
		}
		else
		{
			return rightStickAxes;
		}

	}

}