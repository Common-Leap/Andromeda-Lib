#ifndef GamepadDeviceSwitch_H
#define GamepadDeviceSwitch_H

#include <Andromeda/Input/InputEnums.h>
#include <Andromeda/Input/GamepadDevice.h>

#include <switch.h>

namespace Andromeda
{
	namespace Input
	{
		class InputManagerSwitch;

		class GamepadDeviceSwitch : public GamepadDevice
		{
		
			GamepadDeviceSwitch();
			
			private:
			
			u64 _buttons;
			bool _stickPushed[Gamepad::Count];
			
			HidAnalogStickState _leftJoy;
			HidAnalogStickState _rightJoy;

			void UpdateStick(Gamepad::Button button, float value);

		public:

			float LeftAnalogX();
			float LeftAnalogY();

			float RightAnalogX();
			float RightAnalogY();

			bool KeyDown(Gamepad::Button button);
			bool KeyUp(Gamepad::Button button);
			
			void UpdateButtons(u64 buttons);
			void UpdateJoystick(HidAnalogStickState left,HidAnalogStickState right);

			friend class InputManagerSwitch;

		};
	}
}

#endif
