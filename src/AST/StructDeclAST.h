#ifndef _SWING_STRUCT_DECL_AST_H_
#define _SWING_STRUCT_DECL_AST_H_
#include "DeclAST.h"
#include "StructType.h"

namespace swing
{
	class StructDeclAST : public DeclAST
	{
	public:
		StructType _type;

		static DeclPtr Create(TokenIter& iter);
		llvm::Value* CodeGen() override;
	};
}

#endif
