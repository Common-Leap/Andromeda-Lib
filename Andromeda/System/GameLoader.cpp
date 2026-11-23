#include <Andromeda/System/GameLoader.h>

#include <Andromeda/System/SWITCH/GameLoaderSwitch.h>

namespace Andromeda
{
	namespace System
	{
		GameLoader::GameLoader(GameManager* gameManager)
		{
			_gameManager = gameManager;
		}

		GameLoader* GameLoader::Create(GameManager* gameManager)
		{
			GameLoader* _loader = 0;

            {
                _loader = new GameLoaderSwitch(gameManager);
            }
			
			return _loader;
		}
	}
}
