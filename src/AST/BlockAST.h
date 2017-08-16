#ifndef _SWING_BLOCK_AST_H_
#define _SWING_BLOCK_AST_H_
#include "BaseAST.h"
#include <unordered_map>
#include "SwingTable.h"
#include "SwingCompiler.h"
#include "Error.h"

namespace swing
{
	class BlockAST : public BaseAST
	{
	public:
		using BlockPtr = std::shared_ptr<BlockAST>;

		SwingTable* _localTable;
		llvm::Function* _func;
		llvm::BasicBlock* _blockInst;

		ASTList _astList;

		//void Dump() override;
		static BlockPtr Create(TokenIter& iter)
		{
			auto* ast = new BlockAST();
			ast->_localTable = new SwingTable();
			g_Table.AddVariable(ast->_localTable);
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
			/*_blockInst = llvm::BasicBlock::Create(g_Context, "entry", _func != nullptr ? _func : nullptr);
			g_SwingCompiler->PushIRBuilder(llvm::IRBuilder<>(_blockInst));
			g_Builder.SetInsertPoint(_blockInst);
*/
			for (auto ast : _astList)
				ast->CodeGen();
			
			return nullptr;
		}
	};
}
#endif
