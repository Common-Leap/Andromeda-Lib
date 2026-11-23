#include <Andromeda/System/Timer.h>
#include <time.h>

namespace Andromeda
{
	namespace System
	{
		Timer::Timer()
		{
            msec = 0.0f;
			
            gettimeofday(&lastTime, NULL);

		}

		float Timer::GetDelta()
		{
            timeval curTime;
            gettimeofday(&curTime, NULL);

            double time_in_mill = (curTime.tv_sec) * 1000 + (curTime.tv_usec) / 1000;
            double time_in_mill_last = (lastTime.tv_sec) * 1000 + (lastTime.tv_usec) / 1000;

            msec = (time_in_mill - time_in_mill_last);

            msec = msec * 0.001f;
            lastTime = curTime;

            if (msec < 0.0f)
                return 0.0f;

			return msec;
		}
	}
}
