#ifndef _SWING_FUNC_DECL_AST_H_
#define _SWING_FUNC_DECL_AST_H_

#include "Token.h"
#include "Variable.h"
#include "DeclAST.h"
#include "BlockAST.h"

namespace swing
{
	class FunctionDeclAST : public DeclAST
	{
	public:
		llvm::FunctionType* _funcType;
		llvm::Function* _func;
		std::string _funcName;
		llvm::Type* _returnType;
		std::vector<Variable*> _args;
		BlockAST::BlockPtr _funcBody;

		static DeclPtr Create(TokenIter& iter);
		llvm::Value* CodeGen() override;
	};
}

#endif
