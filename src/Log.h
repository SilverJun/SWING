#ifndef _SWING_LOG_H_
#define _SWING_LOG_H_

#include <string>

namespace swing
{
	class Log
	{
	public:
		static std::string make_daytime_string();
		static void Message(std::string msg);
	};

}

#endif
