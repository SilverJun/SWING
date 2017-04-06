#ifndef _SWING_SWITCH_AST_H_
#define _SWING_SWITCH_AST_H_
#include "StmtAST.h"

namespace swing
{
	class SwitchAST : StmtAST
	{
		llvm::Value* CodeGen() override
		{

		}
	};
}

#endif
