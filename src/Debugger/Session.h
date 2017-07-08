#ifndef _SWING_SESSION_H_
#define _SWING_SESSION_H_

#include "ProtocolMessage.h"

namespace swing
{
	namespace vscode
	{
		class Session
		{
			const std::string _twoCRLF;
			const std::string _contentLength;
			enum {bufsize = 4096};
			char _buffer[bufsize];
			int _jsonLength;
			bool _stopLoop;


			int _sequenceNumber;

		public:
			Session();
			void StartSession();

		private:
			std::string FindContentLength();
			void DispatchJson(std::string json);

			void SendMessage(ProtocolMessage* message);
		};
	}
}

#endif
