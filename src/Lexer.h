#ifndef _SWING_LEXER_H_
#define _SWING_LEXER_H_

#include "Token.h"
#include <vector>

namespace swing
{

	class Lexer
	{
		struct Keyword
		{
			TokenID _id;
			std::string _word;

			Keyword(TokenID id, std::string word) : _id(id), _word(word) {}
		};

		TokenList _tokenList;
		std::vector<Keyword> _keywordList;
		std::string _sourceCode;

		int _sourceLine = 0;

	public:
		void Initialize();
		void LoadSourceFile(std::string filename);
		void GenerateTokenList();

	private:
		void GenerateToken(std::string word);


	public:
		TokenList GetTokenList() const
		{
			return _tokenList;
		}
	};


}

#endif
