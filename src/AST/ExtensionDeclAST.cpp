#include "ExtensionDeclAST.h"
#include "VariableDeclAST.h"
#include "FunctionDeclAST.h"

namespace swing
{
	DeclAST::DeclPtr ExtensionDeclAST::Create(TokenIter& iter)
	{
		auto* ast = new ExtensionDeclAST();
		iter++->Expect(TokenID::Extension_Decl);

		/// Protocol 인지 Struct인지 확인해야 한다.

		iter->Expect(TokenID::Identifier);
		ast->_structType = iter++->_name;

		/// ProtocolType Conform
		if (iter->Is(TokenID::Colon))
		{
			++iter;
			iter->Expect(TokenID::Identifier);

			ast->_protocol.push_back(g_SwingCompiler->_protocols[iter++->_name]);

			while (iter->Is(TokenID::Comma))
			{
				iter->Expect(TokenID::Identifier);
				ast->_protocol.push_back(g_SwingCompiler->_protocols[iter++->_name]);
			}
		}

		iter++->Expect(TokenID::OpenMedium);
		while (!iter->Is(TokenID::CloseMedium))
		{
			switch (iter->_id)
			{
			case TokenID::Type_Var:	/// PropertyObserver, setter, getter 준비하기.
			{
				ast->_var.push_back(VariableDeclAST::Create(iter));
			}
			break;
			case TokenID::Func_Decl:
			{
				ast->_method.push_back(FunctionDeclAST::Create(iter));
			}
			break;
			default:
				throw Error("ExtensionDeclAST Error!, Only available VariableDecl or FunctionDecl");
			}
		}
		++iter;

		return DeclPtr(ast);
	}

	llvm::Value* ExtensionDeclAST::CodeGen()
	{
		StructType* type = g_SwingCompiler->_structs[_structType];
		
		for (int i = 0; i < _var.size(); ++i)
		{
			VariableDeclAST* memberVar = static_cast<VariableDeclAST*>(_var[i].get());
			type->AppendElement(memberVar->_variable->_name, g_SwingCompiler->GetType(memberVar->_variable->_typeName));
		}

		for (int i = 0; i < _method.size(); ++i)
		{
			FunctionDeclAST* memberFunc = static_cast<FunctionDeclAST*>(_method[i].get());
			type->_method[memberFunc->_method->_funcName] = *memberFunc->_method;
		}
		for (int i = 0; i < _protocol.size(); ++i)
		{
			type->conformProtocol(_protocol[i]);
		}

		type->UpdateType();
		return nullptr;
	}
}
