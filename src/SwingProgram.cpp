#include "SwingProgram.h"

#include "crefile.hpp"

swing::SwingProgram::SwingProgram(int argc, char* argv[]) : _args(argc)
{ 
	_outPath = crefile::dirname(argv[0]);

	/// char* array -> string vector
	for (int i = 1; i < argc; i++)
	{
		_args.push_back(std::string(argv[i]));
	}

	_commandLines.push_back(CompileCommand());
	_commandLines.push_back(LinkCommand());
	_commandLines.push_back(DebugCommand());
	_commandLines.push_back(CreateCommand());
}

swing::SwingProgram::~SwingProgram()
{
}

void swing::SwingProgram::InitProgram()
{
	/// Environment variable Setting.
	if (std::getenv("SWING_PATH") == nullptr)
	{
#ifdef _WINDOWS
		_putenv_s("SWING_PATH", _outPath.c_str());
#else
		std::setenv("SWING_PATH", _outPath.c_str());
#endif
	}

	/// Command Line verification check
	
}

int swing::SwingProgram::RunProgram()
{
	/*/// Ready some variables.
	swing::Project* proj = nullptr;

	/// Compile Command
	std::string projectFilePath = parser.get<std::string>("compile");
	if (projectFilePath != "")
	{
		proj = new swing::Project(projectFilePath);

		/// opt 적용

		g_SwingCompiler.CompileProject(proj);
		return 0;
	}

	/// Link Command
	std::vector<std::string> objFiles = parser.get<std::vector<std::string>>("link");
	if (!objFiles.empty())
	{
		/// Link Object Files to one Executive File.
		return 0;
	}

	/// Debug Mode Command
	bool isDebugMode = parser.get<bool>("debug");
	if (isDebugMode)
	{
		/// Debug Mode On
		/// Wait for Packet.
		std::cout << "Debug Mode!!" << std::endl;
		Debugger debugger;
		///debugger.RunDebugger();

		while (true)
		{

		}
	}

	/// Create Command
	std::vector<std::string> createFile = parser.get<std::vector<std::string>>("create");
	if (!createFile.empty())
	{
		/// Create swing File.
	}
	*/
	return 0;
}
