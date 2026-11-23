#include <Andromeda/System/SWITCH/GameLoaderSwitch.h>
#include <Andromeda/Graphics/GL/RenderManagerGL3.h>
#include <Andromeda/FileSystem/FileManager.h>
#include <Andromeda/Input/InputManager.h>
#include <Andromeda/Utils/Logger.h>

#include <iostream>
#include <sys/stat.h>

namespace
{
	bool FileExists(const char* path)
	{
		struct stat st;
		return stat(path, &st) == 0;
	}
}

namespace Andromeda
{
	namespace System
	{
		GameLoaderSwitch::GameLoaderSwitch(GameManager* gameManager) : GameLoader(gameManager)
		{
			_renderManager = 0;
		}

		void GameLoaderSwitch::Run()
		{
			Result romfsResult = romfsInit();

			mkdir("sdmc:/switch", 0777);
			mkdir("sdmc:/switch/JellyCar", 0777);

			std::string mainDir = "";
			if (R_SUCCEEDED(romfsResult) && FileExists("romfs:/Assets/Jelly/scene_list.xml"))
			{
				mainDir = "romfs:/";
			}
			else if (FileExists("sdmc:/switch/JellyCar/Assets/Jelly/scene_list.xml"))
			{
				mainDir = "sdmc:/switch/JellyCar/";
			}

			FileSystem::FileManager::Instance()->SetMainDirPath(mainDir);
			FileSystem::FileManager::Instance()->SetSaveDirPath("sdmc:/switch/JellyCar/");

			Utils::Logger::Instance()->Log("Start\n");
			Utils::Logger::Instance()->Log("romfsInit: 0x%x\n", romfsResult);
			Utils::Logger::Instance()->Log("MainDir: %s\n", mainDir.c_str());

			//get render manager
			_renderManager = Graphics::RenderManager::Instance();

			if (!((Graphics::RenderManagerGL3*)_renderManager)->InitEgl(nwindowGetDefault()))
			{
				Utils::Logger::Instance()->Log("Failed to create gl window\n");

				if (R_SUCCEEDED(romfsResult))
				{
					romfsExit();
				}
				return;
			}

			//set configuration
			Utils::Logger::Instance()->Log("Config\n");
			_gameManager->Configure();

			Utils::Logger::Instance()->Log("Set window size\n");

			//get default monitor
			_renderManager->SetWindowSize(1280, 720);

			//set input manager
			Input::InputManager* intputManager = Input::InputManager::Instance();

			Utils::Logger::Instance()->Log("Init Render\n");

			//create renderer
			_renderManager->Init();

			Utils::Logger::Instance()->Log("Init Game Manager\n");

			//init game manager
			_gameManager->Init();

			Utils::Logger::Instance()->Log("Start loop\n");

			bool appletRunning = true;

			//main loop
			while (_gameManager->Running() && (appletRunning = appletMainLoop()))
			{
				//update input manager
				intputManager->Update();

				//game stuff
				_gameManager->HandleEvents();
				_gameManager->Update();
				_gameManager->Draw();

				//end frame
				_renderManager->SwapBuffers();
			}

			Utils::Logger::Instance()->Log("Loop end: running=%d applet=%d\n", _gameManager->Running(), appletRunning);

			// Proper teardown order for current libnx/OpenGL homebrew behavior.
			Utils::Logger::Instance()->Log("Switch cleanup: game manager\n");
			_gameManager->CleanUp();
			Utils::Logger::Instance()->Log("Switch cleanup: game manager done\n");

			Utils::Logger::Instance()->Log("Switch cleanup: render finish\n");
			_renderManager->Finish();
			Utils::Logger::Instance()->Log("Switch cleanup: render finish done\n");

			//log exit
			Utils::Logger::Instance()->Log("Exit\n");
			Utils::Logger::Instance()->Log("Switch return to libnx exit\n");
			return;
		}

	}
}
