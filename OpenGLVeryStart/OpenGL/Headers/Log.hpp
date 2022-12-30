#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <ratio>
#include<string>

namespace Core::Debug
{
	 class Log
	{
		public:
			static std::ofstream fs;
			static void DebugLog(std::string format, int line, std::string name);
			static void OpenFile(std::filesystem::path const& filename);
			static void CloseFile();
			static void Print(std::string format);
			//template <typename T, typename... Types>
			//void print(T var1, Types... var2);
	};
}
