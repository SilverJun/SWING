#ifndef _SWING_BINARY_OP_AST_
#define _SWING_BINARY_OP_AST_
#include "Operator.h"
#include "ExprAST.h"

namespace swing
{
	class BinaryOpAST : public ExprAST
	{
	public:
		ExprList _exprList;
		
		std::vector<OperatorType*> _opTypes;
		std::vector<OperatorType*> _opCandidates;

		~BinaryOpAST();

		static ExprPtr Create(TokenIter& iter, int PrecedenceLevel);
		llvm::Type* GetType() override;
		llvm::Value* CodeGen() override;
	};
}

#endif
