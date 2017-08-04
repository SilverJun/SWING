#include "AtomAST.h"
#include "ConstValueAST.h"
#include "VariableAST.h"
#include "ConstStringExprAST.h"
#include "CompoundAST.h"
#include "FunctionCallAST.h"

namespace swing
{
	ExprAST::ExprPtr AtomAST::Create(TokenIter& iter)
	{
		/// 변수호출, 함수호출, 상수값, 문자열, 문자, nilValue, 괄호 처리.

		/// Identifier라면 변수이거나 함수호출이다.
		if (iter->Is(TokenID::Identifier))
		{
			if (next(iter)->Is(TokenID::OpenSmall))
				return FunctionCallAST::Create(iter);

			return VariableExprAST::Create(iter);
		}
		switch (iter->_id)
		{
		case TokenID::Boolean_Value:
		case TokenID::Literal_Integer:
		case TokenID::Literal_Float:
		case TokenID::Literal_Double:
		case TokenID::Literal_Letter:
			return ConstValueExprAST::Create(iter);
		case TokenID::Quotmark:
			return ConstStringExprAST::Create(iter);
		case TokenID::OpenSmall:
			return CompoundAST::Create(iter);
		default:
			return nullptr;
		}
	}

	llvm::Value* AtomAST::CodeGen()
	{
		return nullptr;
	}
}
