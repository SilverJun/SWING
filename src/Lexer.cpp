#include "Lexer.h"
#include "Error.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <cctype>

namespace swing
{
	void Lexer::Initialize()
	{
		/// 키워드 초기화
		_keywordList.emplace_back(TokenID::Type_Var, "var");
		_keywordList.emplace_back(TokenID::Type_Let, "let");
		_keywordList.emplace_back(TokenID::Type_Nil, "nil");
		_keywordList.emplace_back(TokenID::Type_Int, "int");
		_keywordList.emplace_back(TokenID::Type_Double, "double");
		_keywordList.emplace_back(TokenID::Type_String, "string");
		_keywordList.emplace_back(TokenID::Type_Array, "Array");
		_keywordList.emplace_back(TokenID::Type_Dictionary, "Dictionary");
		_keywordList.emplace_back(TokenID::Type_Tuple, "Tuple");

		_keywordList.emplace_back(TokenID::Stmt_If, "if");
		_keywordList.emplace_back(TokenID::Stmt_Else, "else");
		_keywordList.emplace_back(TokenID::Stmt_Guard, "guard");
		_keywordList.emplace_back(TokenID::Stmt_While, "while");
		_keywordList.emplace_back(TokenID::Stmt_For, "for");
		_keywordList.emplace_back(TokenID::Stmt_In, "in");

		///

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
			system("pause");
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

	void Lexer::GenerateTokenList()
	{
		/**
		 *	1. 한줄을 읽어들인다.
		 *	2. 한줄에서 공백 단위로 파싱을 한다.
		 *	3. 추출된 한 단어를 준비된 키워드, 연산자 등을 비교하여 토큰생성
		 *	4. 반복
		 */

		std::stringstream ss(_sourceCode);
		std::string line;
		
		/// 1. 한줄을 읽어들인다.
		for (_sourceLine = 1; std::getline(ss, line); ++_sourceLine)
		{
			if (line.empty()){ continue; }		///빈 문자열 처리

			std::regex reg("\\S+(\"(.*)\")?(\'.\')?");
			std::smatch sm;

			/// 2. 한줄에서 공백 단위로 파싱을 한다.
			for (std::string word; regex_search(line, sm, reg); line = sm.suffix())
			{
				/// 3. 추출된 한 단어를 준비된 키워드, 연산자 등을 비교하여 토큰생성
				word = sm.str();
				std::cout << word;

				GenerateToken(word);
			}

			std::cout << std::endl;
		}

		_tokenList.emplace_back(TokenID::Eof, _sourceLine + 1, 0, "");
	}

	void Lexer::GenerateToken(std::string word)
	{
		//if (word.empty()){ return; }
		/**
		 * 첫번째가 문자, 숫자, 특별한문자인가?
		 *     문자-> 키워드, identifier, 띄어쓰기 안한 표현식 처리 ex) variable+1021
		 *     숫자-> 숫자(0b,0o,ox체크, 부동 소수점 포함), 띄어쓰기 안한 표현식처리
		 *     특별-> 큰따옴표, 작은따옴표 그외 연산자
		 */
		try
		{
			std::string str;			///처리 과정에서 필요한 문자열을 담음.
			double num;
			auto wordIter = word.begin();

			///문자일 경우
			if (std::isalpha(word[0]))
			{
				/// 키워드인지 비교.
				for (auto iter = _keywordList.begin(); iter != _keywordList.end(); ++iter)
				{
					if (word == (*iter)._word) { _tokenList.emplace_back((*iter)._id, _sourceLine, word); return; }
				}
				
				/// identifier로 추가.
				for (; wordIter != word.end() && (std::isalnum(*wordIter) || *wordIter == '_'); ++wordIter) { }
				_tokenList.emplace_back(TokenID::Identifier, _sourceLine, std::string(word.begin(), std::prev(wordIter)));
				
				/// 뒤에 남은 문자열은 재귀호출로 처리.
				/// ex) functionCall(args) 같은 경우 functionCall을 생성하고 남은(args)를 재귀호출로 처리.
				if (wordIter != word.end())
				{
					std::string recheckWord(wordIter, word.end());
					GenerateToken(recheckWord);
				}

				return;
			}
			///숫자일 경우
			if (std::isdigit(word[0]))
			{
				/// 0xAB, 0b01010, 0o17등 2,8,16진수 처리
				if (word.size() != 1 && word[0] == '0')
				{
					if (word[1] == 'b' || word[1] == 'o' || word[1] == 'x')
					{
						char* remained = nullptr;

						auto iter = word.begin(); ++iter; ++iter;
						std::string tmp(iter, word.end());
						switch (word[1])
						{		///뒤에 문자열을 편리하게 처리하기위해 C함수를 사용. C++의 경우 문자열로 반환되지 않고 인덱스값으로 반환되기 때문.
						case 'b': num = strtol(tmp.c_str(), &remained, 2); break;
						case 'o': num = strtol(tmp.c_str(), &remained, 8); break;
						case 'x': num = strtol(tmp.c_str(), &remained, 16); break;
						}
						_tokenList.emplace_back(TokenID::Literal_Number, _sourceLine, num);

						if (remained != nullptr) { GenerateToken(remained); }
					}
				}
				///일반적인 10진수
				else
				{
					for (; wordIter != word.end() && (std::isdigit(*wordIter) || *wordIter == '.'); ++wordIter) {}
					num = std::stod(std::string(wordIter, word.end()));
					_tokenList.emplace_back(TokenID::Identifier, _sourceLine, num);

					if (wordIter != word.end()) { GenerateToken(std::string(wordIter, word.end())); }
				}

				return;
			}
			if (std::ispunct(word[0]))	///특수문자일 경우
			{
				// Todo : 기능구현
				return;
			}
			//앞에서 리턴해서 함수를 종료하지 못하면 정의하지 않은 문자열이므로 에러처리.
			throw Error(_sourceLine, "Undefined Charactor " +  word[0] + std::string("in ") + word);
		}
		catch(Error& e)
		{
			std::cout << "Lexer Error : " << e.what() << std::endl;
			exit(-1);
		}
		catch (...)
		{
			std::cout << "Lexer Error : UnknownError " << std::endl;
			exit(-1);
		}
	}

}