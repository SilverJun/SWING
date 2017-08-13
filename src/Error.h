#ifndef _SWING_ERROR_H_
#define _SWING_ERROR_H_

#include <string>
#include <sstream>
#include "source.h"
#include "Token.h"

namespace swing
{
	class Error
	{
	public:
		std::string _description;

		Error(std::string desc) : _description(desc) {}
		virtual ~Error() {}
		
		virtual std::string what() const
		{
			return _description;
		}
	};

	class LexicalError : public Error
	{
	public:
		int _sourceLine;

		LexicalError(int sourceLine, std::string desc) : Error(desc), _sourceLine(sourceLine) {}
		~LexicalError() {}

		std::string what() const override
		{
			std::stringstream iss;
			iss << std::string("Lexical Error> Line:") << _sourceLine << "Message> " << _description;
			return iss.str();
		}
	};

	class ParsingError : public Error
	{
	public:
		const Token& _token;

		ParsingError(const Token& tok, std::string desc) : Error(desc), _token(tok) {}
		~ParsingError() {}

		std::string what() const override
		{
			std::string msg;
			std::stringstream iss(msg);
			iss << std::string("Parsing Error> ") << _token  << "Message> " << _description;
			return msg;
		}
	};
}

#endif
