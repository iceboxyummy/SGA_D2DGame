// Logsystem.cpp

#include"stdafx.h"
#include "Logsystem.h"

using namespace std;

namespace Logsystem
{
	TARGET target = TARGET::ALL;

	std::filesystem::path log_path = "./Mylog.txt";

	bool is_first = true;

	void Print(LPCSTR log);	
}

namespace Logsystem
{
	void SetTarget(const TARGET target)
	{
		Logsystem::target = target;
	}

	void SetLog(const std::string type, const std::string function, const std::string file, const std::string line, const std::string format, ...)
	{
		string log = "";
		va_list list = nullptr;
		va_start(list, format);
		{
			size_t size = _vscprintf(format.c_str(), list) + sizeof('\0');

			char* message = new char[size];
			vsprintf_s(message, size, format.c_str(), list);

			log += "CALLER\t: ";
			log += function + "(";
			log += file + ",";
			log += line + ")\n";
			log += type + "\t";

			log += string(message) + "\n\n";

			delete[] message;
		}
		va_end(list, format);

		Print(log.c_str());
	}

	void Print(LPCSTR log)
	{
		switch (target)
		{
		case Logsystem::TARGET::ALL:

		case Logsystem::TARGET::CONSOLE:
		{
			printf("%s", log);

			if(target!=TARGET::ALL)break;
		}

		case Logsystem::TARGET::FILE:
		{
			ofstream file;

			if (is_first == true)
			{
				file.open(log_path, ios::out);
					is_first = false;
			}

			else
			file.open(log_path,ios::app);

			file << log;

			file.close();

			if(target!=TARGET::ALL)break;
		}
		}
	}
}