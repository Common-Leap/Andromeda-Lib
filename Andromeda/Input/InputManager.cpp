

#include <Andromeda/Input/InputManager.h>

#include <Andromeda/Input/SWITCH/InputManagerSwitch.h>

namespace Andromeda
{
	namespace Input
	{
		InputManager* InputManager::_inputManager = 0;

		InputManager::InputManager()
		{
			
		}

		InputManager* InputManager::Instance()
		{
			if(_inputManager == 0)
			{

				{
					_inputManager = new InputManagerSwitch();
				}
			}

			return _inputManager;
		}

		KeyboardDevice* InputManager::GetKeyboardDevice(int deviceNumber)
		{
			std::string deviceName = "keyboard" + std::to_string(deviceNumber);

			if (_devices.find(deviceName) == _devices.end())
			{
				KeyboardDevice* device = _inputManager->GetKeyboard(deviceNumber);

				_devices.insert(std::pair<std::string, InputDevice*>(deviceName, device));

				return device;
			}
			else
			{
				return static_cast<KeyboardDevice*>(_devices[deviceName]);
			}
		}

		MouseDevice* InputManager::GetMouseDevice(int deviceNumber)
		{
			std::string deviceName = "mouse" + std::to_string(deviceNumber);

			if (_devices.find(deviceName) == _devices.end())
			{
				MouseDevice* device = _inputManager->GetMouse(deviceNumber);

				_devices.insert(std::pair<std::string, InputDevice*>(deviceName, device));

				return device;
			}
			else
			{
				return static_cast<MouseDevice*>(_devices[deviceName]);
			}
		}

		GamepadDevice* InputManager::GetGamepadDevice(int deviceNumber)
		{
			std::string deviceName = "gamepad" + std::to_string(deviceNumber);

			if (_devices.find(deviceName) == _devices.end())
			{
				GamepadDevice* device = _inputManager->GetGamepad(deviceNumber);

				_devices.insert(std::pair<std::string, InputDevice*>(deviceName, device));

				return device;
			}
			else
			{
				return static_cast<GamepadDevice*>(_devices[deviceName]);
			}
		}

		TouchDevice* InputManager::GetTouchDevice(int deviceNumber)
		{
			std::string deviceName = "touch" + std::to_string(deviceNumber);

			if (_devices.find(deviceName) == _devices.end())
			{
				TouchDevice* device = _inputManager->GetTouch(deviceNumber);

				_devices.insert(std::pair<std::string, InputDevice*>(deviceName, device));

				return device;
			}
			else
			{
				return static_cast<TouchDevice*>(_devices[deviceName]);
			}
		}

	}
}

