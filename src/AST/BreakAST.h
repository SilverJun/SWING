#ifndef _SWING_BREAK_AST_
#define _SWING_BREAK_AST_
#include "SwingCompiler.h"
#include "StmtAST.h"

namespace swing
{
	class BreakAST : public StmtAST
	{
	public:
		static StmtPtr Create(TokenIter& iter)
		{
			auto* ast = new BreakAST();

			iter++->Expect(TokenID::Stmt_Break);

			return StmtPtr(ast);
		}
		
		llvm::Value* CodeGen() override
		{
			g_SwingCompiler->BreakCurrentBlock();
			return nullptr;
		}
	};
}

#endif
