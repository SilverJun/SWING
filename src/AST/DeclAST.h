#ifndef _SWING_DECL_AST_H_
#define _SWING_DECL_AST_H_

#include "BaseAST.h"

namespace swing
{
	class DeclAST : public BaseAST
	{
	public:
		DeclAST() : BaseAST() {}

		using DeclPtr = std::shared_ptr<DeclAST>;

		llvm::Value* CodeGen() override
		{
			return nullptr;
		}
	};
}

#endif
