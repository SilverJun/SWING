#include "FunctionDeclAST.h"
#include "SwingCompiler.h"
#include <llvm/IR/Function.h>
#include <llvm/IR/Verifier.h>
#include "Type.h"
#include "Error.h"
#include <iostream>
#include <llvm/Support/raw_os_ostream.h>

namespace swing
{
	DeclAST::DeclPtr FunctionDeclAST::Create(TokenIter& iter)
	{
		FunctionDeclAST* ast = new FunctionDeclAST();
		
		iter->Expect(TokenID::Func_Decl); ++iter;
		iter->Expect(TokenID::Identifier);

		ast->_method = new Method();
		ast->_method->_funcName = iter->_name; ++iter;
		
		iter->Expect(TokenID::OpenSmall); ++iter;

		while (!iter->Is(TokenID::CloseSmall))
		{
			std::string name;
			std::string type;
			//llvm::Type* type = nullptr;

			bool inout = false;
			bool optional = false;
			/*if (iter->Is(TokenID::Func_Inout))
			{
				inout = true; ++iter;
			}*/
			iter->Expect(TokenID::Identifier);
			name = iter->_name;
			++iter;
			iter->Expect(TokenID::Colon);
			++iter;
			type = iter->_name;
			//type = g_SwingCompiler->GetType(iter->_name);
			//type = iter->_name;
			++iter;
			/*if (iter->Is(TokenID::Optional_Nilable))
			{
				optional = true; ++iter;
			}*/
			ast->_method->_args.push_back(new Variable(type, name, false, inout, optional));

			if (iter->Is(TokenID::Comma))
				++iter;
		}
		++iter;

		/// return type check
		if (iter->Is(TokenID::Arrow))
		{
			++iter;
			ast->_method->_returnType = iter++->GetType();
		}
		else
			ast->_method->_returnType = Void;

		ast->_method->_funcBody = BlockAST::Create(iter);
		
		return DeclPtr(ast);
	}

	llvm::Value* FunctionDeclAST::CodeGen()
	{
		g_SwingCompiler->AddFunction(_method->_funcName, _method);
		return _method->CodeGen();
	}
}
