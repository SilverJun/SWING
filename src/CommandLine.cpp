#include "CommandLine.h"
#include <iostream>
//#include "Debugger.h"
#include "SwingCompiler.h"

namespace swing
{


	bool HelpCommand::VerifierCommand(std::vector<std::string> args)
	{
		// help command is always true
		return true;
	}

	int HelpCommand::RunCommand()
	{
		std::cout << std::endl;
		std::cout << "\n" << "SWING Command Line Interface" << std::endl;
		std::cout << std::endl;
		std::cout << "\t" << "-compile [-opt [level]] [-out [extension]] [project | sourcefiles]\n\tCompile the project file(.swingproj) or source files(.swing)" << std::endl;
		std::cout << "\t\t" << "-opt [level]\n\t\tlevel can be int value 0~4 which applies LLVM opt." << std::endl;
		std::cout << "\t\t" << "-out [extension]\n\t\tOutput file extension. It can be .ll .obj .o. Default value is .obj" << std::endl;
		std::cout << std::endl;
		std::cout << "\t" << "-link [-out [extension]] [objective file]\n\tLink SWING Stdlib and main project objective file." << std::endl;
		std::cout << "\t\t" << "-out [extension]\n\t\tOutput file extension. It can be .exe .out so on. Default value is .exe" << std::endl;
		std::cout << std::endl;
		std::cout << "\t" << "-create [\"project\" | \"source\"] [folder] [name]\n\tCreate SWING project file or source file at [folder], file name with [name]" << std::endl;
		std::cout << std::endl;
		std::cout << "\t" << "-debug\n\tSWING Debugger mode on. SWING support Visual Studio Code for debugging and etc." << std::endl;
		return 0;
	}

	bool CompileCommand::VerifierCommand(std::vector<std::string> args)
	{
		/// TODO : 기능구현
		_args = args;
		_optLevel = stoi(_args[2]);
		_outputFormat = _args[4];
		_projectPath = _args[5];
		return true;
	}

	int CompileCommand::RunCommand()
	{
		g_SwingCompiler->CompileProject(new Project(_projectPath), _optLevel, _outputFormat);
		return 0;
	}

	bool LinkCommand::VerifierCommand(std::vector<std::string> args)
	{
		return true;
	}

	int LinkCommand::RunCommand()
	{
		return 0;
	}

	bool DebugCommand::VerifierCommand(std::vector<std::string> args)
	{
		return true;
	}

	int DebugCommand::RunCommand()
	{
		std::ios_base::sync_with_stdio(true);

		//vscode::Debugger debugger;
		//debugger.RunDebugger();

		return 0;
	}

	bool CreateCommand::VerifierCommand(std::vector<std::string> args)
	{
		return true;
	}

	int CreateCommand::RunCommand()
	{
		return 0;
	}
}