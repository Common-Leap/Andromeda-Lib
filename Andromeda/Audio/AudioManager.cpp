#include <Andromeda/Audio/AudioManager.h>

#include <Andromeda/Audio/Sdl/SdlAudioManager.h>

namespace Andromeda
{
	namespace Audio
	{
		AudioManager* AudioManager::_audioManager = 0;

		AudioManager::AudioManager()
		{
			
		}

		AudioManager* AudioManager::Instance()
		{
			if (_audioManager == 0)
			{

				{
					_audioManager = new SdlAudioManager();
				}
				
				_audioManager->Init();
			}

			return _audioManager;
		}

		void AudioManager::Shutdown()
		{
			if (_audioManager != 0)
			{
				delete _audioManager;
				_audioManager = 0;
			}
		}
	}
}
