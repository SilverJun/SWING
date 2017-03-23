#include "Lexer.h"
#include "Error.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>
#include <locale>
#include <iterator>

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
							case ']': 

std::vector<swing::Lexer::Keyword> swing::Lexer::_keywordList = std::vector<Keyword>();

namespace swing
{
	Lexer::Lexer()
	{
		_sourceCode.clear();
		_tokenList.clear();
		_sourceLine = 0;
	}

	void Lexer::InitializeKeyword()
	{
		/// 키워드 초기화
		std::vector<Keyword> kList = {
			{ TokenID::Type_Var, "var" },
			{ TokenID::Type_Let, "let" },
			{ TokenID::Type_Nil, "nil" },
			{ TokenID::Type_Int, "int" },
			{ TokenID::Type_Double, "double" },
			{ TokenID::Type_String, "string" },
			{ TokenID::Type_Array, "Array" },
			{ TokenID::Type_Dictionary, "Dictionary" },
			{ TokenID::Type_Tuple, "Tuple" },

			{ TokenID::Stmt_If, "if" },
			{ TokenID::Stmt_Else, "else" },
			{ TokenID::Stmt_Guard, "guard" },
			{ TokenID::Stmt_While, "while" },
			{ TokenID::Stmt_For, "for" },
			{ TokenID::Stmt_In, "in" }
		};

		_keywordList.clear();

		_keywordList = kList;
	}

	void Lexer::Initialize()
	{
		InitializeKeyword();

		_sourceCode.clear();
		_tokenList.clear();
		_sourceLine = 0;
	}

	void Lexer::LoadSourceFile(std::string filename)
	{
		std::fstream* srcFile = new std::fstream(filename, std::ios::in);

		_sourceCode.clear();

		if (!srcFile)
		{
			std::cout << "Error : FileOpenError!" << std::endl;
			exit(-1);
		}

		char c;
		while ((c = srcFile->get()) != -1)
		{
			_sourceCode += c;
		}

		srcFile->close();
		delete srcFile;
	}

	void Lexer::SetSourceCode(std::string source)
	{
		_sourceCode.clear();
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
					continue;

				case '/':
					if (*next(iter) == '/') { SkipToLineAnnotation(iter); }		/// slash-slash line annotation "//"
					else if (*next(iter) == '*') { SkipToBlockAnnotation(iter); }		/// slash-star block annotation "/*"
					else { LexPunct(iter); }		/// operators
					break;

				CASE_LOWER_ALPHA
				CASE_UPPER_ALPHA
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
			std::cout << "Lexer Error : " << e.what() << std::endl;
		}
		catch (std::out_of_range& e)
		{
			std::cout << "Lexer Error : " << e.what() << std::endl;
		}
		catch (...)
		{
			std::cout << "Unexpected Error in Lexer line " + std::to_string(_sourceLine) << std::endl;
			exit(1);
		}
		

		_tokenList.emplace_back(TokenID::Eof, _sourceLine + 1, 0, "");
	}

	void Lexer::LexCharacter(std::string::iterator& iter)
	{
		/// Identifier ::= [a-zA-Z_][0-9a-zA-z_]*

		std::string word;
		for (; isalnum(*iter) || *iter == '_'; word += *iter, ++iter) {}

		/// 키워드인지 비교.
		for (auto kw = _keywordList.begin(); kw != _keywordList.end(); ++kw)
		{
			if (word == (*kw)._word)
			{
				_tokenList.emplace_back((*kw)._id, _sourceLine, word);
				return;
			}
		}

		/// identifier로 추가.
		_tokenList.emplace_back(TokenID::Identifier, _sourceLine, word);
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
		word += *next(iter);

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

			_tokenList.emplace_back(TokenID::Literal_Integer, _sourceLine, stoi(std::string(start, prev(iter)), nullptr, base));
		}

		auto start = iter;
		bool hasPoint = false;
		for (; iter != _sourceCode.end(); ++iter)
		{
			if (!hasPoint && *iter == '.') { hasPoint = true; }
			else if (!std::isdigit(*iter)) { break; }
		}

		_tokenList.emplace_back(hasPoint? TokenID::Literal_Double: TokenID::Literal_Integer, _sourceLine, stod(std::string(start, --iter), nullptr));
	}

	void Lexer::LexPunct(std::string::iterator& iter)
	{

	}

	void Lexer::LexStringLiteral(std::string::iterator& iter)
	{
		/// " 문자열 \(문자열 보간) 문자열 "
		/// \ + ( 있으면 Lexer새로 생성하고 괄호 안에 있는 것만 따로 Lex시킨다음 토큰 리스트를 이어 붙인다.
		/// \ ( TokenList )


	}

	void Lexer::SkipToLineAnnotation(std::string::iterator& iter)
	{

	}

	void Lexer::SkipToBlockAnnotation(std::string::iterator& iter)
	{

	}

}