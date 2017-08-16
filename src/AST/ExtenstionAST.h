#ifndef _SWING_EXTENSION_AST_H_
#define _SWING_EXTENSION_AST_H_
#include "StructType.h"
#include "DeclAST.h"

namespace swing
{
	class ExtenstionAST : DeclAST
	{
	public:
		StructType*	_struct;
		ProtocolType* _protocol;

		static DeclPtr Create(TokenIter& iter);
		llvm::Value* CodeGen() override;
	};

}

#endif
