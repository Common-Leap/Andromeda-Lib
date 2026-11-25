#ifndef TouchDeviceSwitch_H
#define TouchDeviceSwitch_H

#include <Andromeda/Input/TouchDevice.h>

#include <switch.h>

namespace Andromeda
{
	namespace Input
	{
		class InputManagerSwitch;

		class TouchDeviceSwitch : public TouchDevice
		{
			TouchDeviceSwitch();
			
			HidTouchScreenState _state;

		public:

			void Update();

			int GetTouchCount();

			int GetTouchX(int touch);
			int GetTouchY(int touch);

			friend class InputManagerSwitch;
		};
	}
}

#endif
