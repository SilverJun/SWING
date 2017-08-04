#include "Lexer.h"
#include "Error.h"

#include <fstream>
#include <iostream>
#include <cctype>

#define CASE_WHITE_SPACE	case ' ': case '\r': case '\t': case '\n':

#define CASE_LOWER_ALPHA	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': \
							case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': \
							case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z': 

#define CASE_UPPER_ALPHA	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': \
							case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R': \
							case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z': 

#define CASE_NUMBER			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':

#define CASE_PUNCT			case '+': case '-': case '*': case '%': case '=': case '<': case '>': case '!': case ':': \
							case '?': case '&': case '|': case '^':  case '.': case ',':

//#define CASE_ESCAPE_SQUENCE	case '\n': case '\0': case '\t': case '\r': case '\"': case '\'': case '\\':

namespace swing
{
	std::vector<Keyword> Lexer::_keywordList = {
		{ TokenID::Type_Var, "var" },
		{ TokenID::Type_Let, "let" },
		{ TokenID::Type_Nil, "nil" },
		{ TokenID::Type_Void, "void" },
		{ TokenID::Type_Bool, "bool" },
		{ TokenID::Type_Char, "char" },
		{ TokenID::Type_Int, "int" },
		{ TokenID::Type_Float, "float" },
		{ TokenID::Type_Double, "double" },
		{ TokenID::Type_String, "string" },
		{ TokenID::Type_Array, "Array" },
		{ TokenID::Type_Dictionary, "Dictionary" },
		{ TokenID::Type_Tuple, "Tuple" },
		{ TokenID::Struct_Decl, "struct" },
		{ TokenID::Enum_Decl, "enum" },
		{ TokenID::Class_Decl, "class" },
		{ TokenID::Protocol_Decl, "protocol" },
		{ TokenID::Extension_Decl, "extension" },
		{ TokenID::Stmt_If, "if" },
		{ TokenID::Stmt_Else, "else" },
		{ TokenID::Stmt_Switch, "switch" },
		{ TokenID::Stmt_Case, "case" },
		{ TokenID::Stmt_Default, "default" },
		{ TokenID::Stmt_Guard, "guard" },
		{ TokenID::Stmt_While, "while" },
		{ TokenID::Stmt_For, "for" },
		{ TokenID::Stmt_In, "in" },
		{ TokenID::Stmt_Return, "return" },
		{ TokenID::Stmt_Private, "for" },
		{ TokenID::Stmt_Inherit, "in" },
		{ TokenID::Stmt_Public, "return" },
		{ TokenID::Func_Decl, "func" },
		{ TokenID::Func_Inout, "inout" },
		{ TokenID::Operator_Prefix, "prefix" },
		{ TokenID::Operator_Infix, "infix" },
		{ TokenID::Operator_Postfix, "postfix" },
		{ TokenID::Operator_Decl, "operator" },
		{ TokenID::Boolean_Value, "true" },
		{ TokenID::Boolean_Value, "false" },

		{ TokenID::Arithmetic_Add, "+" },
		{ TokenID::Arithmetic_Subtract, "-" },
		{ TokenID::Arithmetic_Multiply, "*" },
		{ TokenID::Arithmetic_Divide, "/" },
		{ TokenID::Arithmetic_Modulo, "%" },
		{ TokenID::Arithmetic_Power, "**" },
		{ TokenID::Assignment, "=" },
		{ TokenID::Bitwise_And, "&" },
		{ TokenID::Bitwise_Or, "|" },
		{ TokenID::Bitwise_Not, "~" },
		{ TokenID::Bitwise_Xor, "^" },
		{ TokenID::Bitwise_ShiftRight, ">>" },
		{ TokenID::Bitwise_ShiftLeft, "<<" },
		{ TokenID::Logical_And, "&&" },
		{ TokenID::Logical_Or, "||" },
		{ TokenID::Logical_Not, "!" },
		{ TokenID::Relational_Equal, "==" },
		{ TokenID::Relational_NotEqual, "!=" },
		{ TokenID::Relational_Greater, ">" },
		{ TokenID::Relational_Less, "<" },
		{ TokenID::Relational_GreaterEqual, ">=" },
		{ TokenID::Relational_LessEqual, "<=" },
		{ TokenID::Arrow, "->" },
		{ TokenID::Optional_Nilable, "?" },
		{ TokenID::Optional_Binding, "!" },
		{ TokenID::OpenBig, "[" },
		{ TokenID::OpenMedium, "{" },
		{ TokenID::OpenSmall, "(" },
		{ TokenID::CloseSmall, ")" },
		{ TokenID::CloseMedium, "}" },
		{ TokenID::CloseBig, "]" },
		{ TokenID::Range_Closed, "..." },
		{ TokenID::Range_Opened, "..<" },

		{ TokenID::Casting_As, "as" },
		{ TokenID::Casting_Is, "is" },

		{ TokenID::Colon, ":" },
		{ TokenID::Comma, "," },
	};

