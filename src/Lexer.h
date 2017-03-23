#ifndef _SWING_LEXER_H_
#define _SWING_LEXER_H_

#include "Token.h"
#include <vector>

namespace swing
{
	class Lexer
	{
	public:
		struct Keyword
		{
			TokenID _id;
			std::string _word;

			Keyword(TokenID id, std::string word) : _id(id), _word(word) {}
		};

	private:
		static std::vector<Keyword> _keywordList;

		TokenList _tokenList;
		std::string _sourceCode;

		int _sourceLine = 0;

	public:
		Lexer::Lexer();

		static void InitializeKeyword();

		void Initialize();

		void LoadSourceFile(std::string filename);
		void SetSourceCode(std::string source);

		void GenerateTokenList();

		void LexCharacter(std::string::iterator& iter);
		void LexNumber(std::string::iterator& iter);
		void LexPunct(std::string::iterator& iter);
		void LexStringLiteral(std::string::iterator& iter);
		void SkipToLineAnnotation(std::string::iterator& iter);
		void SkipToBlockAnnotation(std::string::iterator& iter);
		
		TokenList GetTokenList() const
		{
			return _tokenList;
		}
	};

}

#endif
