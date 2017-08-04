#include "UnaryOpAST.h"
#include "VariableAST.h"
#include "ConstValueAST.h"
#include "ConstStringExprAST.h"

namespace swing
{
	ExprAST::ExprPtr UnaryOpAST::Create(TokenIter& iter)
	{
		auto* ast = new UnaryOpAST();

		/// prefix 이라면,
		if (iter->Is(TokenID::Operator))
		{
			ast->_opType = *g_SwingCompiler->FindPreFixOp(iter->_name);
			++iter;
			ast->_value = AtomAST::Create(iter);
			
			return ExprPtr(ast);
		}

		ast->_value = AtomAST::Create(iter);

		/// postfix op처리.
		if (iter->Is(TokenID::Operator))
		{
			ast->_opType = *g_SwingCompiler->FindPostFixOp(iter->_name);
			++iter;
		}

		return ExprPtr(ast);
	}

	llvm::Value* UnaryOpAST::CodeGen()
	{
		/// Prefix op, Postfix op 처리.
		switch (_opType._tokenID)
		{
		case TokenID::Logical_Not:
			return g_Builder.CreateNot(_value->CodeGen(), "nottmp");
		case TokenID::Bitwise_Not:
			return g_Builder.CreateNeg(_value->CodeGen(), "negtmp");
		//case TokenID::Optional_Nilable:
		//	return g_Builder.CreateNot(_value->CodeGen(), "nottmp");
		//case TokenID::Optional_Binding:
		//	return g_Builder.CreateNot(_value->CodeGen(), "nottmp");
		}

		/// TODO : 유저 정의 op들 Function call 처리
		return _value->CodeGen();
	}
}
