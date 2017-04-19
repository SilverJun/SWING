#include "SwingCompiler.h"

#include "llvm/Support/TargetSelect.h"
#include "Type.h"

namespace swing
{
	std::unique_ptr<SwingCompiler> SwingCompiler::_instance;
	std::once_flag SwingCompiler::_InitInstance;

	SwingCompiler::SwingCompiler() :_module("SwingCompiler", _llvmContext), _builder(_llvmContext)
	{
		llvm::InitializeNativeTarget();
		llvm::InitializeNativeTargetAsmParser();
		llvm::InitializeNativeTargetAsmPrinter();

		_tokenLists.push_back(TokenList());
		_lexer = new Lexer(&_tokenLists.back(), &_keywordList, &_operatorList);

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

			{ TokenID::Struct_Decl, "struct" },
			{ TokenID::Enum_Decl, "enum" },
			{ TokenID::Class_Decl, "class" },
			{ TokenID::Protocol_Decl, "protocol" },
			{ TokenID::Extension_Decl, "extension" },

			{ TokenID::Stmt_If, "if" },
			{ TokenID::Stmt_Else, "else" },
			{ TokenID::Stmt_Guard, "guard" },
			{ TokenID::Stmt_While, "while" },
			{ TokenID::Stmt_For, "for" },
			{ TokenID::Stmt_In, "in" }
		};
		_keywordList = kList;

		std::vector<Keyword> oList = {
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
		};
		_operatorList = oList;

		/// type which is used to generate
		_types = BuiltinType;

	}

	void SwingCompiler::SetProject(Project* project)
	{
		_project = project;
	}

	void SwingCompiler::CompileProject()
	{

	}

	void SwingCompiler::CompileFile(std::string file)
	{
		_lexer->LoadSourceFile(file);
		_lexer->GenerateTokenList();
	}

	std::string SwingCompiler::GenerateNameMangling(llvm::Function* func)
	{
		return "";
	}
}
