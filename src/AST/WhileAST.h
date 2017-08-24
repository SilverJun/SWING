#ifndef _SWING_WHILE_AST_H_
#define _SWING_WHILE_AST_H_
#include "StmtAST.h"
#include "ExprAST.h"
#include "BlockAST.h"

namespace swing
{
	class WhileAST : public BlockAST
	{
	public:
		ExprAST::ExprPtr _conditions;
		BasePtr _loopBody = nullptr;
		llvm::BasicBlock* condBlock;
		llvm::BasicBlock* loopBlock;
		llvm::BasicBlock* endBlock;

		static StmtPtr Create(TokenIter& iter);
		llvm::Value* CodeGen() override;
	};
}

#endif
