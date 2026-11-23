#include <Andromeda/Input/SWITCH/TouchDeviceSwitch.h>

#include <switch.h>

namespace Andromeda
{
	namespace Input
	{
		TouchDeviceSwitch::TouchDeviceSwitch()
		{
			_touchCount = 0;
		}

		int TouchDeviceSwitch::GetTouchCount()
		{
			HidTouchScreenState touchState;
			if (hidGetTouchScreenStates(&touchState, 1) == 0)
			{
				return 0;
			}

			return touchState.count;
		}

		int TouchDeviceSwitch::GetTouchX(int touchNumber)
		{
			HidTouchScreenState touchState;
			if (hidGetTouchScreenStates(&touchState, 1) == 0)
			{
				return 0;
			}

			if (touchNumber < 0 || touchNumber >= touchState.count)
			{
				return 0;
			}

			return touchState.touches[touchNumber].x;
		}

		int TouchDeviceSwitch::GetTouchY(int touchNumber)
		{
			HidTouchScreenState touchState;
			if (hidGetTouchScreenStates(&touchState, 1) == 0)
			{
				return 0;
			}

			if (touchNumber < 0 || touchNumber >= touchState.count)
			{
				return 0;
			}

			return touchState.touches[touchNumber].y;
		}

	}
}
