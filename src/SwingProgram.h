#ifndef _SWING_PROGRAM_H_
#define _SWING_PROGRAM_H_

#include <vector>
#include <functional>
#include <unordered_map>

#include "CommandLine.h"

namespace swing
{
	class SwingProgram
	{
		/// Program Path not include /swing.exe
		std::string _outPath;
		std::vector<std::string> _args;
		std::vector<CommandLine> _commandLines;

	public:
		SwingProgram(int argc, char* argv[]);
		~SwingProgram();

		void InitProgram();
		int RunProgram();
	};
}

#endif
