#include "IfAST.h"

namespace swing
{
	StmtAST::StmtPtr IfAST::Create(TokenIter& iter)
	{
		auto* ast = new IfAST();

		iter++->Expect(TokenID::Stmt_If);

		ast->_conditions = ExprAST::CreateTopLevelExpr(iter);
		ast->_then = BaseAST::Create(iter);

		if (iter->Is(TokenID::Stmt_Else))
		{
			++iter;
			ast->_else = BaseAST::Create(iter);
		}

		return StmtPtr(ast);
	}

	llvm::Value* IfAST::CodeGen()
	{
		/// if.then
		/// if.else
		/// if.end

		llvm::Function* func = g_Builder.GetInsertBlock()->getParent();

		llvm::Value* conditionValue = _conditions->CodeGen();
		if (!conditionValue)
			throw Error("If condition is null!");

		conditionValue = g_Builder.CreateICmpEQ(conditionValue, TrueValue);
		endBlock = llvm::BasicBlock::Create(g_Context, "if.end", func);

		auto* thenBlockAST = dynamic_cast<BlockAST*>(_then.get());
		/// BlockAST이면
		if (thenBlockAST)
		{
			thenBlockAST->_blockInst = llvm::BasicBlock::Create(g_Context, "if.then", func, _beforeBlock);
			thenBlockAST->_alreadyInsertBlock = true;
			thenBlockAST->_beforeBlock = endBlock;
			thenBlock = thenBlockAST->_blockInst;
		}
		else
		{
			thenBlock = llvm::BasicBlock::Create(g_Context, "if.then", func, _beforeBlock);
		}

		BlockAST* elseBlockAST = nullptr;
		if (_else) /// else문이 없는 if문 하나.
		{
			elseBlockAST = dynamic_cast<BlockAST*>(_else.get());
			if (elseBlockAST)
			{
				elseBlockAST->_blockInst = llvm::BasicBlock::Create(g_Context, "if.else", func, _beforeBlock);
				elseBlockAST->_alreadyInsertBlock = true;
				thenBlockAST->_beforeBlock = endBlock;
				elseBlock = elseBlockAST->_blockInst;
			}
			else
				elseBlock = llvm::BasicBlock::Create(g_Context, "if.else", func, _beforeBlock);
		}

		g_Builder.CreateCondBr(conditionValue, thenBlock, elseBlock == nullptr ? endBlock : elseBlock);

		g_Builder.SetInsertPoint(thenBlock);
		g_SwingCompiler->_breakBlocks.push_back(endBlock);
		_then->CodeGen();
		g_Builder.CreateBr(g_SwingCompiler->GetEndBlock());

		if (_else)
		{
			g_Builder.SetInsertPoint(elseBlock);
			g_SwingCompiler->_breakBlocks.push_back(endBlock);
			_else->CodeGen();
			g_Builder.CreateBr(g_SwingCompiler->GetEndBlock());
		}

		if (g_SwingCompiler->GetEndBlock() == endBlock)
			g_SwingCompiler->_breakBlocks.pop_back();

		g_Builder.SetInsertPoint(endBlock);

		return nullptr;
	}
}
