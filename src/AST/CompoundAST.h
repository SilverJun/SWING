#ifndef _SWING_COMPOUND_AST_H_
#define _SWING_COMPOUND_AST_H_
#include "ExprAST.h"

namespace swing
{
	class CompoundAST : public ExprAST
	{
	public:
		ExprPtr _expr;

		static ExprPtr Create(TokenIter& iter);
		llvm::Value* CodeGen() override;
	};
}

#endif
