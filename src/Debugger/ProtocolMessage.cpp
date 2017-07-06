#include "ProtocolMessage.h"
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "Log.h"

namespace swing
{
	namespace vscode
	{
		void JsonSerializer::Serialize(JsonSerializable* message, std::string& json)
		{
			rapidjson::Document doc;
			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer;

			message->Serialize(doc);

			doc.Accept(writer);

			json = buffer.GetString();
		}

		void JsonSerializer::DeSerialize(JsonSerializable* message, std::string& json)
		{
			rapidjson::Document doc;
			doc.Parse(json.c_str(), json.length());
			rapidjson::Value root = doc.GetObject();
			message->DeSerialize(root);
		}

		Dynamic::Dynamic(std::string json)
		{
			rapidjson::Document doc;
			doc.Parse(json.c_str(), json.length());
			rapidjson::Value obj = doc.GetObject();
			_root.CopyFrom(obj, _allocator);
		}

		Dynamic::Dynamic(rapidjson::Value& json)
		{
			_root.CopyFrom(json, _allocator);
		}

		Dynamic::Dynamic(const Dynamic& args)
		{
			_root.CopyFrom(args._root, _allocator);
		}

		Dynamic& Dynamic::operator=(Dynamic& rhs)
		{
			_root.CopyFrom(rhs._root, _allocator);
			return *this;
		}

		///------------------------------------------------------

		ProtocolMessage::ProtocolMessage(std::string typ) :
			_seq(0), _type(typ)
		{
		}

		ProtocolMessage::ProtocolMessage(std::string typ, int sq) :
			_seq(sq), _type(typ)
		{
		}

		void ProtocolMessage::Serialize(rapidjson::Document& root)
		{
			root.AddMember("seq", rapidjson::Value().SetInt(_seq), root.GetAllocator());
			root.AddMember("type", rapidjson::Value(_type.c_str(), root.GetAllocator()), root.GetAllocator());
		}

		void ProtocolMessage::DeSerialize(rapidjson::Value& root)
		{
			_seq = root["seq"].GetInt();
			_type = root["type"].GetString();
		}

		///

		Request::Request(std::string cmd, Dynamic arg) :
			ProtocolMessage("request"), _command(cmd), _arguments(arg)
		{
		}

		Request::Request(int id, std::string cmd, Dynamic arg) :
			ProtocolMessage("request", id), _command(cmd), _arguments(arg)
		{
		}

		void Request::Serialize(rapidjson::Document& root)
		{
			ProtocolMessage::Serialize(root);
			root.AddMember("command", rapidjson::Value(_command.c_str(), root.GetAllocator()), root.GetAllocator());
			root.AddMember("arguments", _arguments._root, root.GetAllocator());
		}

		void Request::DeSerialize(rapidjson::Value& root)
		{
			ProtocolMessage::DeSerialize(root);
			_command = root["command"].GetString();
			_arguments._root.CopyFrom(root["arguments"], _arguments._allocator);
		}

		///

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

		void Response::Serialize(rapidjson::Document& root)
		{
			ProtocolMessage::Serialize(root);

			root.AddMember("request_seq", rapidjson::Value().SetInt(_requestSeq), root.GetAllocator());
			root.AddMember("success", rapidjson::Value().SetBool(_success), root.GetAllocator());
			root.AddMember("command", rapidjson::Value(_message.c_str(), root.GetAllocator()), root.GetAllocator());
			root.AddMember("message", rapidjson::Value(_message.c_str(), root.GetAllocator()), root.GetAllocator());
			root.AddMember("body", _body._root, root.GetAllocator());
		}

		void Response::DeSerialize(rapidjson::Value& root)
		{
			ProtocolMessage::DeSerialize(root);

			_requestSeq = root["request_seq"].GetInt();
			_success = root["success"].GetBool();
			_command = root["command"].GetString();
			_message = root["message"].GetString();
			_body._root.CopyFrom(root["body"], _body._allocator);
		}

		///

		Event::Event(std::string type) :
			ProtocolMessage("event"), _event(type), _body()
		{
		}

		Event::Event(std::string type, std::string body) :
			ProtocolMessage("event"), _event(type), _body(body)
		{
		}

		void Event::Serialize(rapidjson::Document& root)
		{
			ProtocolMessage::Serialize(root);
			root.AddMember("event", rapidjson::Value(_event.c_str(), root.GetAllocator()), root.GetAllocator());
			root.AddMember("body", _body._root, root.GetAllocator());
		}

		void Event::DeSerialize(rapidjson::Value& root)
		{
			ProtocolMessage::DeSerialize(root);
			_event = root["event"].GetString();
			_body._root.CopyFrom(root["body"], _body._allocator);
		}

		///

	}
}
