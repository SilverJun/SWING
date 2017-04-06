#ifndef _SWING_FUNC_DECL_AST_H_
#define _SWING_FUNC_DECL_AST_H_

#include "Token.h"
#include <llvm/IR/Function.h>
#include "StmtAST.h"

namespace swing
{
	class FunctionDeclAST : StmtAST
	{
		
	public:
		llvm::Function* CodeGen() override
		{
			
		}
	};
}

#endif
