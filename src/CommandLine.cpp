#include "CommandLine.h"

bool swing::HelpCommand::VerifierCommand(std::vector<std::string> args)
{
	// help command is always true
	return true;
}

int swing::HelpCommand::RunCommand()
{
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
