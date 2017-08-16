#include "StructDeclAST.h"
#include "VariableDeclAST.h"
#include "Error.h"

namespace swing
{
	DeclAST::DeclPtr StructDeclAST::Create(TokenIter& iter)
	{
		auto* ast = new StructDeclAST();
		iter++->Expect(TokenID::Struct_Decl);

		iter->Expect(TokenID::Identifier);
		std::string structName = iter++->_name;

		/* ProtocolType Conform
		if (iter->Is(TokenID::Colon))
		{
		}
		*/

		iter++->Expect(TokenID::OpenMedium);
		while (!iter->Is(TokenID::CloseMedium))
		{
			switch (iter->_id)
			{
			case TokenID::Type_Var:	/// PropertyObserver, setter, getter 준비하기.
			{
				DeclPtr varDeclAST = VariableDeclAST::Create(iter);
				VariableDeclAST* memberVar = static_cast<VariableDeclAST*>(varDeclAST.get());
				ast->_type.AppendElement(memberVar->_variable->_name, memberVar->_variable->_type);
			}
				break;
			case TokenID::Func_Decl:

				break;
			default:
				throw Error("StructDeclAST Error!, Only available VariableDecl or FunctionDecl");
			}
		}
		++iter;

		ast->_type._name = structName;
		return DeclPtr(ast);
	}

	llvm::Value* StructDeclAST::CodeGen()
	{
		_type.CreateStructType();
		return nullptr;
	}
}
