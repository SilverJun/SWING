#ifndef _SWING_STMT_AST_H_
#define _SWING_STMT_AST_H_

#include "BaseAST.h"

namespace swing
{
	class StmtAST : public BaseAST
	{
	public:
		using StmtPtr = std::shared_ptr<StmtAST>;

		static StmtPtr Create(TokenIter& iter)
		{
			/// TODO : 전체적인 Stmt처리?
			return nullptr;
		}

		llvm::Value* CodeGen() override
		{
			return nullptr;
		}
	};
}

#endif
