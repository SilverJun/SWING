#ifndef _SWING_GUARD_AST_H_
#define _SWING_GUARD_AST_H_
#include "StmtAST.h"

namespace swing
{
	class GuardAST : StmtAST
	{
		llvm::Value* CodeGen() override
		{

		}
	};
}

#endif
