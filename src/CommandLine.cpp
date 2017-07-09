#include "CommandLine.h"
#include <iostream>
#include "Debugger.h"

bool swing::HelpCommand::VerifierCommand(std::vector<std::string> args)
{
	// help command is always true
	return true;
}

int swing::HelpCommand::RunCommand()
{
	std::cout << "\n"   << "SWING Command Line Interface" << std::endl;
	std::cout << "\t"   << "-compile [-opt [level]] [-out [extension]] [project | sourcefiles] := Compile the project file(.swingproj) or source files(.swing)" << std::endl;
	std::cout << "\t\t" << "-opt [level] := level can be int value 0~4 which applies LLVM opt." << std::endl;
	std::cout << "\t\t" << "-out [extension] := Output file extension. It can be .ll .obj .o. Default value is .obj" << std::endl;
	std::cout << "\t"   << "-link [-out [extension]] [objective file] := Link SWING Stdlib and main project objective file." << std::endl;
	std::cout << "\t\t" << "-out [extension] := Output file extension. It can be .exe .out so on. Default value is .exe" << std::endl;
	std::cout << "\t"   << "-create [\"project\" | \"source\"] [folder] [name] := Create SWING project file or source file at [folder], file name with [name]" << std::endl;
	std::cout << "\t"   << "-debug := SWING Debugger mode on. SWING support Visual Studio Code for debugging and etc." << std::endl;
	return 0;
}

bool swing::CompileCommand::VerifierCommand(std::vector<std::string> args)
{
	return true;
}

int swing::CompileCommand::RunCommand()
{
	return 0;
}

bool swing::LinkCommand::VerifierCommand(std::vector<std::string> args)
{
	return true;
}

int swing::LinkCommand::RunCommand()
{
	return 0;
}

bool swing::DebugCommand::VerifierCommand(std::vector<std::string> args)
{
	return true;
}

int swing::DebugCommand::RunCommand()
{
	std::ios_base::sync_with_stdio(true);

	vscode::Debugger debugger;

	debugger.RunDebugger();

	return 0;
}

bool swing::CreateCommand::VerifierCommand(std::vector<std::string> args)
{
	return true;
}

int swing::CreateCommand::RunCommand()
{
	return 0;
}
