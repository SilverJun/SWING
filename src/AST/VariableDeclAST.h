#ifndef _SWING_VARIABLE_DECL_AST_H_
#define _SWING_VARIABLE_DECL_AST_H_

#include "DeclAST.h"
#include "Error.h"
#include "Variable.h"
#include "ExprAST.h"

namespace swing
{
	class VariableDeclAST : public DeclAST
	{
	public:
		Variable* _variable = nullptr;
		ExprAST::ExprPtr _initValue = nullptr;

		static DeclPtr Create(TokenIter& iter);
		llvm::Value* CodeGen() override;
	};
}

#endif
