#include "ForAST.h"
#include "Type.h"

namespace swing
{
	StmtAST::StmtPtr ForAST::Create(TokenIter& iter)
	{
		auto* ast = new ForAST();
		ast->_localTable = new SwingTable();

		iter++->Expect(TokenID::Stmt_For);

		ast->_initialize = BaseAST::Create(iter);
		iter++->Expect(TokenID::SemiColon);
		ast->_conditions = ExprAST::CreateTopLevelExpr(iter);
		iter++->Expect(TokenID::SemiColon);
		ast->_increment = BaseAST::Create(iter);
		ast->_loopBody = BaseAST::Create(iter);

		return StmtPtr(ast);
	}

	llvm::Value* ForAST::CodeGen()
	{
		llvm::Function* func = g_Builder.GetInsertBlock()->getParent();

		llvm::BasicBlock* condBlock = llvm::BasicBlock::Create(g_Context, "for.cond", func, _beforeBlock);
		llvm::BasicBlock* incBlock = llvm::BasicBlock::Create(g_Context, "for.inc", func, _beforeBlock);
		llvm::BasicBlock* loopBlock = nullptr;
		llvm::BasicBlock* endBlock = llvm::BasicBlock::Create(g_Context, "for.end", func);

		g_SwingCompiler->_breakBlocks.push_back(endBlock);

		auto* loopBlockAST = dynamic_cast<BlockAST*>(_loopBody.get());
		/// BlockAST이면
		if (loopBlockAST)
		{
			loopBlockAST->_blockInst = llvm::BasicBlock::Create(g_Context, "for.loop", func, _beforeBlock);
			loopBlockAST->_alreadyInsertBlock = true;
			loopBlockAST->_beforeBlock = endBlock;
			loopBlock = loopBlockAST->_blockInst;
		}
		else
		{
			loopBlock = llvm::BasicBlock::Create(g_Context, "for.loop", func);
		}

		g_Table->AddVariable(_localTable);
		
		_initialize->CodeGen();
		g_Builder.CreateBr(condBlock);
		
		g_Builder.SetInsertPoint(condBlock);
		g_Builder.CreateCondBr(g_Builder.CreateICmpEQ(_conditions->CodeGen(), TrueValue), loopBlock, endBlock);
		g_Builder.SetInsertPoint(loopBlock);
		loopBlockAST->CodeGen();
		g_Builder.CreateBr(incBlock);
		g_Builder.SetInsertPoint(incBlock);
		_increment->CodeGen();
		g_Builder.CreateBr(condBlock);
		
		g_Table->PopLocalTable();

		g_Builder.SetInsertPoint(endBlock);
		g_SwingCompiler->_breakBlocks.pop_back();
		return nullptr;
	}
}
