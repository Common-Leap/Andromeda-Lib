#include <Andromeda/Utils/Logger.h>

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <Andromeda/FileSystem/FileManager.h>

#if defined(ANDROMEDA_FILE_LOG) && (ANDROMEDA_FILE_LOG != 0)
#define ANDROMEDA_LOG_FILE_OUTPUT 1
#else
#define ANDROMEDA_LOG_FILE_OUTPUT 0
#endif

namespace Andromeda
{
	namespace Utils
	{
		Logger* Logger::_logger = 0;

		Logger::Logger()
		{
			_active = true;
			_debug = false;

#ifdef _DEBUG
			_debug = true;
#endif // DEBUG

			_debug = true;

			std::string logTime = GetTime();

			//create filename
			_fileName = "Info" + logTime + ".txt";
			_errorFileName = "Error" + logTime + ".txt";

		}

		Logger* Logger::Instance()
		{
			if (_logger == 0)
			{
				_logger = new Logger();
			}

			return _logger;
		}

		void Logger::Log(const char* message, ...)
		{
			if (!_active)
			{
				return;
			}

#if ANDROMEDA_LOG_FILE_OUTPUT
			va_list argList;
			char cbuffer[1024];
			va_start(argList, message);
			vsnprintf(cbuffer, 1024, message, argList);
			va_end(argList);

			FileSystem::BaseFile* file = FileSystem::FileManager::Instance()->GetFile(_fileName,true);

			if (file == 0)
				return;

			if (!file->Open(FileSystem::Append, FileSystem::Text))
			{
				delete file;
				return;
			}

			file->Write(cbuffer, sizeof(char), strlen(cbuffer));
			delete file;
#endif
		}

		void Logger::Info(const char* file, const char* function, int line, const char *message, ...)
		{
			if (!_active)
			{
				return;
			}

#if ANDROMEDA_LOG_FILE_OUTPUT
			va_list argList;
			char cbuffer[1024];
			va_start(argList, message);
			vsnprintf(cbuffer, 1024, message, argList);
			va_end(argList);

			std::string logMessage = "";

			if (_debug)
			{
				logMessage = GetTime() + " " + std::string(file) + "(" + to_string(line) + ") " + std::string(function) + " : " + std::string(cbuffer);
			}
			else
			{
				logMessage = std::string(cbuffer);
			}

			FileSystem::BaseFile* outFile = FileSystem::FileManager::Instance()->GetFile(_fileName, true);

			if (outFile == 0)
				return;

			if (!outFile->Open(FileSystem::Append, FileSystem::Text))
			{
				delete outFile;
				return;
			}

			outFile->Write((void*)logMessage.c_str(), sizeof(char), logMessage.length());
			delete outFile;
#endif
		}

		void Logger::Error(const char* file, const char* function,int line, const char *message, ...)
		{
			if (!_active)
			{
				return;
			}

#if ANDROMEDA_LOG_FILE_OUTPUT
			va_list argList;
			char cbuffer[1024];
			va_start(argList, message);
			vsnprintf(cbuffer, 1024, message, argList);
			va_end(argList);

			std::string logMessage = "";

			if (_debug)
			{
				logMessage = GetTime() + " " + std::string(file) + "(" + to_string(line) + ") " + std::string(function) + " : " + std::string(cbuffer);
			}
			else
			{
				logMessage = std::string(cbuffer);
			}

			FileSystem::BaseFile* outFile = FileSystem::FileManager::Instance()->GetFile(_errorFileName, true);

			if (outFile == 0)
				return;

			if (!outFile->Open(FileSystem::Append, FileSystem::Text))
			{
				delete outFile;
				return;
			}

			outFile->Write((void*)logMessage.c_str(), sizeof(char), logMessage.length());
			delete outFile;
#endif
		}

		void Logger::NetLog(const char *message, ...)
		{
			va_list argList;
			char cbuffer[1024];
			va_start(argList, message);
			vsnprintf(cbuffer, 1024, message, argList);
			va_end(argList);

		}

		void Logger::SetActive(bool state)
		{
			_active = state;
		}

		bool Logger::IsActive()
		{
			return _active;
		}

		std::string Logger::GetTime()
		{
			time_t     now = time(0);
			struct tm  tstruct;
			char       buf[80];
			tstruct = *localtime(&now);
			// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
			// for more information about date/time format
			strftime(buf, sizeof(buf), "%Y_%m_%d_%H_%M_%S", &tstruct);

			return buf;
		}

	}
}
