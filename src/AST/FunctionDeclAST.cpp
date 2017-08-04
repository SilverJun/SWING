#include "FunctionDeclAST.h"
#include "SwingCompiler.h"
#include <llvm/IR/Function.h>
#include <llvm/IR/Verifier.h>
#include "Type.h"
#include <iostream>
#include <llvm/Support/raw_os_ostream.h>

namespace swing
{
	DeclAST::DeclPtr FunctionDeclAST::Create(TokenIter& iter)
	{
		FunctionDeclAST* FunctionAST = new FunctionDeclAST();

		iter->Expect(TokenID::Func_Decl); ++iter;
		iter->Expect(TokenID::Identifier);
		FunctionAST->_funcName = iter->_name; ++iter;
		iter->Expect(TokenID::OpenSmall); ++iter;

		while (!iter->Is(TokenID::CloseSmall))
		{
			std::string name;
			llvm::Type* type;
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
			type = g_SwingCompiler->_types[iter->_name];
			++iter;
			if (iter->Is(TokenID::Optional_Nilable))
			{
				optional = true; ++iter;
			}
			FunctionAST->_args.push_back(new Variable(type, name, false, inout, optional));

			if (!iter->Is(TokenID::Comma))
				break;
		}
		++iter;

		/// return type check
		if (iter->Is(TokenID::Arrow))
		{
			++iter;
			FunctionAST->_returnType = iter++->GetType();
		}
		else
		{
			FunctionAST->_returnType = Void;
		}

		FunctionAST->_funcBody = BlockAST::Create(iter);

		g_SwingCompiler->AddFunction(FunctionAST->_funcName, FunctionAST);

		return DeclPtr(FunctionAST);
	}

	llvm::Value* FunctionDeclAST::CodeGen()
	{
		std::vector<llvm::Type*> argTypes;

		for (auto& element : _args)
			argTypes.push_back(element->GetType());

		_funcType = llvm::FunctionType::get(_returnType, argTypes.size() != 0 ? argTypes, false : false);
		_func = llvm::Function::Create(_funcType, llvm::Function::ExternalLinkage, _funcName, &g_Module);
		
		/// 인자 등록하는 과정.
		int Idx = 0;
		for (auto &Arg : _func->args())
		{
			if (_args[Idx]->isInout())
				Arg.addAttr(llvm::Attribute::Dereferenceable);

			Arg.setName(_args[Idx]->GetName());
			_args[Idx]->SetValue(&Arg);

			_funcBody->_localTable->AddVariable(_args[Idx]);
			Idx++;
		}
		g_Table.AddVariable(_funcBody->_localTable);

		_funcBody->_func = _func;
		_funcBody->CodeGen();

		llvm::raw_os_ostream os(std::cout);
		if (verifyFunction(*_func, &os))
			throw Error("Function Generate Error.");

		return _func;
	}
}
