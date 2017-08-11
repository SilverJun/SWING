#ifndef _SWING_CONST_VALUE_EXPR_AST_H_
#define _SWING_CONST_VALUE_EXPR_AST_H_

#include "ExprAST.h"
#include "Type.h"
#include "Error.h"

namespace swing
{
	class ConstValueExprAST : public ExprAST
	{
		enum class ConstValueType
		{
			BoolValue,
			CharValue,
			IntValue,
			FloatValue,
			DoubleValue
		};

	public:
		union
		{
			bool _bool;
			char _char;
			int _int;
			float _float;
			double _double;
		};

		//bool _nil;
		ConstValueType _type;

		static ExprPtr Create(TokenIter& iter)
		{
			/// ''문자, ""문자열, 숫자, 부동소수점 숫자, 불대수.
			
			auto* ast = new ConstValueExprAST();
			/// Bool 인지 체크.
			if (iter->Is(TokenID::Boolean_Value))
			{
				ast->_bool = iter->_name == "true" ? true : false;
				ast->_type = ConstValueType::BoolValue;
				++iter;
				return ExprPtr(ast);
			}

			switch (iter->_type)
			{
			case Token::TokenTypeTag::_char:
				ast->_char = iter++->_char;
				ast->_type = ConstValueType::CharValue;
				return ExprPtr(ast);
			case Token::TokenTypeTag::_int:
				ast->_int = iter++->_int;
				ast->_type = ConstValueType::IntValue;
				return ExprPtr(ast);
			case Token::TokenTypeTag::_float:
				ast->_float = iter++->_float;
				ast->_type = ConstValueType::FloatValue;
				return ExprPtr(ast);
			case Token::TokenTypeTag::_double:
				ast->_double = iter++->_double;
				ast->_type = ConstValueType::DoubleValue;
				return ExprPtr(ast);
			case Token::TokenTypeTag::_notuse:
				throw ParsingError(*iter, "Can't parsing ConstValue which tag _notuse");
			}
			throw ParsingError(*iter, "UnaryOpAST Error occur, Unexpected Error.");
		}

		llvm::Value* CodeGen() override 
		{
			switch (_type)
			{
			case ConstValueType::BoolValue:
				return llvm::ConstantInt::get(Bool, llvm::APInt(8, _bool));
			case ConstValueType::CharValue:
				return llvm::ConstantInt::get(Char, llvm::APInt(8, _char));
			case ConstValueType::IntValue:
				return llvm::ConstantInt::get(Int, llvm::APInt(32, _int));
			case ConstValueType::FloatValue:
				return llvm::ConstantFP::get(Float, static_cast<double>(_float));
			case ConstValueType::DoubleValue:
				return llvm::ConstantFP::get(Double, _double);
			/*case ConstValueType::NilValue:
				return llvm::ConstantPointerNull::get(llvm::Type::getInt32PtrTy(g_Context));*/
			}
			return nullptr;
		}

		llvm::Type* GetType() override
		{
			switch (_type)
			{
			case ConstValueType::BoolValue:
				return Bool;
			case ConstValueType::CharValue:
				return Char;
			case ConstValueType::IntValue:
				return Int;
			case ConstValueType::FloatValue:
				return Float;
			case ConstValueType::DoubleValue:
				return Double;
				/*case ConstValueType::NilValue:
				return llvm::ConstantPointerNull::get(llvm::Type::getInt32PtrTy(g_Context));*/
			}
			return nullptr;
		}
	};
}

#endif
