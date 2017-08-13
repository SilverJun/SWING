#ifndef _SWING_VARIABLE_EXPR_AST_H_
#define _SWING_VARIABLE_EXPR_AST_H_

#include "ExprAST.h"
#include "Variable.h"
#include "SwingCompiler.h"
#include "StructType.h"
#include "Property.h"

namespace swing
{
	class VariableExprAST : public ExprAST
	{
	public:
		std::vector<std::string> _variableName;


		static ExprPtr Create(TokenIter& iter)
		{
			auto* ast = new VariableExprAST();

			iter->Expect(TokenID::Identifier);

			ast->_variableName.push_back(iter++->_name);

			while (iter->Is(TokenID::Dot))
			{
				++iter;
				if (iter->Is(TokenID::Identifier))
					ast->_variableName.push_back(iter++->_name);
			}
			/// 함수이면 어떻하지?

			return ExprPtr(ast);
		}

		llvm::Value* CodeGen() override
		{
			/// 그냥 변수
			if (_variableName.size() == 1)
				return g_Builder.CreateLoad(g_Table.Find(_variableName.front())->GetValue());
			
			/*
				%val22 = getelementptr inbounds %struct.test2, %struct.test2* %MyStruct, i32 0, i32 1
				%val13 = getelementptr inbounds %struct.test1, %struct.test1* %val22, i32 0, i32 0
				%0 = load i32, i32* %val13, align 4
				ret i32 %0
			 */

			/// 멤버 참조 연산이 있을 때.
			std::string name = _variableName.front();
			
			StructType* structType = g_SwingCompiler->_structs[g_Table.Find(name)->GetType()->getStructName()];
			//return structType->GetElementPtr(this->_variableName);
			return g_Builder.CreateLoad(structType->GetElementPtr(this->_variableName));
		}

		llvm::Value* CodeGenRef()
		{
			if (_variableName.size() == 1)
				return g_Table.Find(_variableName.front())->GetValue();

			/// 멤버 참조 연산이 있을 때.
			std::string name = _variableName.front();

			StructType* structType = g_SwingCompiler->_structs[g_Table.Find(name)->GetType()->getStructName()];
			return structType->GetElementPtr(this->_variableName);
		}
	};
}

#endif
