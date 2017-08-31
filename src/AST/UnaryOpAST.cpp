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
		auto* op = g_SwingCompiler->FindPreFixOp(iter->_name);
		if (op)
		{
			ast->_opType = *op;
			++iter;
			ast->_value = AtomAST::Create(iter);
			
			return ExprPtr(ast);
		}

		ast->_value = AtomAST::Create(iter);

		/// postfix op처리.
		op = g_SwingCompiler->FindPostFixOp(iter->_name);
		if (op)
		{
			ast->_opType = *op;
			++iter;

			return ExprPtr(ast);
		}

		return ast->_value;
	}

	llvm::Value* UnaryOpAST::CodeGen()
	{
		/// Prefix op, Postfix op 처리.
		switch (_opType._tokenID)
		{
		case TokenID::Logical_Not:
			return g_Builder.CreateNot(_value->CodeGen());
		case TokenID::Arithmetic_Subtract:
			{
			auto* lhs = _value->CodeGen();
			return g_Builder.CreateMul(lhs, llvm::ConstantInt::get(lhs->getType(), -1, true));
			}
		//case TokenID::Bitwise_Not:
		//	return g_Builder.CreateNeg(_value->CodeGen());
		//case TokenID::Optional_Nilable:
		//case TokenID::Optional_Binding:
		}

		/// TODO : 유저 정의 op들 Function call 처리
		return _value->CodeGen();
	}

	llvm::Type* UnaryOpAST::GetType()
	{
		/// TODO : 타입 추론 보강하기.
		return _value->GetType();
	}
}
