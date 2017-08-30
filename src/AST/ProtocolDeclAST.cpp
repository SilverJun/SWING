#include "ProtocolDeclAST.h"
#include "Error.h"
#include "Type.h"

namespace swing
{
	DeclAST::DeclPtr ProtocolDeclAST::Create(TokenIter& iter)
	{
		auto* ast = new ProtocolDeclAST();
		ast->_type = new ProtocolType();
		iter++->Expect(TokenID::Protocol_Decl);

		iter->Expect(TokenID::Identifier);
		ast->_type->_name = iter++->_name;

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
				
				ast->_type->_requirePropertys.push_back(Property(index++, name));
				ast->_type->_typeLayout.push_back(type);
				++iter;
			}
				break;
			case TokenID::Func_Decl:
			{
				++iter;
				iter->Expect(TokenID::Identifier);
				std::string funcName = iter++->_name;
				iter++->Expect(TokenID::OpenSmall);

				ast->_type->_requireMethods[funcName] = Method();
				Method* nowMethod = &ast->_type->_requireMethods[funcName];
				nowMethod->_funcName = funcName;
				nowMethod->_isRequired = true;
				nowMethod->_funcBody = nullptr;
				while (!iter->Is(TokenID::CloseSmall))
				{
					std::string name;
					std::string type;
					bool inout = false;
					bool optional = false;
					if (iter->Is(TokenID::Func_Inout))
					{
						inout = true; ++iter;
					}
					iter->Expect(TokenID::Identifier);
					name = iter->_name;
					++iter;
					iter->Expect(TokenID::Colon);
					++iter;
					///type = g_SwingCompiler->_types[iter->_name];
					type = iter->_name;
					++iter;

					nowMethod->_args.push_back(new Variable(type, name, false, inout, optional));

					if (iter->Is(TokenID::Comma))
						++iter;
				}
				++iter;

				/// return type check
				if (iter->Is(TokenID::Arrow))
				{
					++iter;
					nowMethod->_returnType = iter++->GetType();
				}
				else
					nowMethod->_returnType = Void;
			}
				break;
			default:
				throw ParsingError(*iter, "Unresolved Token in Protocol declare scope.");
			}
		}

		iter++->Expect(TokenID::CloseMedium);

		g_SwingCompiler->_protocols[ast->_type->_name] = ast->_type;

		return DeclPtr(ast);
	}

	llvm::Value* ProtocolDeclAST::CodeGen()
	{
		return nullptr;
	}
}
