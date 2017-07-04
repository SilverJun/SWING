#ifndef _SWING_SESSION_H_
#define _SWING_SESSION_H_

#include <vector>
#include <iostream>

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

		public:
			Session();
			void StartSession();

		private:
			std::string FindContentLength();
			void DispatchJson(std::string json);
		};
	}
}

#endif
