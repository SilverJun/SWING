#ifndef _SWING_FOR_AST_H_
#define _SWING_FOR_AST_H_
#include "StmtAST.h"
#include "ExprAST.h"
#include "BlockAST.h"

namespace swing
{
	class ForAST : public BlockAST
	{
	public:
		SwingTable* _localTable;
		BasePtr _initialize;
		ExprAST::ExprPtr _conditions;
		BasePtr _increment;
		BasePtr _loopBody = nullptr;

		static StmtPtr Create(TokenIter& iter);
		llvm::Value* CodeGen() override;
	};
}

#endif
