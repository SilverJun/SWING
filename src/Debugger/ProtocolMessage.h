#ifndef _SWING_PROTOCOL_MESSAGE_H_
#define _SWING_PROTOCOL_MESSAGE_H_

#include <string>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <vector>
#include <map>

namespace swing
{
	namespace vscode
	{
		class ProtocolMessage
		{
		public:
			rapidjson::Document _json;
			rapidjson::Value _jsonRoot;
			rapidjson::Document::AllocatorType& _allocator;
			int _seq;

			/**
			 * \brief Maybe  request, response, event
			 */
			std::string _type;

			ProtocolMessage(std::string typ);
			ProtocolMessage(std::string typ, int sq);

			rapidjson::Value* GetValue(std::string key);
			std::string Serialize();
		private:
			void GenerateJson();
		};

		struct RequestArgs
		{
			std::string _kind;
			std::string _title;
			std::string _cwd;
			std::vector<std::string> _args;
			std::map<std::string, std::string> _env;

			RequestArgs();
			RequestArgs(std::string kind, std::string title, std::string cwd, std::vector<std::string> args, std::map<std::string, std::string> env);
		};

		class Request : public ProtocolMessage
		{
		public:
			std::string _command;
			RequestArgs _arguments;

			Request(std::string cmd, RequestArgs arg);
			Request(int id, std::string cmd, RequestArgs arg);
		private:
			void GenerateJson();
		};

		class ResponseBody
		{
			/// Nothing.
		};

		class Response : public ProtocolMessage
		{
		public:
			bool _success;
			std::string _message;
			int _requestSeq;
			std::string _command;
			ResponseBody _body;

			Response(Request req);
			void SetBody(ResponseBody bdy);
			void SetErrorBody(std::string msg, ResponseBody bdy);
		private:
			void GenerateJson();
		};

		class Event : ProtocolMessage
		{
		public:
			std::string _eventType;

			Event(std::string type);
		private:
			void GenerateJson();
		};
	}
}
#endif
