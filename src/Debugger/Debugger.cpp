#include "Debugger.h"
#include <thread>
#include <functional>
#include <iostream>
#include "Log.h"

namespace swing
{
	namespace vscode
	{
		Debugger::Debugger() : _session(new Session())
		{
		}

		Debugger::~Debugger()
		{
			if (_session != nullptr)
			{
				delete _session;
			}
		}

		void Debugger::RunDebugger()
		{
			_session->StartSession();
		}
	}
}
