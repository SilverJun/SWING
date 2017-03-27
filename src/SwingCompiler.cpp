#include "SwingCompiler.h"

namespace swing
{
	void SwingCompiler::InitializeCompiler()
	{
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

		std::vector<Keyword> oList = {
			{ TokenID::Cross, "+" },
			{ TokenID::Hyphen, "-" },
			{ TokenID::Asterisk, "*" },
			{ TokenID::ForwardSlash, "/" },
			{ TokenID::Percent, "%" },
			{ TokenID::Equal, "=" },
			{ TokenID::Bitwise_And, "&" },
			{ TokenID::Bitwise_Or, "|" },
			{ TokenID::Bitwise_Not, "~" },
			{ TokenID::Logical_And, "&&" },
			{ TokenID::Logical_Or, "||" },
			{ TokenID::Logical_Not, "!" },
		};

		_operatorList.clear();
		_operatorList = oList;
	}

	void SwingCompiler::CompileFile(std::string file)
	{
		_lexer->LoadSourceFile(file);
		_lexer->GenerateTokenList();
	}
}
