#include <Andromeda/System/MemoryManager.h>

#include <Andromeda/System/SWITCH/MemoryManagerSwitch.h>

namespace Andromeda
{
	namespace System
	{
		MemoryManager* MemoryManager::_memoryManager = 0;

		MemoryManager::MemoryManager()
		{

		}

		MemoryManager* MemoryManager::Instance()
		{
			if (_memoryManager == 0	)
			{

                {
                    _memoryManager = new MemoryManagerSwitch();
                }
				
			}

			return _memoryManager;
		}
	}
}