	Lexer::Lexer() : _tokenList(nullptr), _sourceCode(nullptr), _sourceName(nullptr), _sourceLine(1)
	{
		
	}

	void Lexer::LexSource(Source* src)
	{
		/// src에 있는 소스코드와 src에 있는 토큰리스트에 토큰을 넣는다. 좋아. 가자.
		_sourceCode = &src->_code;
		_tokenList = &src->_tokenList;
		_sourceLine = 1;
		_sourceName = &src->_name;

		LexStart();
	}

	void Lexer::LexStart()
	{
		try
		{
			for (auto iter = _sourceCode->begin(); iter != _sourceCode->end(); ++iter)
			{
				switch (*iter)
				{
				CASE_WHITE_SPACE
						if (*iter == '\n') { ++_sourceLine; }
					continue;
				case '(':
					_tokenList->emplace_back(TokenID::OpenSmall, _sourceLine, *_sourceName, "(");
					break;
				case ')':
					_tokenList->emplace_back(TokenID::CloseSmall, _sourceLine, *_sourceName, ")");
					break;
				case '{':
					_tokenList->emplace_back(TokenID::OpenMedium, _sourceLine, *_sourceName, "{");
					break;
				case '}':
					_tokenList->emplace_back(TokenID::CloseMedium, _sourceLine, *_sourceName, "}");
					break;
				case '[':
					_tokenList->emplace_back(TokenID::OpenBig, _sourceLine, *_sourceName, "[");
					break;
				case ']':
					_tokenList->emplace_back(TokenID::CloseBig, _sourceLine, *_sourceName, "]");
					break;

				case '/':
					if (*next(iter) == '/') { SkipToLineAnnotation(iter); }		/// slash-slash line annotation "//"
					else if (*next(iter) == '*') { SkipToBlockAnnotation(iter); }		/// slash-star block annotation "/*"
					else { LexPunct(iter); }		/// operators
					break;

				case '\'':
					LexCharacterLiteral(iter);
					break;

				case '\"':
					LexStringLiteral(iter);
					break;

				CASE_UPPER_ALPHA
				CASE_LOWER_ALPHA
				case '_':
					LexCharacter(iter);
					break;

				CASE_NUMBER
						LexNumber(iter);
					break;

				CASE_PUNCT
						LexPunct(iter);
					break;

				default:
					throw LexicalError(_sourceLine, "Unexcepted Token : " + *iter);
				}
			}
		}
		catch (Error& e)
		{
			std::cout << "Lexer Error : " << e.what() << std::endl;
			exit(1);
		}
		catch (std::invalid_argument& e)
		{
			std::cout << "Lexer Error(invalid_argument) : " << e.what() << std::endl;
			exit(1);
		}
		catch (std::out_of_range& e)
		{
			std::cout << "Lexer Error(out_of_range) : " << e.what() << std::endl;
			exit(1);
		}
		catch (std::range_error& e)
		{
			std::cout << "Lexer Error(range_error) : " << e.what() << std::endl;
			exit(1);
		}
		catch (std::system_error& e)
		{
			std::cout << "Lexer Error(system_error) code:" << e.code() << " " << e.what() << std::endl;
			exit(1);
		}
		catch (...)
		{
			std::cout << "Unexpected Error in Lexer line " + std::to_string(_sourceLine) << std::endl;
			exit(1);
		}

		_tokenList->emplace_back(TokenID::Eof, _sourceLine + 1, *_sourceName);
	}

