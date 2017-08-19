#ifndef _SWING_RETURN_AST_H_
#define _SWING_RETURN_AST_H_

#include "StmtAST.h"
#include "SwingCompiler.h"
#include "ExprAST.h"

namespace swing
{
	class ReturnAST : public StmtAST
	{
	public:
		bool _isVoid;
		ExprAST::ExprPtr _retVal;

		static StmtPtr Create(TokenIter& iter)
		{
			auto* ast = new ReturnAST();
			
			iter++->Expect(TokenID::Stmt_Return);

			if (iter->Is(TokenID::Type_Void))
			{
				++iter;
				ast->_isVoid = true;
			}
			else
			{
				ast->_isVoid = false;
				ast->_retVal = ExprAST::CreateTopLevelExpr(iter);
			}

			return StmtPtr(ast);
		}

		llvm::Value* CodeGen() override
		{
			return _isVoid == true ? g_Builder.CreateRetVoid() : g_Builder.CreateRet(_retVal.get()->CodeGen());
		}
	};
}

#endif
