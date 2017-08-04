#include "CompoundAST.h"

/// return ExprAST::CreateTopExprAST(iter);
swing::ExprAST::ExprPtr swing::CompoundAST::Create(TokenIter& iter)
{
	auto* ast = new CompoundAST();
	ast->_expr = ExprAST::CreateTopLevelExpr(iter);
	return ExprPtr(ast);
}

llvm::Value* swing::CompoundAST::CodeGen()
{
	return _expr->CodeGen();
}
