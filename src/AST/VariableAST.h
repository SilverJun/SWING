#ifndef _SWING_VARIABLE_EXPR_AST_H_
#define _SWING_VARIABLE_EXPR_AST_H_

#include "ExprAST.h"
#include "Variable.h"
#include "SwingCompiler.h"
#include "StructType.h"
#include "Property.h"
#include "FunctionCallAST.h"

namespace swing
{
	class VariableExprAST : public ExprAST
	{
	public:
		std::string _variableName;


		static ExprPtr Create(TokenIter& iter)
		{
			auto* ast = new VariableExprAST();

			iter->Expect(TokenID::Identifier);

			ast->_variableName = iter++->_name;
			/*
			while (iter->Is(TokenID::Dot))
			{
				++iter;
				if (iter->Is(TokenID::Identifier))
					ast->_variableName.push_back(iter++->_name);
			}
			/// 함수이면 어떻하지?
			if (iter->Is(TokenID::OpenSmall))
			{
				--iter;
				return FunctionCallAST::Create(iter);
			}
			*/

			return ExprPtr(ast);
		}

		llvm::Value* CodeGen() override
		{
			/// 그냥 변수
			//if (_variableName.size() == 1)
			Variable* value = g_Table->Find(_variableName);
			return g_Builder.CreateLoad(value->GetValue());
			/*
			/// 멤버 참조 연산이 있을 때.
			std::string name = _variableName.front();
			
			StructType* structType = g_SwingCompiler->_structs[g_Table.Find(name)->GetType()->getStructName()];
			//return structType->GetElementPtr(this->_variableName);
			return g_Builder.CreateLoad(structType->GetElementPtr(this->_variableName));
			*/
		}

		llvm::Value* CodeGenRef() override
		{
			/// 그냥 변수
			//if (_variableName.size() == 1)
			Variable* value = g_Table->Find(_variableName);
			return value->GetValue();
			/*
			/// 멤버 참조 연산이 있을 때.
			std::string name = _variableName.front();

			StructType* structType = g_SwingCompiler->_structs[g_Table.Find(name)->GetType()->getStructName()];
			return structType->GetElementPtr(this->_variableName);*/
		}
	};
}

#endif
