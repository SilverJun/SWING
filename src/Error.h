#ifndef _SWING_ERROR_H_
#define _SWING_ERROR_H_

#include <string>

namespace swing
{
	struct Error
	{
		int _line;
		std::string _description;

		Error(int line, std::string desc) : _line(line), _description(desc) {}
		Error(std::string desc) :_line(-1), _description(desc) {}
		
		std::string what() const
		{
			return _line != -1 ? "line:" + std::to_string(_line) + " " + _description : _description;
		}
	};
}

#endif
