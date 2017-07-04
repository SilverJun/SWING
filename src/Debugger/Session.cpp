#include "Session.h"
#include <iostream>
#include "Log.h"
#include <algorithm>

namespace swing
{
	namespace vscode
	{
		Session::Session() : _twoCRLF("\r\n\r\n"), _contentLength("Content-Length: "), _jsonLength(-1), _stopLoop(false)
		{
		}

		void Session::StartSession()
		{
			while (!_stopLoop)
			{
				while (!std::cin.eof())
				{
					// Dispatch Content-Length
					std::string bufString = FindContentLength();

					if (bufString == "") { break; }

					Log::Message(bufString);

					std::string jsonLength = bufString.substr(_contentLength.length(), bufString.length() - 1);

					_jsonLength = std::stoi(jsonLength);

					// Eat CRLF
					std::cin.get();
					
					memset(_buffer, 0, bufsize);

					Log::Message(jsonLength);

					// Dispatch Json
					std::cin.read(_buffer, _jsonLength);

					Log::Message(_buffer);
					DispatchJson(_buffer);

					memset(_buffer, 0, bufsize);
				}

			}
		}

		std::string Session::FindContentLength()
		{
			std::string result = "";
			char c = '\0';

			while (true)
			{
				c = std::cin.get();
				if (c == '\n')
				{
					break;
				}
				result += c;
			}

			auto it = std::find_end(result.begin(), result.end(), _contentLength.begin(), _contentLength.end());

			return std::string(it, result.end());
		}

		void Session::DispatchJson(std::string json)
		{
			// Dispatch Json, respone json.
		}
	}
}
