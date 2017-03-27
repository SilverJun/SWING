#pragma once
#include "Lexer.h"
#include "Operator.h"
#include "Token.h"

namespace swing
{
	class SwingCompiler
	{
		std::vector<Keyword> _keywordList;
		std::vector<Keyword> _operatorList;
		std::list<TokenList> _tokenLists;

		Lexer* _lexer;

		//ProjectManager

	public:
		void InitializeCompiler();
		
		void CompileProject(/*swing::project*/);
		void CompileFile(std::string file);



	};

}

