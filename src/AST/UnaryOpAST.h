#ifndef _SWING_UNARY_OP_AST_
#define _SWING_UNARY_OP_AST_
#include "Operator.h"
#include "ExprAST.h"
#include "AtomAST.h"

namespace swing
{
	class UnaryOpAST : public ExprAST
	{
	public:
		OperatorType _opType;
		ExprPtr _value;

		static ExprPtr Create(TokenIter& iter);
		llvm::Value* CodeGen() override;
	};
}

#endif
