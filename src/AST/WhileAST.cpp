#include "WhileAST.h"
#include "Error.h"
#include "Type.h"
#include "BlockAST.h"

namespace swing
{
	StmtAST::StmtPtr WhileAST::Create(TokenIter& iter)
	{
		auto* ast = new WhileAST();

		iter++->Expect(TokenID::Stmt_While);

		ast->_conditions = ExprAST::CreateTopLevelExpr(iter);
		ast->_loopBody = BaseAST::Create(iter);

		return StmtPtr(ast);
	}

	llvm::Value* WhileAST::CodeGen()
	{
		llvm::Function* func = g_Builder.GetInsertBlock()->getParent();
		
		llvm::BasicBlock* condBlock = llvm::BasicBlock::Create(g_Context, "while.cond", func, _beforeBlock);
		llvm::BasicBlock* loopBlock = nullptr;
		llvm::BasicBlock* endBlock = llvm::BasicBlock::Create(g_Context, "while.end", func);

		g_SwingCompiler->_breakBlocks.push_back(endBlock);

		auto* loopBlockAST = dynamic_cast<BlockAST*>(_loopBody.get());
		/// BlockAST이면
		if (loopBlockAST)
		{
			loopBlockAST->_blockInst = llvm::BasicBlock::Create(g_Context, "while.loop", func, _beforeBlock);
			loopBlockAST->_alreadyInsertBlock = true;
			loopBlockAST->_beforeBlock = endBlock;
			loopBlock = loopBlockAST->_blockInst;
		}
		else
		{
			loopBlock = llvm::BasicBlock::Create(g_Context, "while.loop", func);
		}
		g_Builder.CreateBr(condBlock);
		g_Builder.SetInsertPoint(condBlock);
		g_Builder.CreateCondBr(g_Builder.CreateICmpEQ(_conditions->CodeGen(), TrueValue), loopBlock, endBlock);
		
		g_Builder.SetInsertPoint(loopBlock);
		loopBlockAST->CodeGen();
		g_Builder.CreateBr(condBlock);

		g_Builder.SetInsertPoint(endBlock);
		g_SwingCompiler->_breakBlocks.pop_back();
		return nullptr;
	}
}
