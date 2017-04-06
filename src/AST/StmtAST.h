#ifndef _SWING_STMT_AST_H_
#define _SWING_STMT_AST_H_

#include "BaseAST.h"

namespace swing
{
	class StmtAST : public BaseAST
	{
	public:
		llvm::Value* CodeGen() override
		{
			return nullptr;
		}
	};
}

#endif
