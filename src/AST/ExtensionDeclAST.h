#ifndef _SWING_EXTENSION_AST_H_
#define _SWING_EXTENSION_AST_H_
#include "StructType.h"
#include "DeclAST.h"
#include "FunctionDeclAST.h"

namespace swing
{
	class ExtensionDeclAST : public DeclAST
	{
	public:
		std::string _structType;
		std::vector<ProtocolType*> _protocol;

		std::vector<DeclPtr> _var;
		std::vector<DeclPtr> _method;

		static DeclPtr Create(TokenIter& iter);
		llvm::Value* CodeGen() override;
	};

}

#endif
