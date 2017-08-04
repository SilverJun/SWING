#ifndef _SWING_ATOM_AST_H_
#define _SWING_ATOM_AST_H_
#include "ExprAST.h"

namespace swing
{
	class AtomAST : ExprAST
	{
	public:
		static ExprPtr Create(TokenIter& iter);
		llvm::Value* CodeGen() override;
	};
}

#endif
