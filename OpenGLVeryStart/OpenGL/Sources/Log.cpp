#include "Log.hpp"

namespace Core::Debug
{
	std::ofstream Log::fs;

	void Log::DebugLog(std::string format, int line, std::string namefile)
	{
		Log::Print(namefile + std::to_string(line) +" : "+ format);
	}
	 void Log::OpenFile(std::filesystem::path const& filename)
	{
		 if (!fs.is_open())
		 {
			fs.open(filename);  
			Core::Debug::Log::Print("File is open\n");
		}
	}

	void Log::CloseFile()
	{
		fs.close();
	}

	void Log::Print(std::string format)
	{
		std::cout << format;
		if (fs.is_open())
			fs << format;
	}

}