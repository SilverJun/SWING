#ifndef _SWING_LIB_DECL_AST_
#define _SWING_LIB_DECL_AST_
#include "DeclAST.h"
#include "FunctionDeclAST.h"

namespace swing
{
	class SwingLibDeclAST : public DeclAST
	{
	public:
		FunctionDeclAST* _output;
		FunctionDeclAST* _outputInt;
		FunctionDeclAST* _outputFloat;
		FunctionDeclAST* _outputDouble;

		static DeclPtr Create();
		llvm::Value* CodeGen() override;
	};
}

#endif
