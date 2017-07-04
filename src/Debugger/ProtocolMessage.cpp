#include "ProtocolMessage.h"
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace swing
{
	namespace vscode
	{
		///

		ProtocolMessage::ProtocolMessage(std::string typ) :
			_seq(0), _type(typ), _jsonRoot(_json.GetObject()), _allocator(_json.GetAllocator())
		{
			GenerateJson();
		}

		ProtocolMessage::ProtocolMessage(std::string typ, int sq) :
			_seq(sq), _type(typ), _jsonRoot(_json.GetObject()), _allocator(_json.GetAllocator())
		{
			GenerateJson();
		}

		rapidjson::Value* ProtocolMessage::GetValue(std::string key)
		{
			auto root = _json.GetObject();
			for (auto iter = _json.MemberBegin(); iter != _json.MemberEnd(); ++iter)
			{
				if (key == iter->name.GetString())
				{
					return &iter->value;
				}
			}
			return nullptr;
		}

		std::string ProtocolMessage::Serialize()
		{
			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> prettyWriter(buffer);

			_json.CopyFrom(_jsonRoot, _allocator);
			_json.Accept(prettyWriter);

			return buffer.GetString();
		}

		void ProtocolMessage::GenerateJson()
		{
			_jsonRoot.AddMember("seq", rapidjson::Value(_seq), _allocator);
			_jsonRoot.AddMember("type", rapidjson::Value(_type.c_str(), _allocator), _allocator);
		}

		///

		RequestArgs::RequestArgs() :
			_kind(""), _title(""), _cwd(""), _args({}), _env({})
		{
		}
		RequestArgs::RequestArgs(std::string kind, std::string title, std::string cwd, std::vector<std::string> args, std::map<std::string, std::string> env) :
			_kind(kind), _title(title), _cwd(cwd), _args(args), _env(env)
		{
		}

		///

		Request::Request(std::string cmd, RequestArgs arg) :
			ProtocolMessage("request"), _command(cmd), _arguments(arg)
		{
			GenerateJson();
		}

		Request::Request(int id, std::string cmd, RequestArgs arg) :
			ProtocolMessage("request", id), _command(cmd), _arguments(arg)
		{
			GenerateJson();
		}

		void Request::GenerateJson()
		{
			_jsonRoot.AddMember("command", rapidjson::Value(_command.c_str(), _allocator), _allocator);

			rapidjson::Value argRoot(rapidjson::kObjectType);
			argRoot.AddMember("kind", rapidjson::Value(_arguments._kind.c_str(), _allocator), _allocator);
			argRoot.AddMember("title", rapidjson::Value(_arguments._title.c_str(), _allocator), _allocator);
			argRoot.AddMember("cwd", rapidjson::Value(_arguments._cwd.c_str(), _allocator), _allocator);

			rapidjson::Value argArgs(rapidjson::kArrayType);
			for (auto element : _arguments._args)
			{
				argArgs.PushBack(rapidjson::Value(element.c_str(), _allocator), _allocator);
			}
			argRoot.AddMember("args", argArgs, _allocator);

			rapidjson::Value argEnv(rapidjson::kObjectType);
			for (auto element : _arguments._env)
			{
				rapidjson::Value key(element.first.c_str(), _allocator);
				rapidjson::Value value(element.second.c_str(), _allocator);
				argEnv.AddMember(key, value, _allocator);
			}
			argRoot.AddMember("env", argEnv, _allocator);

			_jsonRoot.AddMember("arguments", argRoot, _allocator);
		}

		Response::Response(Request req) : 
			ProtocolMessage("response"), _success(true), _requestSeq(req._seq), _command(req._command)
		{
		}

		void Response::SetBody(ResponseBody bdy)
		{
			_success = true;
			_body = bdy;
		}

		void Response::SetErrorBody(std::string msg, ResponseBody bdy)
		{
			_success = false;
			_message = msg;
			_body = bdy;
		}

		void Response::GenerateJson()
		{
		}

		Event::Event(std::string type) : ProtocolMessage("event"), _eventType(type)
		{
		}

		void Event::GenerateJson()
		{
		}
	}
}
