#include <Andromeda/Input/InputEnums.h>
#include <Andromeda/Input/SWITCH/GamepadDeviceSwitch.h>

#include <switch.h>

namespace Andromeda
{
	namespace Input
	{
		GamepadDeviceSwitch::GamepadDeviceSwitch()
		{
			
		}
		
		void GamepadDeviceSwitch::UpdateKesy(u64 kDown,u64 kUp)
		{
			_kDown = kDown;
			_kUp = kUp;
		}
		
		void GamepadDeviceSwitch::UpdateJoystick(HidAnalogStickState left,HidAnalogStickState right)
		{
			_leftJoy = left;
			_rightJoy = right;
		}

		float GamepadDeviceSwitch::LeftAnalogX()
		{
			return _leftJoy.x / 32760.0f;
		}
		
		float GamepadDeviceSwitch::LeftAnalogY()
		{
			return _leftJoy.y / 32760.0f;
		}

		float GamepadDeviceSwitch::RightAnalogX()
		{
			return _rightJoy.x / 32760.0f;
		}
		
		float GamepadDeviceSwitch::RightAnalogY()
		{
			return _rightJoy.y / 32760.0f;
		}

		bool GamepadDeviceSwitch::KeyDown(Gamepad::Button button)
		{
			//check states			
			switch(button)
			{
			case Gamepad::Left: 
				return (_kDown & HidNpadButton_Left);
				break;
			case Gamepad::Right: 
				return (_kDown & HidNpadButton_Right);
				break;
			case Gamepad::Up: 
				return (_kDown & HidNpadButton_Up);
				break;
			case Gamepad::Down: 
				return (_kDown & HidNpadButton_Down);
				break;
			case Gamepad::Triangle: 
				return (_kDown & HidNpadButton_X);
				break;
			case Gamepad::Square: 
				return (_kDown & HidNpadButton_Y);
				break;
			case Gamepad::Circle: 
				return (_kDown & HidNpadButton_A);
				break;
			case Gamepad::Cross: 
				return (_kDown & HidNpadButton_B);
				break;
			case Gamepad::LTrigger:
				return (_kDown & HidNpadButton_L);
				break;
			case Gamepad::RTrigger:
				return (_kDown & HidNpadButton_R);
				break;
			case Gamepad::Select:
				return (_kDown & HidNpadButton_Minus);
				break;
			case Gamepad::Start:
				return (_kDown & HidNpadButton_Plus);
				break;
			}
			
			
			float toleranceLevel = 0.3f;

			//specials
			switch (button)
			{
			case Gamepad::LAnalogLeft:
				return LeftAnalogX() < toleranceLevel * -1.0f;
				break;
			case Gamepad::LAnalogRight:
				return LeftAnalogX() > toleranceLevel;
				break;
			case Gamepad::LAnalogUp:
				return LeftAnalogY() > toleranceLevel;
				break;
			case Gamepad::LAnalogDown:
				return LeftAnalogY() < toleranceLevel * -1.0f;
				break;
			case Gamepad::LAnalogPushed:
				return (_kDown & HidNpadButton_StickL);
				break;
			}

			switch (button)
			{
			case Gamepad::RAnalogLeft:
				return RightAnalogX() < toleranceLevel * -1.0f;
				break;
			case Gamepad::RAnalogRight:
				return RightAnalogX() > toleranceLevel;
				break;
			case Gamepad::RAnalogUp:
				return RightAnalogY() > toleranceLevel;
				break;
			case Gamepad::RAnalogDown:
				return RightAnalogY() < toleranceLevel * -1.0f;
				break;
			case Gamepad::RAnalogPushed:
				return (_kDown & HidNpadButton_StickR);
				break;
			}

			return false;
		}

		bool GamepadDeviceSwitch::KeyUp(Gamepad::Button button)
		{
			//check states
			switch(button)
			{
			case Gamepad::Left: 
				return !(_kUp & HidNpadButton_Left);
				break;
			case Gamepad::Right: 
				return !(_kUp & HidNpadButton_Right);
				break;
			case Gamepad::Up: 
				return !(_kUp & HidNpadButton_Up);
				break;
			case Gamepad::Down: 
				return !(_kUp & HidNpadButton_Down);
				break;
			case Gamepad::Triangle: 
				return !(_kUp & HidNpadButton_X);
				break;
			case Gamepad::Square: 
				return !(_kUp & HidNpadButton_Y);
				break;
			case Gamepad::Circle: 
				return !(_kUp & HidNpadButton_A);
				break;
			case Gamepad::Cross: 
				return !(_kUp & HidNpadButton_B);
				break;
			case Gamepad::LTrigger:
				return !(_kUp & HidNpadButton_L);
				break;
			case Gamepad::RTrigger:
				return !(_kUp & HidNpadButton_R);
				break;
			case Gamepad::Select:
				return !(_kUp & HidNpadButton_Minus);
				break;
			case Gamepad::Start:
				return !(_kUp & HidNpadButton_Plus);
				break;
			}
			
			float toleranceLevel = 0.3f;

			//specials
			switch (button)
			{
			case Gamepad::LAnalogLeft:
				return !(LeftAnalogX() < toleranceLevel * -1.0f);
				break;
			case Gamepad::LAnalogRight:
				return !(LeftAnalogX() > toleranceLevel);
				break;
			case Gamepad::LAnalogUp:
				return !(LeftAnalogY() > toleranceLevel);
				break;
			case Gamepad::LAnalogDown:
				return !(LeftAnalogY() < toleranceLevel * -1.0f);
				break;
			case Gamepad::LAnalogPushed:
				return !(_kDown & HidNpadButton_StickL);
				break;
			}

			switch (button)
			{
			case Gamepad::RAnalogLeft:
				return !(RightAnalogX() < toleranceLevel * -1.0f);
				break;
			case Gamepad::RAnalogRight:
				return !(RightAnalogX() > toleranceLevel);
				break;
			case Gamepad::RAnalogUp:
				return !(RightAnalogY() > toleranceLevel);
				break;
			case Gamepad::RAnalogDown:
				return !(RightAnalogY() < toleranceLevel * -1.0f);
				break;
			case Gamepad::RAnalogPushed:
				return !(_kDown & HidNpadButton_StickR);
				break;
			}

			return false;
		}

	}
}
