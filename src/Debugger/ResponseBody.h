#ifndef _SWING_RESPONSE_BODY_H_
#define _SWING_RESPONSE_BODY_H_

#include "ProtocolMessage.h"
#include "DebugComponent.h"

namespace swing
{
	namespace vscode
	{
		class Capabilities : public ResponseBody 
		{
		public:
			bool _supportsConfigurationDoneRequest;
			bool _supportsFunctionBreakpoints;
			bool _supportsConditionalBreakpoints;
			bool _supportsEvaluateForHovers;
			std::vector<Dynamic> _exceptionBreakpointFilters;
		};

		class ErrorResponseBody : public ResponseBody
		{
		public:
			Message _error;

			ErrorResponseBody(Message error) :
				_error(error)
			{
			}
		};

		class StackTraceResponseBody : public ResponseBody
		{
		public:
			std::vector<StackFrame> _stackFrames;

			StackTraceResponseBody(std::vector<StackFrame>* frames = nullptr)
			{
				if (frames != nullptr)
					_stackFrames = *frames;
			}
		};

		class ScopesResponseBody : public ResponseBody
		{
		public:
			std::vector<Scope> _scopes;

			ScopesResponseBody(std::vector<Scope>* scps = nullptr) {
				if (scps != nullptr)
					_scopes = *scps;
			}
		};

		class VariablesResponseBody : public ResponseBody
		{
		public:
			std::vector<Variable> _variables;

			VariablesResponseBody(std::vector<Variable>* vars = nullptr) {
				if (vars != nullptr)
					_variables = *vars;
			}
		};

		class ThreadsResponseBody : public ResponseBody
		{
		public:
			std::vector<Thread> _threads;

			ThreadsResponseBody(std::vector<Thread>* vars = nullptr) {
				if (vars != nullptr)
					_threads = *vars;
			}
		};

		class EvaluateResponseBody : public ResponseBody
		{
		public:
			std::string _result;
			int _variablesReference;

			EvaluateResponseBody(std::string value, int reff = 0) {
				_result = value;
				_variablesReference = reff;
			}
		};

		class SetBreakpointsResponseBody : public ResponseBody
		{
		public:
			std::vector<Breakpoint> _breakpoints;

			SetBreakpointsResponseBody(std::vector<Breakpoint>* bpts = nullptr) {
				if (bpts != nullptr)
					_breakpoints = *bpts;
			}
		};
	}
}

#endif
