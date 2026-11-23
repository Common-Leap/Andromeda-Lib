#include <Andromeda/FileSystem/FileManager.h>
#include <Andromeda/Utils/Logger.h>

#include <Andromeda/FileSystem/Stdio/StdioFile.h>
#include <Andromeda/FileSystem/Stdio/StdioDirectory.h>

namespace Andromeda
{
	namespace FileSystem
	{
		FileManager* FileManager::_instance = 0;

		FileManager::FileManager()
		{
			_mainDirPath = "";
			_instance = 0;			
		}

		FileManager::FileManager(std::string dirPath)
		{
			_mainDirPath = "";
			_instance = 0;
		}

		FileManager* FileManager::Instance()
		{
			if (_instance == 0)
			{
				_instance = new FileManager();
			}

			return _instance;
		}

		//set main location of file system
		void FileManager::SetMainDirPath(const std::string &pathName)
		{
			_mainDirPath = pathName;
		}

		//get main location of file system
		std::string FileManager::GetMainDirPath()
		{
			return _mainDirPath;
		}

		void FileManager::SetSaveDirPath(const std::string &pathName)
		{
			_saveDirPath = pathName;
		}

		std::string FileManager::GetSaveDirPath()
		{
			return _saveDirPath;
		}

		//get directory
		BaseDirectory* FileManager::GetDirectory(std::string fileName)
		{
			std::string loadName = _mainDirPath + fileName;
			BaseDirectory* directory;

			{
				directory = new StdioDirectory(loadName);
			}

			return directory;
		}

		//check if file exists
		bool FileManager::FileExists(const std::string &fileName)
		{
			bool exist = false;

			BaseFile* file = GetFile(fileName);

			file->Open(Read, Binary);

			exist = file->Exist();

			//delete will also close file
			delete file;

			return exist;
		}

		//get file
		BaseFile *FileManager::GetFile(std::string fileName, bool saveLocation)
		{
			std::string loadName = "";

			if (saveLocation)
			{
				loadName = _saveDirPath + fileName;
			}
			else
			{
				loadName = _mainDirPath + fileName;
			}

			BaseFile* newFile;

			{
				newFile = new StdioFile(fileName, loadName);
			}

			return newFile;
		}
	}
}
