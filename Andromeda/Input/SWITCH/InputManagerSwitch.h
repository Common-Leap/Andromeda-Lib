#ifndef InputManagerSwitch_H
#define InputManagerSwitch_H

#include <Andromeda/Input/InputManager.h>
#include <Andromeda/Input/SWITCH/GamepadDeviceSwitch.h>
#include <Andromeda/Input/SWITCH/TouchDeviceSwitch.h>

namespace Andromeda
{
	namespace Input
	{
		class InputManagerSwitch : public InputManager
		{
			private:
			
				GamepadDeviceSwitch* _gamepad;
				TouchDeviceSwitch* _touch;
				PadState _pad;
			
			public:
			
				InputManagerSwitch();

				int GetKayboardCount();
				int GetMouseCount();
				int GetGamepadCount();
				int GetTouchDeviceCount();

				void Update();

				KeyboardDevice* GetKeyboard(int deviceNumber);
				MouseDevice* GetMouse(int deviceNumber);
				GamepadDevice* GetGamepad(int deviceNumber);
				TouchDevice* GetTouch(int deviceNumber);
		};
	}
}

#endif
