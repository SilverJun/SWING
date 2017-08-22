#ifndef _SWING_CLI_H_
#define _SWING_CLI_H_

#include <vector>

#include "CommandLine.h"

namespace swing
{
	class SwingCLI
	{
		/// Program Path not include /swing.exe
		std::string _outPath;
		std::vector<std::string> _args;
		CommandLine* _commandLines;

	public:
		SwingCLI(int argc, char* argv[]);
		~SwingCLI();

		void InitProgram();
		int RunProgram();
	};
}

#endif
