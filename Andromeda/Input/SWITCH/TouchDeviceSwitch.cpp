#include <Andromeda/Input/SWITCH/TouchDeviceSwitch.h>

#include <string.h>

namespace Andromeda
{
	namespace Input
	{
		TouchDeviceSwitch::TouchDeviceSwitch()
		{
			memset(&_state, 0, sizeof(_state));
		}

		void TouchDeviceSwitch::Update()
		{
			if (hidGetTouchScreenStates(&_state, 1) == 0)
			{
				_state.count = 0;
			}
		}

		int TouchDeviceSwitch::GetTouchCount()
		{
			return _state.count;
		}

		int TouchDeviceSwitch::GetTouchX(int touchNumber)
		{
			if (touchNumber < 0 || touchNumber >= (int)_state.count)
			{
				return 0;
			}

			return _state.touches[touchNumber].x;
		}

		int TouchDeviceSwitch::GetTouchY(int touchNumber)
		{
			if (touchNumber < 0 || touchNumber >= (int)_state.count)
			{
				return 0;
			}

			return _state.touches[touchNumber].y;
		}
	}
}
