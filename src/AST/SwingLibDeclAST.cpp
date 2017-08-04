#include "SwingLibDeclAST.h"

#include "SwingCompiler.h"
#include "Type.h"
#include <llvm/IR/Verifier.h>
#include <iostream>
#include <llvm/Support/raw_os_ostream.h>

namespace swing
{
	DeclAST::DeclPtr SwingLibDeclAST::Create()
	{
		auto* ast = new SwingLibDeclAST();
		ast->_output = new FunctionDeclAST();

		/// Function Decl과 유사한 작업을 여기서 해준다.
		/// IO 함수를 연결, 컬렉션 타입을 여기서 다 연결해준다.
		
		ast->_output->_returnType = Void;
		ast->_output->_funcName = "output";
		ast->_output->_args.push_back(new Variable(g_Builder.getInt8Ty()->getPointerTo(), "str", true, false, false));

		g_SwingCompiler->AddFunction("output", ast->_output);

		return DeclPtr(ast);
	}

	llvm::Value* SwingLibDeclAST::CodeGen()
	{
		/// output Function Decl Start.
		std::vector<llvm::Type*> args;
		for (auto& element : _output->_args)
			args.push_back(element->GetType());

		_output->_funcType = llvm::FunctionType::get(_output->_returnType, args, false);
		_output->_func = llvm::Function::Create(_output->_funcType, llvm::Function::ExternalLinkage, "output", &g_Module);
		/// output Function Decl End.


		return nullptr;
	}
}
