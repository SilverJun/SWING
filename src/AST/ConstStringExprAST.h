#ifndef _SWING_CONST_STRING_EXPR_AST_H_
#define _SWING_CONST_STRING_EXPR_AST_H_

#include "ExprAST.h"
#include "Type.h"

namespace swing
{
	class ConstStringExprAST : public ExprAST
	{
	public:
		std::string _string;
		llvm::Value* _strValue;

		static ExprPtr Create(TokenIter& iter)
		{
			auto* ast = new ConstStringExprAST();

			/// String Interpolation이 있으면 따로 계산을 해야한다.
			iter++->Expect(TokenID::Quotmark);
			iter->Is(TokenID::Literal_String);
			ast->_string = iter++->_name;
			iter++->Expect(TokenID::Quotmark);

			return ExprPtr(ast);
		}

		llvm::Value* CodeGen() override
		{
			/// ConstString 조립하기.
			/// String Interpolation 때문에 생긴 Expr을 수행하고 string을 만들어서 추가.
			_strValue = g_Builder.CreateGlobalString(_string.c_str());
			return g_Builder.CreateConstInBoundsGEP2_64(_strValue, 0, 0);
		}
	};
}

#endif
