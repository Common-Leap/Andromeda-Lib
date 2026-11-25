#include <Andromeda/Input/InputEnums.h>
#include <Andromeda/Input/SWITCH/GamepadDeviceSwitch.h>

#include <switch.h>

namespace Andromeda
{
	namespace Input
	{
		namespace
		{
			//a stick counts as pushed past the first value and as released below the second one
			const float STICK_PUSH = 0.5f;
			const float STICK_RELEASE = 0.35f;

			const float STICK_MAX = 32767.0f;

			u64 ButtonMask(Gamepad::Button button)
			{
				switch (button)
				{
				case Gamepad::Left:          return HidNpadButton_Left;
				case Gamepad::Right:         return HidNpadButton_Right;
				case Gamepad::Up:            return HidNpadButton_Up;
				case Gamepad::Down:          return HidNpadButton_Down;
				case Gamepad::Triangle:      return HidNpadButton_X;
				case Gamepad::Square:        return HidNpadButton_Y;
				case Gamepad::Circle:        return HidNpadButton_A;
				case Gamepad::Cross:         return HidNpadButton_B;
				case Gamepad::LTrigger:      return HidNpadButton_L;
				case Gamepad::RTrigger:      return HidNpadButton_R;
				case Gamepad::ZLTrigger:     return HidNpadButton_ZL;
				case Gamepad::ZRTrigger:     return HidNpadButton_ZR;
				case Gamepad::Select:        return HidNpadButton_Minus;
				case Gamepad::Start:         return HidNpadButton_Plus;
				case Gamepad::LAnalogPushed: return HidNpadButton_StickL;
				case Gamepad::RAnalogPushed: return HidNpadButton_StickR;
				default:                     return 0;
				}
			}
		}

		GamepadDeviceSwitch::GamepadDeviceSwitch()
		{
			_buttons = 0;

			_leftJoy.x = 0;
			_leftJoy.y = 0;
			_rightJoy.x = 0;
			_rightJoy.y = 0;

			for (int i = 0; i < Gamepad::Count; i++)
			{
				_stickPushed[i] = false;
			}
		}

		void GamepadDeviceSwitch::UpdateButtons(u64 buttons)
		{
			_buttons = buttons;
		}

		void GamepadDeviceSwitch::UpdateStick(Gamepad::Button button, float value)
		{
			_stickPushed[button] = value > (_stickPushed[button] ? STICK_RELEASE : STICK_PUSH);
		}

		void GamepadDeviceSwitch::UpdateJoystick(HidAnalogStickState left, HidAnalogStickState right)
		{
			_leftJoy = left;
			_rightJoy = right;

			UpdateStick(Gamepad::LAnalogLeft, -LeftAnalogX());
			UpdateStick(Gamepad::LAnalogRight, LeftAnalogX());
			UpdateStick(Gamepad::LAnalogUp, LeftAnalogY());
			UpdateStick(Gamepad::LAnalogDown, -LeftAnalogY());

			UpdateStick(Gamepad::RAnalogLeft, -RightAnalogX());
			UpdateStick(Gamepad::RAnalogRight, RightAnalogX());
			UpdateStick(Gamepad::RAnalogUp, RightAnalogY());
			UpdateStick(Gamepad::RAnalogDown, -RightAnalogY());
		}

		float GamepadDeviceSwitch::LeftAnalogX()
		{
			return _leftJoy.x / STICK_MAX;
		}

		float GamepadDeviceSwitch::LeftAnalogY()
		{
			return _leftJoy.y / STICK_MAX;
		}

		float GamepadDeviceSwitch::RightAnalogX()
		{
			return _rightJoy.x / STICK_MAX;
		}

		float GamepadDeviceSwitch::RightAnalogY()
		{
			return _rightJoy.y / STICK_MAX;
		}

		bool GamepadDeviceSwitch::KeyDown(Gamepad::Button button)
		{
			return (_buttons & ButtonMask(button)) != 0 || _stickPushed[button];
		}

		bool GamepadDeviceSwitch::KeyUp(Gamepad::Button button)
		{
			return !KeyDown(button);
		}
	}
}
