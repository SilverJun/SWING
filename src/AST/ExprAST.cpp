#include "ExprAST.h"
#include "BinaryOpAST.h"

namespace swing
{
	ExprAST::ExprPtr ExprAST::CreateTopLevelExpr(TokenIter& iter)
	{
		/// Binary Operation Parse.
		return BinaryOpAST::Create(iter, OperatorType::Precedence_Min);
	}

	llvm::Value* ExprAST::CodeGen()
	{
		return nullptr;
	}
}
