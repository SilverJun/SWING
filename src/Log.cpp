#include "Log.h"
#include <fstream>
#include <ctime>
#include <iostream>

namespace swing
{
	std::string Log::make_daytime_string()
	{
		using namespace std; // For time_t, time and ctime;
		time_t now = time(nullptr);
		string str(ctime(&now));
		return str.substr(0, str.length() - 1);
	}

	void Log::Message(std::string msg)
	{
		std::fstream logFile("C:/Users/SilverJun/Desktop/swinglog.txt", std::ios_base::out | std::ios_base::app);
		logFile << make_daytime_string() << " Message (" << msg.length() << ") : " << msg << std::endl;
		
		logFile.close();
	}
}