	void Lexer::LexCharacter(std::string::iterator& iter)
	{
		/// Identifier ::= [a-zA-Z_][0-9a-zA-z_]*

		std::string word;
		for (; isalnum(*iter) || *iter == '_'; word += *iter, ++iter) {}
		--iter;

		/// 키워드인지 비교.
		for (auto kw : _keywordList)
		{
			if (word == kw._word)
			{
				_tokenList->emplace_back(kw._id, _sourceLine, *_sourceName, word);
				return;
			}
		}

		/// identifier로 추가.
		_tokenList->emplace_back(TokenID::Identifier, _sourceLine, *_sourceName, word);
	}

	void Lexer::LexNumber(std::string::iterator& iter)
	{
		/// Integer	::= [0-9][0-9]*
		/// Hexa	::= 0x[0-9a-fA-F][0-9a-fA-F]*
		/// Octal	::= 0o[0-7][0-7]*
		/// Binary	::= 0b[01][01]*
		/// Double	::= [0-9][0-9]*.[0-9][0-9]*
		
		std::string word;

		/// 0xAB, 0b01010, 0o17등 2,8,16진수 처리
		word = *iter;

		if (*iter == 0 && iter != _sourceCode->end())
			word += *next(iter);

		/// 특이 케이스 처리.
		if (word == "0x" || word == "0o" || word == "0b")
		{
			int base = 10;		/// 2 - binary, 8 - octa, 10 - decimal, 16 - hexa
			switch (*++iter)
			{
			case 'b': base = 2; break;
			case 'o': base = 8; break;
			case 'x': base = 16; break;
			}

			auto start = ++iter;

			for (; iter != _sourceCode->end(); ++iter)
			{
				if (!std::isxdigit(*iter))
					break;		/// xdigit이 아닐때 까지 iter를 증가한다.
			}

			std::string number(start, prev(iter));

			_tokenList->emplace_back(TokenID::Literal_Integer, _sourceLine, *_sourceName, stoi(number, nullptr, base), number);
		}
		else
		{
			auto start = iter;
			bool hasPoint = false;
			bool floatIdenti = false;
			for (; iter != _sourceCode->end(); ++iter)
			{
				/// 소수점을 사용했는가?
				if (!hasPoint && *iter == '.')
					hasPoint = true;
				/// .0f와 같은 float형을 명시적으로 사용했는가?
				else if (hasPoint && !floatIdenti && *iter == 'f')
					floatIdenti = true;
				else if (!std::isdigit(*iter))
					break;
			}
			
			std::string number(start, iter--);

			if (hasPoint)
			{
				if (floatIdenti)
					_tokenList->push_back(Token(TokenID::Literal_Float, _sourceLine, *_sourceName, stof(number, nullptr), number));
				else
					_tokenList->push_back(Token(TokenID::Literal_Double, _sourceLine, *_sourceName, stod(number, nullptr), number));
			}
			else
				_tokenList->push_back(Token(TokenID::Literal_Integer, _sourceLine, *_sourceName, stoi(number, nullptr), number));

		}
	}

	void Lexer::LexPunct(std::string::iterator& iter)
	{
		auto start = iter;
		for (;iter != _sourceCode->end() && std::ispunct(*iter) && *iter != '\"' && *iter != '\''; ++iter) {}
		std::string operatorString(start, iter--);

		for (auto it : _keywordList)
		{
			if (operatorString == it._word)
			{
				_tokenList->emplace_back(it._id, _sourceLine, *_sourceName, it._word);
				return;
			}
		}
		
		_tokenList->emplace_back(TokenID::Operator_UserDefined, _sourceLine, *_sourceName, operatorString);
	}

	void Lexer::LexCharacterLiteral(std::string::iterator& iter)
	{
		/// Character ::= '_|[\][ntr0\'"]'
		switch (*++iter)
		{
		case '\\':
			LexEscapeSquence(iter);

		default:
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, *_sourceName, *iter);
		}

