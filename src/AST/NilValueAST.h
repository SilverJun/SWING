#ifndef _SWING_COMPOUND_AST_H_
#define _SWING_COMPOUND_AST_H_
#include "ExprAST.h"

namespace swing
{
	class NilValueAST : public ExprAST
	{
	public:
		static ExprPtr Create(TokenIter& iter);
		llvm::Value* CodeGen() override;
	};
}

#endif
