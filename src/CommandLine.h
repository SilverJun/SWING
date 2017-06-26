#ifndef _SWING_COMMAND_LINE_H_
#define _SWING_COMMAND_LINE_H_
#include <vector>

namespace swing
{
	class CommandLine
	{
	public:
		virtual ~CommandLine() {}
		/**
		 * \brief check correct paramater function
		 * \param args args.
		 * \return if it is correct paramater, it will return true
		 */
		virtual bool VerifierCommand(std::vector<std::string> args) = 0;
		virtual int RunCommand() = 0;
	};

	class HelpCommand : public CommandLine
	{
	public:
		~HelpCommand() {}
		bool VerifierCommand(std::vector<std::string> args) override;
		int RunCommand() override;
	};

	class CompileCommand : public CommandLine
	{
	public:
		~CompileCommand() {}
		bool VerifierCommand(std::vector<std::string> args) override;
		int RunCommand() override;
	};

	class LinkCommand : public CommandLine
	{
	public:
		~LinkCommand() {}
		bool VerifierCommand(std::vector<std::string> args) override;
		int RunCommand() override;
	};

	class DebugCommand : public CommandLine
	{
	public:
		~DebugCommand() {}
		bool VerifierCommand(std::vector<std::string> args) override;
		int RunCommand() override;
	};

	class CreateCommand : public CommandLine
	{
	public:
		~CreateCommand() {}
		bool VerifierCommand(std::vector<std::string> args) override;
		int RunCommand() override;
	};
}
#endif
