#ifndef _SWING_BASE_AST_H_
#define _SWING_BASE_AST_H_

#include "llvm/IR/Value.h"
#include "Token.h"
#include <vector>
#include <memory>

namespace swing
{
	class BaseAST
	{
	public:
		using BasePtr = std::shared_ptr<BaseAST>;

		BaseAST() {}
		virtual ~BaseAST() {}
		virtual void Dump() {}
		static BasePtr Create(TokenIter& iter);
		virtual llvm::Value* CodeGen() = 0;
	};

	using ASTList = std::vector<BaseAST::BasePtr>;
}

#endif
