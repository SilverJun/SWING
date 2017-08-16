#ifndef _SWING_PROTOCOL_DECL_AST_H_
#define _SWING_PROTOCOL_DECL_AST_H_
#include "DeclAST.h"
#include "ProtocolType.h"

namespace swing
{
	class ProtocolDeclAST : public DeclAST
	{
	public:
		ProtocolType _type;

		static DeclPtr Create(TokenIter& iter);
		llvm::Value* CodeGen() override;
	};
}

#endif
