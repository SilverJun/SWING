#include "StructDeclAST.h"
#include "VariableDeclAST.h"
#include "FunctionDeclAST.h"
#include "Error.h"

namespace swing
{
	DeclAST::DeclPtr StructDeclAST::Create(TokenIter& iter)
	{
		auto* ast = new StructDeclAST();
		iter++->Expect(TokenID::Struct_Decl);

		iter->Expect(TokenID::Identifier);
		std::string structName = iter++->_name;

		/// ProtocolType Conform
		if (iter->Is(TokenID::Colon))
		{
			++iter;
			iter->Expect(TokenID::Identifier);
			
			ast->_type.conformProtocol(g_SwingCompiler->_protocols[iter++->_name]);

			while (iter->Is(TokenID::Comma))
			{
				++iter;
				iter->Expect(TokenID::Identifier);
				ast->_type.conformProtocol(g_SwingCompiler->_protocols[iter++->_name]);
			}
		}

		iter++->Expect(TokenID::OpenMedium);
		while (!iter->Is(TokenID::CloseMedium))
		{
			switch (iter->_id)
			{
			case TokenID::Type_Var:	/// PropertyObserver, setter, getter 준비하기.
			{
				DeclPtr varDeclAST = VariableDeclAST::Create(iter);
				VariableDeclAST* memberVar = static_cast<VariableDeclAST*>(varDeclAST.get());
				ast->_type.AppendElement(memberVar->_variable->_name, g_SwingCompiler->GetType(memberVar->_variable->_typeName));
			}
				break;
			case TokenID::Func_Decl:
			{
				DeclPtr funcDeclAST = FunctionDeclAST::Create(iter);
				FunctionDeclAST* memberFunc = static_cast<FunctionDeclAST*>(funcDeclAST.get());
				ast->_type._method[memberFunc->_method->_funcName] = *memberFunc->_method;
			}
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
		/// TODO : Struct타입을 변수 생성할때 구체화 하기.
		//_type.CreateStructType();
		_type.UpdateType();
		return nullptr;
	}
}
