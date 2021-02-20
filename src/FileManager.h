#pragma once
#include <fstream>
#include <string>

namespace StarBangBang
{
	class FileManager
	{
	public:
		static std::ifstream& ReadFile(std::string const path);
		static std::ofstream& WriteFile(std::string const path);
	};

}