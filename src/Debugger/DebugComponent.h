#ifndef _SWING_DEBUG_COMPONENT_H_
#define _SWING_DEBUG_COMPONENT_H_

#include <string>
#include <algorithm>
#include "ProtocolMessage.h"

namespace swing
{
	namespace vscode
	{
		class Message
		{
		public:
			int _id;
			std::string _format;
			Dynamic _variables;
			bool _showUser;
			bool _sendTelemetry;

			Message(int id, std::string format, Dynamic variables, bool user = true, bool telemetry = false);
		};

		class Scope
		{
		public:
			std::string _name;
			int _variablesReference;
			bool _expensive;

			Scope(std::string name, int variablesReference, bool expensive = false);
		};

		class Variable
		{
		public:
			std::string _name;
			std::string _value;
			std::string _type;
			int _variablesReference;

			Variable(std::string name, std::string value, std::string type, int variablesReference = 0);
		};

		class Thread
		{
		public:
			int _id;
			std::string _name;

			Thread(int id, std::string name);
		};

		class Source
		{
		public:
			std::string _name;
			std::string _path;
			int _sourceReference;

		private:
			Source(std::string name, std::string path, int sourceReference = 0);
			Source(std::string path, int sourceReference = 0);
		public:
			static Source* Create(std::string name, std::string path, int sourceReference = 0);
		};

		class StackFrame
		{
		public:
			int _id;
			Source* _source;
			int _line;
			int _column;
			std::string _name;
			std::string _presentationHint;

			StackFrame(int id, std::string name, Source* source, int line, int column);
		};

		class Breakpoint
		{
		public:
			bool _verified;
			int _line;

			Breakpoint(bool verified, int line);
		};
	}
}

#endif
