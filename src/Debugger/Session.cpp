#include "Session.h"
#include <iostream>
#include "Log.h"


namespace swing
{
	namespace vscode
	{
		Session::Session() :
			_twoCRLF("\r\n\r\n"), _contentLength("Content-Length: "), _jsonLength(-1), _stopLoop(false), _sequenceNumber(1)
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

					Log::Message(bufString);

					//if (bufString == "") { break; }

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

					for (int i = 0; i < _jsonLength; i++) { std::cin.get(); }
					memset(_buffer, 0, bufsize);
				}

			}
		}

		std::string Session::FindContentLength()
		{
			char buf[512];
			std::cin.getline(buf, 512);
			return std::string(buf);
		}

		void Session::DispatchJson(std::string json)
		{
			// Dispatch Json, respone json.

			ProtocolMessage message;
			JsonSerializer::DeSerialize(&message, json);

			if (message._type == "request")
			{
				
			}
			else if (message._type == "response")
			{
				
			}
			else
			{
				Log::Message("Unknown json type: " + std::string(message._type));
			}
		}

		void Session::SendMessage(ProtocolMessage* message)
		{
			if (message->_seq == 0) {
				message->_seq = _sequenceNumber++;
			}

			std::string json;
			JsonSerializer::Serialize(message, json);

			std::cout << _contentLength << std::to_string(json.length()) << _twoCRLF << json;
			std::cout.flush();
		}
	}
}
