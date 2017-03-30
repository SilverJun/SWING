#ifndef _SWING_BASE_AST_H_
#define _SWING_BASE_AST_H_

#include "llvm/IR/Value.h"

class BaseAST
{
	virtual ~BaseAST() = delete;

public:
	virtual llvm::Value* CodeGen() = 0;

};

#endif
