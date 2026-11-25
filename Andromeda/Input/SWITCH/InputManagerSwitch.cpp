#include <Andromeda/Input/SWITCH/InputManagerSwitch.h>
#include <Andromeda/Input/SWITCH/GamepadDeviceSwitch.h>
#include <Andromeda/Input/SWITCH/TouchDeviceSwitch.h>

#include <switch.h>

namespace Andromeda
{
	namespace Input
	{
		InputManagerSwitch::InputManagerSwitch()
		{
			padConfigureInput(1, HidNpadStyleSet_NpadStandard);
			padInitializeDefault(&_pad);

			hidInitializeTouchScreen();

			_gamepad = new GamepadDeviceSwitch();
			_touch = new TouchDeviceSwitch();
		}
		
		
		int InputManagerSwitch::GetKayboardCount()
		{
			return 0;
		}

		int InputManagerSwitch::GetMouseCount()
		{
			return 0;
		}

		int InputManagerSwitch::GetGamepadCount()
		{
			return 1;
		}

		int InputManagerSwitch::GetTouchDeviceCount()
		{
			return 1;
		}

		void InputManagerSwitch::Update()
		{
			padUpdate(&_pad);
			u64 kHeld = padGetButtons(&_pad);

			HidAnalogStickState pos_left = padGetStickPos(&_pad, 0);
			HidAnalogStickState pos_right = padGetStickPos(&_pad, 1);
			
			//update Ggamepad device
			_gamepad->UpdateButtons(kHeld);
			_gamepad->UpdateJoystick(pos_left,pos_right);

			//update touch device
			_touch->Update();
		}

		KeyboardDevice* InputManagerSwitch::GetKeyboard(int deviceNumber)
		{
			return 0;
		}

		MouseDevice* InputManagerSwitch::GetMouse(int deviceNumber)
		{
			return 0;
		}

		GamepadDevice* InputManagerSwitch::GetGamepad(int deviceNumber)
		{
			return _gamepad;
		}

		TouchDevice* InputManagerSwitch::GetTouch(int deviceNumber)
		{
			return _touch;
		}
	}
}
