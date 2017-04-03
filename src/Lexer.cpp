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
							case '?': case '&': case '|': case '^': case '(': case ')': case '{': case '}': case '[': \
							case ']': case '.': case ',':

#define CASE_ESCAPE_SQUENCE	case '\n': case '\0': case '\t': case '\r': case '\"': case '\'': case '\\':

namespace swing
{
	Lexer::Lexer(TokenList* tokList, std::vector<Keyword>* keywords, std::vector<Keyword>* operators) : _tokenList(tokList), _keywordList(keywords), _operatorList(operators), _sourceCode(""), _sourceLine(1)
	{
	}

	void Lexer::InitializeKeyword(std::vector<Keyword>* keywords)
	{
		if (!_keywordList->empty()) { return; }

		/// 키워드 초기화
		
		_keywordList = keywords;
	}

	void Lexer::InitializeLexer()
	{
		_sourceCode.clear();
		_tokenList->clear();
	}

	void Lexer::LoadSourceFile(std::string filename)
	{
		std::ifstream file(filename);

		if(!file.is_open())
		{
			std::cout << "File open Error, " << filename << std::endl;
			exit(1);
		}

		_sourceCode = std::string(std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>());

	}

	void Lexer::SetSourceCode(std::string source)
	{
		if (_sourceCode.length() != 0)
		{
			_sourceCode.clear();
		}
		_sourceCode = source;
	}

	void Lexer::GenerateTokenList()
	{
		try
		{
			for (auto iter = _sourceCode.begin(); iter != _sourceCode.end(); ++iter)
			{
				switch (*iter)
				{
				CASE_WHITE_SPACE
					if (*iter == '\n') { ++_sourceLine; }
					continue;

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
					throw Error(_sourceLine, "Unexcepted Token : " + *iter);
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
		}
		catch (std::out_of_range& e)
		{
			std::cout << "Lexer Error(out_of_range) : " << e.what() << std::endl;
		}
		catch(std::range_error& e)
		{
			std::cout << "Lexer Error(range_error) : " << e.what() << std::endl;
		}
		catch(std::system_error& e)
		{
			std::cout << "Lexer Error(system_error) code:" << e.code() << " " << e.what() << std::endl;
		}
		catch (...)
		{
			std::cout << "Unexpected Error in Lexer line " + std::to_string(_sourceLine) << std::endl;
			exit(1);
		}

		_tokenList->emplace_back(TokenID::Eof, _sourceLine + 1, 0, "");
	}

	void Lexer::LexCharacter(std::string::iterator& iter)
	{
		/// Identifier ::= [a-zA-Z_][0-9a-zA-z_]*

		std::string word;
		for (; isalnum(*iter) || *iter == '_'; word += *iter, ++iter) {}
		--iter;

		/// 키워드인지 비교.
		for (auto kw = _keywordList->begin(); kw != _keywordList->end(); ++kw)
		{
			if (word == (*kw)._word)
			{
				_tokenList->emplace_back((*kw)._id, _sourceLine, word);
				return;
			}
		}

		/// identifier로 추가.
		_tokenList->emplace_back(TokenID::Identifier, _sourceLine, word);
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

		if (*iter == 0 && iter != _sourceCode.end())
		{
			word += *next(iter);
		}

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
			for (; iter != _sourceCode.end(); ++iter) { if (!std::isxdigit(*iter)) { break; } }			/// xdigit이 아닐때 까지 iter를 증가한다.

			std::string number(start, prev(iter));

			_tokenList->emplace_back(TokenID::Literal_Integer, _sourceLine, stoi(number, nullptr, base), number);
		}

		auto start = iter;
		bool hasPoint = false;
		for (; iter != _sourceCode.end(); ++iter)
		{
			if (!hasPoint && *iter == '.') { hasPoint = true; }
			else if (!std::isdigit(*iter)) { break; }
		}
		std::string number(start, iter--);
		_tokenList->emplace_back(hasPoint ? TokenID::Literal_Double : TokenID::Literal_Integer, _sourceLine, stod(number, nullptr), number);
	}

	void Lexer::LexPunct(std::string::iterator& iter)
	{
		auto start = iter;
		for (;iter != _sourceCode.end() && std::ispunct(*iter) && *iter != '\"' && *iter != '\''; ++iter) {}
		std::string operatorString(start, iter--);

		for (auto it = _operatorList->begin(); it != _operatorList->end(); ++it)
		{
			if (operatorString == (*it)._word)
			{
				_tokenList->emplace_back((*it)._id, _sourceLine, (*it)._word);
				return;
			}
		}
		
		_tokenList->emplace_back(TokenID::Operator_UserDefined, _sourceLine, operatorString);
	}

	void Lexer::LexCharacterLiteral(std::string::iterator& iter)
	{
		/// Character ::= '_|[\][ntr0\'"]'

		switch (*++iter)
		{
		CASE_ESCAPE_SQUENCE
			LexEscapeSquence(iter);

		default:
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, *iter);
		}

		if (*iter != '\'') { throw Error(_sourceLine, "LexCharacterLiteral Error, Character is more than one."); }
	}

