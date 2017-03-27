#ifndef _SWING_LEXER_H_
#define _SWING_LEXER_H_

#include "Token.h"
#include "Operator.h"
#include <vector>

namespace swing
{
	class Lexer
	{
		std::vector<Keyword>* _keywordList;
		std::vector<Keyword>* _operatorList;
		TokenList* _tokenList;
		std::string _sourceCode;

		int _sourceLine;

	public:
		Lexer::Lexer(TokenList* tokList, std::vector<Keyword>* keywords, std::vector<Keyword>* operators);

		void InitializeKeyword(std::vector<Keyword>* keywords);

		void InitializeLexer();

		void LoadSourceFile(std::string filename);
		void SetSourceCode(std::string source);

		void GenerateTokenList();

		void LexCharacter(std::string::iterator& iter);
		void LexNumber(std::string::iterator& iter);
		void LexPunct(std::string::iterator& iter);
		void LexCharacterLiteral(std::string::iterator& iter);
		void LexEscapeSquence(std::string::iterator& iter);
		void LexStringLiteral(std::string::iterator& iter);
		void SkipToLineAnnotation(std::string::iterator& iter);
		void SkipToBlockAnnotation(std::string::iterator& iter);

		void SetSourceLine(int line)
		{
			_sourceLine = line;
		}
	};

}

#endif
