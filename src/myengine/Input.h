#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <memory>
#include <map>
#include <SDL2/SDL.h>
#include "glm.hpp"

namespace frontier 
{
	class Core;
	

	class Input
	{
	public:
		enum ListedButtons
		{
			FORWARD,
			BACK,
			LEFT,
			RIGHT,
			UP,
			DOWN,
			SHOOT,
			ESC,
			NUM_OF_BUTTONS
		};

		enum ControllerAxes
		{
			LEFTSTICK,
			RIGHTSTICK
		};

		enum ControllerButtons
		{
			A_BUTTON,
			B_BUTTON,
			X_BUTTON,
			Y_BUTTON,
			LB_BUTTON,
			RB_BUTTON,
			BACK_BUTTON,
			START_BUTTON,
			NUM_OF_CONTROLLER_BUTTONS
		};

		enum DpadStates
		{
			DPAD_LEFTUP,
			DPAD_UP,
			DPAD_RIGHTUP,
			DPAD_LEFT,
			DPAD_CENTER,
			DPAD_RIGHT,
			DPAD_LEFTDOWN,
			DPAD_DOWN,
			DPAD_RIGHTDOWN,
			NUM_OF_STATES
		};

		enum MouseButtonStates
		{
			LEFT_MOUSE_BUTTON,
			RIGHT_MOUSE_BUTTON,
			NUM_OF_MOUSE_BUTTON_STATES
		};

		Input();
		
		bool getKey(ListedButtons _keycode);
		bool getMouseButton(MouseButtonStates _btn);
		glm::vec2 getMousePos();
		bool getJoystickButton(ControllerButtons _btn);
		bool getJoystickDpadState(DpadStates _state);
		glm::vec2 GetJoystickAxis(ControllerAxes _axis);

		void setCorePtr(std::weak_ptr<Core> _core);
		bool isJoystickConnected();
		void FreeJoystick();
		void UpdateLeftJoystick(glm::vec2 axes);
		void UpdateRightJoystick(glm::vec2 axes);
		void Tick();

		void QueueMouseMovementUpdate();
		void QueueMouseButtonUpdate();
		void QueueKeyboardUpdate();
		void QueueControllerJoystickUpdate();
		void QueueControllerButtonUpdate();
		void QueueControllerDpadUpdate();


		

	private:
		std::weak_ptr<Core> _corePtr;
		//std::map<int, bool> _keyboard;

		//keyboard info
		const Uint8* SDL_KEYBOARDSTATE;
		uint8_t keys[NUM_OF_BUTTONS - 1] = { false };
		uint8_t controllerBtns[NUM_OF_CONTROLLER_BUTTONS - 1] = { false };
		uint8_t dpadStates[NUM_OF_STATES - 1] = { false };
		uint8_t mouseBtnStates[NUM_OF_MOUSE_BUTTON_STATES - 1] = { false };
		glm::vec2 _mousePos;

		//joystick info (evetually make this a struct and have an array of pointer structs for multiple controllers
		bool joystickConnected;
		SDL_Joystick* Joystick;
		glm::vec2 leftStickAxes;
		glm::vec2 rightStickAxes;
		Sint16 leftTrigger;
		Sint16 rightTrigger;
		bool _queueKeyboardUpdate, _queueJoystickUpdate, _queueJoystickButtonUpdate, _queueDpadUpdate, _queueMouseMovementUpdate, _queueMouseButtonUpdate;
	};


}