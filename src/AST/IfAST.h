#ifndef _SWING_IF_AST_H_
#define _SWING_IF_AST_H_

#include "StmtAST.h"
#include "BlockAST.h"
#include "ExprAST.h"
#include "Type.h"

namespace swing
{
	class IfAST : public BlockAST
	{
	public:
		ExprAST::ExprPtr _conditions;
		BasePtr _then = nullptr;
		BasePtr _else = nullptr;
		llvm::BasicBlock* thenBlock = nullptr;
		llvm::BasicBlock* elseBlock = nullptr;
		llvm::BasicBlock* endBlock = nullptr;
		static StmtPtr Create(TokenIter& iter);
		llvm::Value* CodeGen() override;
	};
}

#endif
