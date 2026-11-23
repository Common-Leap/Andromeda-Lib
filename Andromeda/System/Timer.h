#ifndef Timer_H
#define Timer_H

#include <ctime>

#include <sys/time.h>

namespace Andromeda
{
	namespace System
	{
		class Timer
		{
		private:

            timeval lastTime;

			float msec;

		public:

			Timer();

			float GetDelta();
		};
	}
}

#endif