	void Lexer::LexEscapeSquence(std::string::iterator& iter)
	{
		/// Escape_sequence ::= [\]n | [\]t | [\]r | [\]0 | [\]\ | [\]' | [\]"

		switch (*iter)
		{
		case '\n':
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, '\n');
			break;

		case '\t':
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, '\t');
			break;

		case '\r':
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, '\r');
			break;
			
		case '\0':
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, '\0');
			break;

		case '\\':
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, '\\');
			break;

		case '\'':
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, '\'');
			break;

		case '\"':
			_tokenList->emplace_back(TokenID::Literal_Letter, _sourceLine, '\"');
			break;

		default:
			throw Error(_sourceLine, "Escape_sequence error \\" + *iter);
		}
	}

	void Lexer::LexStringLiteral(std::string::iterator& iter)
	{
		/// " 문자열 \(문자열 보간) 문자열 "
		/// \ + ( 있으면 Lexer새로 생성하고 괄호 안에 있는 것만 따로 Lex시킨다음 토큰 리스트를 이어 붙인다.
		/// \ ( TokenList )
		_tokenList->emplace_back(TokenID::Quotmark, _sourceLine, "\"");

		auto endOfInterpolation = [](std::string::iterator& iter) -> std::string
		{
			std::string::iterator start; 
			int paranCount = 1;
			for (start = iter; paranCount; ++iter) 
			{ 
				if (*iter == '(') 
				{
					++paranCount;
				} 
				else if (*iter == ')')
				{
					--paranCount;
				}
			}
			return std::string(start, --iter);
		};

		std::string::iterator start;

		for (start = ++iter; iter != _sourceCode.end() && *iter != '\"'; ++iter)
		{
			if (*iter == '\\')
			{
				if (*next(iter) == '(')		/// \(  String Interpolation
				{
					_tokenList->emplace_back(TokenID::Literal_String, _sourceLine, std::string(start, prev(iter++)));
					
					_tokenList->emplace_back(TokenID::StringInterpolation_Start, _sourceLine, "\\(");

					Lexer newLexer(_tokenList, _keywordList, _operatorList);
					newLexer.SetSourceLine(_sourceLine);

					newLexer.SetSourceCode(endOfInterpolation(++iter));

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
					newLexer.GenerateTokenList();
					_tokenList->pop_back();			//EOF TokenPop
					_tokenList->emplace_back(TokenID::StringInterpolation_End, _sourceLine, ")");

					start = next(iter);
				}
			}
		}

		if (start != iter)
		{
			_tokenList->emplace_back(TokenID::Literal_String, _sourceLine, std::string(start, iter));
		}

		_tokenList->emplace_back(TokenID::Quotmark, _sourceLine, "\"");
	}

	void Lexer::SkipToLineAnnotation(std::string::iterator& iter)
	{
		for (; *iter != '\n'; ++iter);		//개행문자를 만날 때 까지 iter증가
	}

	void Lexer::SkipToBlockAnnotation(std::string::iterator& iter)
	{
		for (; *prev(iter) != '*' && *iter != '/'; ++iter);		/// */까지 iter증가
	}

}