		if (*iter != '\'') { throw LexicalError(_sourceLine, "LexCharacterLiteral Error, Character is more than one."); }
	}

	void Lexer::LexEscapeSquence(std::string::iterator& iter)
	{
		/// Escape_sequence ::= [\]n | [\]t | [\]r | [\]0 | [\]\ | [\]' | [\]"
		if (*iter != '\\') return;
		++iter;

		switch (*iter)
		{
		case 'n':
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, *_sourceName, '\n');
			break;

		case 't':
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, *_sourceName, '\t');
			break;

		case 'r':
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, *_sourceName, '\r');
			break;
			
		case '0':
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, *_sourceName, '\0');
			break;

		case '\\':
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, *_sourceName, '\\');
			break;

		case '\'':
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, *_sourceName, '\'');
			break;

		case '\"':
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, *_sourceName, '\"');
			break;

		default:
			throw LexicalError(_sourceLine, "Escape_sequence error \\" + *iter);
		}
	}

	void Lexer::LexStringLiteral(std::string::iterator& iter)
	{
		/// " 문자열 \(문자열 보간) 문자열 "
		/// \ + ( 있으면 Lexer새로 생성하고 괄호 안에 있는 것만 따로 Lex시킨다음 토큰 리스트를 이어 붙인다.
		/// \ ( TokenList )
		_tokenList->emplace_back(TokenID::Quotmark, _sourceLine, *_sourceName, "\"");

		auto endOfInterpolation = [](std::string::iterator& iter) -> std::string
		{
			std::string::iterator start; 
			int paranCount = 1;
			for (start = iter; paranCount; ++iter) 
			{ 
				if (*iter == '(') 
					++paranCount;
				else if (*iter == ')')
					--paranCount;
			}
			return std::string(start, --iter);
		};

		std::string::iterator start;

		for (start = ++iter; iter != _sourceCode->end() && *iter != '\"'; ++iter)
		{
			if (*iter == '\\')
			{
				if (*next(iter) == '(')		/// \(  String Interpolation
				{
					_tokenList->emplace_back(TokenID::Literal_String, _sourceLine, *_sourceName, std::string(start, prev(iter++)));
					
					_tokenList->emplace_back(TokenID::StringInterpolation_Start, _sourceLine, *_sourceName, "\\(");

					auto temp = _sourceCode;
					auto strIntrp = endOfInterpolation(++iter);
					_sourceCode = &strIntrp;

					/// Token List Structure
					///
					/// "	Quotmark		StringLiteral Start
					/// ...	Literal_String	StringLiterals...
					/// (	OpenSmall		StringInterpolation Start
					/// ... TokenLists		Token
					/// )	CloseSmall		StringInterpolation End
					/// ...	Literal_String	StringLiterals...
					/// "	Quotmark		StringLiteral End
					///

					LexStart();

					_tokenList->pop_back();			// EOF TokenPop
					_tokenList->emplace_back(TokenID::StringInterpolation_End, _sourceLine, *_sourceName, ")");
					_sourceCode = temp;
				}
				else
				{
					LexEscapeSquence(iter);
					Token token = _tokenList->back();
					char escape = token._char;
					_tokenList->pop_back();			// escape TokenPop

					iter = _sourceCode->erase(std::prev(iter), std::next(iter));
					_sourceCode->insert(iter, escape);
				}
			}
		}

		if (start != iter)
			_tokenList->emplace_back(TokenID::Literal_String, _sourceLine, *_sourceName, std::string(start, iter));

		_tokenList->emplace_back(TokenID::Quotmark, _sourceLine, *_sourceName, "\"");
	}

	void Lexer::SkipToLineAnnotation(std::string::iterator& iter)
	{
		for (; *iter != '\n'; ++iter);		/// 개행문자를 만날 때 까지 iter증가
	}

	void Lexer::SkipToBlockAnnotation(std::string::iterator& iter)
	{
		for (; *prev(iter) != '*' && *iter != '/'; ++iter);		/// */까지 iter증가
	}
}
