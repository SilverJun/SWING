#include "DebugComponent.h"

#include "crefile.hpp"
#undef max

namespace swing
{
	namespace vscode
	{
		Message::Message(int id, std::string format, Dynamic variables, bool user, bool telemetry):
			_id(id), _format(format), _variables(variables), _showUser(user), _sendTelemetry(telemetry)
		{
		}

		Scope::Scope(std::string name, int variablesReference, bool expensive):
			_name(name), _variablesReference(variablesReference), _expensive(expensive)
		{
		}

		Variable::Variable(std::string name, std::string value, std::string type, int variablesReference):
			_name(name), _value(value), _type(type), _variablesReference(variablesReference)
		{
		}

		Thread::Thread(int id, std::string name):
			_id(id)
		{
			if (name.empty())
			{
				_name = std::string("Thread ") + std::to_string(id);
			}
			else
			{
				_name = name;
			}
		}

		Source::Source(std::string name, std::string path, int sourceReference)
		{
			_name = name;
			_path = path;
			_sourceReference = sourceReference;
		}

		Source::Source(std::string path, int sourceReference)
		{
			_name = crefile::fileName(path);
			_path = path;
			_sourceReference = sourceReference;
		}

		Source* Source::Create(std::string name, std::string path, int sourceReference)
		{
			if (std::string(name).empty() || std::string(path).empty())
				return nullptr;

			return new Source(name, path, sourceReference);
		}

		StackFrame::StackFrame(int id, std::string name, Source* source, int line, int column):
			_id(id), _source(source), _name(name)
		{
			// These should NEVER be negative
			_line = std::max(0, line);
			_column = std::max(0, column);

			// issue #21 - Don't provide source object when it doesn't make sense
			if (_line == 0 || _source == nullptr || std::string(_source->_name).empty() || std::string(_source->_path).empty())
			{
				_presentationHint = "subtle";
			}
			else
			{
				this->_presentationHint = "normal";
			}
		}

		Breakpoint::Breakpoint(bool verified, int line):
			_verified(verified), _line(line)
		{
		}
	}
}
