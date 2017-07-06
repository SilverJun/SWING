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
		/// JSON Serialize
		class JsonSerializable
		{
		public:
			virtual ~JsonSerializable() {}
			/**
			* \brief JsonSerializable -> std::string
			*/
			virtual void Serialize(rapidjson::Document& root) = 0;

			/**
			* \brief std::string -> JsonSerializable
			*/
			virtual void DeSerialize(rapidjson::Value& root) = 0;
		};

		class JsonSerializer
		{
		public:
			/**
			 * \brief JsonSerializable -> std::string
			 */
			static void Serialize(JsonSerializable* message, std::string& json);

			/**
			 * \brief std::string -> JsonSerializable
			 */
			static void DeSerialize(JsonSerializable* message, std::string& json);

		private:
			JsonSerializer() {}
		};
		///

		class Dynamic
		{
		public:
			rapidjson::Value _root;
			rapidjson::MemoryPoolAllocator<> _allocator;
			Dynamic() {}
			explicit Dynamic(std::string json);
			Dynamic(rapidjson::Value& json);
			Dynamic(const Dynamic& args);
			Dynamic& operator=(Dynamic& rhs);
		};

		/// ProtocolMessage
		class ProtocolMessage : public JsonSerializable
		{
		public:
			int _seq;
			/**
			 * \brief Maybe  request, response, event
			 */
			std::string _type;

			ProtocolMessage() {}
			ProtocolMessage(std::string typ);
			ProtocolMessage(std::string typ, int sq);

			void Serialize(rapidjson::Document& root) override;
			void DeSerialize(rapidjson::Value& root) override;
		};

		class Request : public ProtocolMessage
		{
		public:
			std::string _command;
			Dynamic _arguments;

			Request() {}
			Request(std::string cmd, Dynamic arg);
			Request(int id, std::string cmd, Dynamic arg);

			void Serialize(rapidjson::Document& root) override;
			void DeSerialize(rapidjson::Value& root) override;
		};

		class ResponseBody : public Dynamic
		{
			// Nothing.
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

			void Serialize(rapidjson::Document& root) override;
			void DeSerialize(rapidjson::Value& root) override;
		};

		class Event : public ProtocolMessage
		{
		public:
			std::string _event;
			Dynamic _body;

			explicit Event(std::string type);
			Event(std::string type, std::string body);

			void Serialize(rapidjson::Document& root) override;
			void DeSerialize(rapidjson::Value& root) override;
		};
	}
}
#endif
