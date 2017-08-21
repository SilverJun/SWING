#ifndef _SWING_BLOCK_AST_H_
#define _SWING_BLOCK_AST_H_
#include "StmtAST.h"
#include <unordered_map>
#include "SwingTable.h"
#include "SwingCompiler.h"
#include "Error.h"

namespace swing
{
	class BlockAST : public StmtAST
	{
	public:
		using BlockPtr = std::shared_ptr<BlockAST>;

		bool _alreadyInsertBlock = false;
		SwingTable* _localTable;
		llvm::BasicBlock* _beforeBlock = nullptr;
		llvm::BasicBlock* _blockInst = nullptr;

		ASTList _astList;

		//void Dump() override;
		static BlockPtr Create(TokenIter& iter)
		{
			auto* ast = new BlockAST();
			ast->_localTable = new SwingTable();
			//g_Table->AddVariable(ast->_localTable);
			iter->Expect(TokenID::OpenMedium); ++iter;
			while (!iter->Is(TokenID::CloseMedium))
			{
				if (iter->_id == TokenID::Eof) 
					throw ParsingError(*iter, "in BlockAST, Unexpected EOF Error");
				ast->_astList.push_back(BaseAST::Create(iter));
			}
			++iter;
			return BlockPtr(ast);
		}

		llvm::Value* CodeGen() override
		{
			/// Add blockTable as ChildTable
			/// Create Block
			g_Table->AddVariable(_localTable);

			if (!_alreadyInsertBlock)
			{
				_blockInst = llvm::BasicBlock::Create(g_Context);
				g_Builder.SetInsertPoint(_blockInst);
			}
			
			g_SwingCompiler->PushIRBuilder(llvm::IRBuilder<>(_blockInst));

			for (auto ast : _astList)
				ast->CodeGen();

			g_SwingCompiler->PopIRBuilder();

			g_Table->PopLocalTable();

			return nullptr;
		}
	};
}
#endif
