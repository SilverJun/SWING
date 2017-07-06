#ifndef _SWING_RESPONSE_BODY_H_
#define _SWING_RESPONSE_BODY_H_

#include "ProtocolMessage.h"

namespace swing
{
	namespace vscode
	{
		class InitializedEvent : public Event
		{
		public:
			InitializedEvent() : 
				Event("initialized") { }
		};

		class StoppedEvent : public Event
		{
		public:
			StoppedEvent(int tid, std::string reasn, std::string txt = "") :
			Event("stopped", "{ \"threadId\": " + std::to_string(tid) + ", \"reason\": " + reasn + ", \"text\": " + txt + " }") { }
		};

		class ExitedEvent : public Event
		{
		public:
			ExitedEvent(int exCode) : 
				Event("exited", "{ \"exitCode\": " + std::to_string(exCode) + " }") { }
		};

		class TerminatedEvent : public Event
		{
		public:
			TerminatedEvent() : 
			Event("terminated") {	}
		};

		class ThreadEvent : public Event
		{
		public:
			ThreadEvent(std::string reasn, int tid) :
			Event("thread", "{ \"reason\": " + reasn + ", \"threadId\":" + std::to_string(tid) + " }") { }
		};

		class OutputEvent : public Event
		{
		public:
			OutputEvent(std::string cat, std::string outpt) :
				Event("output", "{ \"category\": " + cat + ", \"output\": " + outpt + " }") { }
		};
	}
}

#endif
