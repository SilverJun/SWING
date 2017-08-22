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
		std::cout << "\t" << "-build [sourcefiles] -out [folder path]\n\tBuild the source file(.swing) to target executive file." << std::endl;
		std::cout << "\t\t" << "-out [extension]\n\t\toutput folder path." << std::endl;
		std::cout << std::endl;
		std::cout << "\t" << "-compile [sourcefiles] -out [folder path]\n\tCompile the source file(.swing)" << std::endl;
		std::cout << "\t\t" << "-out [extension]\n\t\toutput folder path." << std::endl;
		std::cout << std::endl;
		std::cout << "\t" << "-link [objective file] -out [folder path]\n\tLink SWING Stdlib and source objective file." << std::endl;
		std::cout << "\t\t" << "-out [extension]\n\t\toutput folder path." << std::endl;
		std::cout << std::endl;
		/*
		std::cout << "\t" << "-create [\"project\" | \"source\"] [folder] [name]\n\tCreate SWING project file or source file at [folder], file name with [name]" << std::endl;
		std::cout << std::endl;
		std::cout << "\t" << "-debug\n\tSWING Debugger mode on. SWING support Visual Studio Code for debugging and etc." << std::endl;
		*/
		return 0;
	}

	bool BuildCommand::VerifierCommand(std::vector<std::string> args)
	{
		//C:\Users\SilverJun\Desktop\SWING\bin\Debug\swing.exe -build C:\Users\SilverJun\Desktop\SWING\example\HelloSwing\main.swing -out C:\Users\SilverJun\Desktop\SWING\example\HelloSwing\
		
		_args = args;

		if (args.size() < 2)
			return false;
		_sourcePath = _args[1];
		if (args.size() < 4)
			return true;
		_output = _args[3];

		return true;
	}

	int BuildCommand::RunCommand()
	{
		g_SwingCompiler->BuildSource(_sourcePath, _output);
		return 0;
	}

	bool CompileCommand::VerifierCommand(std::vector<std::string> args)
	{
		_args = args;
		if (args.size() < 2)
			return false;
		_sourcePath = _args[1];
		if (args.size() < 4)
			return true;
		_output = _args[3];

		return true;
	}

	int CompileCommand::RunCommand()
	{
		g_SwingCompiler->CompileSource(_sourcePath, _output);
		return 0;
	}

	bool LinkCommand::VerifierCommand(std::vector<std::string> args)
	{
		_args = args;
		if (args.size() < 2)
			return false;
		_sourcePath = _args[1];
		if (args.size() < 4)
			return true;
		_output = _args[3];

		return true;
	}

	int LinkCommand::RunCommand()
	{
		g_SwingCompiler->LinkSource(_sourcePath, _output);
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