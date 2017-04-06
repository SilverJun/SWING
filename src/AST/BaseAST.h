#ifndef _SWING_BASE_AST_H_
#define _SWING_BASE_AST_H_

#include "llvm/IR/Value.h"

namespace swing
{
	class BaseAST
	{
	public:
		virtual ~BaseAST() {}
		virtual llvm::Value* CodeGen() = 0;
	};
}

#endif
