#ifndef _SWING_LEXER_H_
#define _SWING_LEXER_H_

#include "Token.h"
#include "Operator.h"
#include <vector>
#include "Source.h"
#include "SwingCompiler.h"

namespace swing
{
	class Lexer
	{
		static std::vector<Keyword> _keywordList;
		TokenList* _tokenList;
		std::string* _sourceCode;
		std::string* _sourceName;
		int _sourceLine;


	public:
		Lexer();

		void LexSource(Source* src);

	private:
		void LexStart();
		void LexCharacter(std::string::iterator& iter);
		void LexNumber(std::string::iterator& iter);
		void LexPunct(std::string::iterator& iter);
		void LexCharacterLiteral(std::string::iterator& iter);
		void LexEscapeSquence(std::string::iterator& iter);
		void LexStringLiteral(std::string::iterator& iter);
		void SkipToLineAnnotation(std::string::iterator& iter);
		void SkipToBlockAnnotation(std::string::iterator& iter);
	};
}

#endif
