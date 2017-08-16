#include "CompoundAST.h"

swing::ExprAST::ExprPtr swing::CompoundAST::Create(TokenIter& iter)
{
	auto* ast = new CompoundAST();
	++iter;
	ast->_expr = ExprAST::CreateTopLevelExpr(iter);
	iter++->Expect(TokenID::CloseSmall);
	return ExprPtr(ast);
}

llvm::Value* swing::CompoundAST::CodeGen()
{
	return _expr->CodeGen();
}
