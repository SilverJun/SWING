#ifndef _SWING_IF_AST_H_
#define _SWING_IF_AST_H_

#include "StmtAST.h"
#include "BlockAST.h"
#include "ExprAST.h"
#include "Type.h"

namespace swing
{
	class IfAST : public StmtAST
	{
	public:
		std::vector<ExprAST::ExprPtr> _conditions;
		std::vector<BlockAST::BlockPtr> _blocks;
		llvm::PHINode* _phiNode;

		static StmtPtr Create(TokenIter& iter)
		{
			auto* ast = new IfAST();

			iter++->Expect(TokenID::Stmt_If);
			/// TODO : Table Must Pop!
			ast->_conditions.push_back(ExprAST::CreateTopLevelExpr(iter));
			ast->_blocks.push_back(BlockAST::Create(iter));

			while (iter->Is(TokenID::Stmt_Else))
			{
				++iter;
				if (iter->Is(TokenID::Stmt_If))
				{
					ast->_conditions.push_back(ExprAST::CreateTopLevelExpr(iter));
					ast->_blocks.push_back(BlockAST::Create(iter));
				}
				else
				{
					ast->_blocks.push_back(BlockAST::Create(iter));
					break;
				}
			}

			return StmtPtr(ast);
		}

		llvm::Value* CodeGen() override
		{
			/// TODO : Toy line:1000참고.
			/// PHI에 대해 자세히 알아보기.

			_phiNode = g_Builder.CreatePHI(Bool, _blocks.size(), "if");
		}
	};
}

#endif
