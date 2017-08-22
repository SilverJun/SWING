#include "SwingCLI.h"

#include "SwingCompiler.h"
//#include "crefile.hpp"
//#include "Debugger.h"
#include <iostream>

namespace swing
{

	SwingCLI::SwingCLI(int argc, char* argv[]) : _args(), _commandLines(nullptr)
	{
		//_outPath = crefile::dirname(argv[0]);
		std::string exe(argv[0]);
		auto iter = exe.rbegin();
		for (; iter != exe.rend(); ++iter)
		{
			if (*iter == '\\')
				break;
		}
		exe = std::string(exe.begin(), iter.base());

		g_SwingCompiler->_swingPath = exe;
		/// char* array -> string vector
		for (int i = 1; i < argc; i++)
		{
			_args.push_back(std::string(argv[i]));
		}
	}

	SwingCLI::~SwingCLI()
	{
	}

	void SwingCLI::InitProgram()
	{
		/// Environment variable Setting.
		/*if (std::getenv("SWING_PATH") == nullptr)
		{
#ifdef _WINDOWS
			_putenv_s("SWING_PATH", _outPath.c_str());
#else
			std::setenv("SWING_PATH", _outPath.c_str());
#endif
		}*/

		/// Command Line
		if (_args.empty())
		{
			_commandLines = new HelpCommand();
		}
		else if (_args[0] == "-build")
		{
			_commandLines = new BuildCommand();
		}
		else if (_args[0] == "-compile")
		{
			_commandLines = new CompileCommand();
		}
		else if (_args[0] == "-link")
		{
			_commandLines = new LinkCommand();
		}
		/*else if (_args[0] == "-debug")
		{
			_commandLines = new DebugCommand();
		}
		else if (_args[0] == "-create")
		{
			_commandLines = new CreateCommand();
		}*/
		else
		{
			_commandLines = new HelpCommand();
		}
	}

	int SwingCLI::RunProgram()
	{
		if (!_commandLines->VerifierCommand(_args))
			return -1;

		return _commandLines->RunCommand();
	}

}