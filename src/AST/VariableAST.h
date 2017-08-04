#ifndef _SWING_VARIABLE_EXPR_AST_H_
#define _SWING_VARIABLE_EXPR_AST_H_

#include "ExprAST.h"
#include "Variable.h"
#include "SwingCompiler.h"

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

			ast->_variableName = iter->_name;
			++iter;

			return ExprPtr(ast);
		}

		llvm::Value* CodeGen() override
		{
			return g_Table.Find(_variableName)->GetValue();
		}
	};
}

#endif
