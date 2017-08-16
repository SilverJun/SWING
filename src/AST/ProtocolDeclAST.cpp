#include "ProtocolDeclAST.h"
#include "Error.h"

namespace swing
{
	DeclAST::DeclPtr ProtocolDeclAST::Create(TokenIter& iter)
	{
		auto* ast = new ProtocolDeclAST();

		iter++->Expect(TokenID::Protocol_Decl);

		iter->Expect(TokenID::Identifier);
		ast->_type._name = iter++->_name;

		iter++->Expect(TokenID::OpenMedium);

		/// Protocol Property Index.
		int index = 0;

		while (!iter->Is(TokenID::CloseMedium))
		{
			switch (iter->_id)
			{
			case TokenID::Type_Var:
			{
				++iter;
				iter->Expect(TokenID::Identifier);
				std::string name = iter++->_name;
				iter++->Expect(TokenID::Colon);
				llvm::Type* type = g_SwingCompiler->GetType(iter->_name);
				
				ast->_type._requirePropertys[name] = new Property(index++, name);
				ast->_type._typeLayout.push_back(type);
			}
				break;
			case TokenID::Func_Decl:
				
				break;
			default:
				throw ParsingError(*iter, "Unresolved Token in Protocol declare scope.");
			}
			++iter;
		}

		return DeclPtr(ast);
	}

	llvm::Value* ProtocolDeclAST::CodeGen()
	{
		return nullptr;
	}
}
