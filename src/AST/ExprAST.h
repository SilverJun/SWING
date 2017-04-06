#ifndef _SWING_EXPR_AST_H_
#define _SWING_EXPR_AST_H_

#include "BaseAST.h"
#include "SwingCompiler.h"

namespace swing
{
	class ExprAST : public BaseAST
	{
	public:
		virtual ~ExprAST() {}
		llvm::Value* CodeGen() override
		{
			return;
		}
	};
}

#endif
