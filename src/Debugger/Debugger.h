#ifndef _SWING_DEBUGGER_H_
#define _SWING_DEBUGGER_H_

#include "Session.h"
#include "DebugComponent.h"

namespace swing
{
	namespace vscode
	{
		class Debugger
		{
			Session* _session;

		public:
			Debugger();
			~Debugger();

			void RunDebugger();
		};
	}
}

#endif
