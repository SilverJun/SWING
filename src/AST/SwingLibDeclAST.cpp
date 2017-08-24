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
		ast->_output->_method = new Method();
		ast->_outputInt = new FunctionDeclAST();
		ast->_outputInt->_method = new Method();
		ast->_outputFloat = new FunctionDeclAST();
		ast->_outputFloat->_method = new Method();
		ast->_outputDouble = new FunctionDeclAST();
		ast->_outputDouble->_method = new Method();

		/// Function Decl과 유사한 작업을 여기서 해준다.
		/// IO 함수를 연결, 컬렉션 타입을 여기서 다 연결해준다.
		
		ast->_output->_method->_returnType = Void;
		ast->_output->_method->_funcName = "output";
		ast->_output->_method->_args.push_back(new Variable(g_Builder.getInt8Ty()->getPointerTo(), "str", true, false, false));
		g_SwingCompiler->AddFunction("output", ast->_output->_method);

		ast->_outputInt->_method->_returnType = Void;
		ast->_outputInt->_method->_funcName = "outputInt";
		ast->_outputInt->_method->_args.push_back(new Variable(Int, "value", true, false, false));
		g_SwingCompiler->AddFunction("outputInt", ast->_outputInt->_method);

		ast->_outputFloat->_method->_returnType = Void;
		ast->_outputFloat->_method->_funcName = "outputFloat";
		ast->_outputFloat->_method->_args.push_back(new Variable(Float, "value", true, false, false));
		g_SwingCompiler->AddFunction("outputFloat", ast->_outputFloat->_method);

		ast->_outputDouble->_method->_returnType = Void;
		ast->_outputDouble->_method->_funcName = "outputDouble";
		ast->_outputDouble->_method->_args.push_back(new Variable(Double, "value", true, false, false));
		g_SwingCompiler->AddFunction("outputDouble", ast->_outputDouble->_method);

		return DeclPtr(ast);
	}

	llvm::Value* SwingLibDeclAST::CodeGen()
	{
		std::vector<llvm::Type*> args;
		for (auto& element : _output->_method->_args)
			args.push_back(element->GetType());

		_output->_method->_funcType = llvm::FunctionType::get(_output->_method->_returnType, args, false);
		_output->_method->_func = llvm::Function::Create(_output->_method->_funcType, llvm::Function::ExternalLinkage, "output", &g_Module);
		/// _output Function Decl End.
		args.clear();
		for (auto& element : _outputInt->_method->_args)
			args.push_back(element->GetType());

		_outputInt->_method->_funcType = llvm::FunctionType::get(_outputInt->_method->_returnType, args, false);
		_outputInt->_method->_func = llvm::Function::Create(_outputInt->_method->_funcType, llvm::Function::ExternalLinkage, "outputInt", &g_Module);
		/// _outputInt Function Decl End.
		args.clear();
		for (auto& element : _outputFloat->_method->_args)
			args.push_back(element->GetType());

		_outputFloat->_method->_funcType = llvm::FunctionType::get(_outputFloat->_method->_returnType, args, false);
		_outputFloat->_method->_func = llvm::Function::Create(_outputFloat->_method->_funcType, llvm::Function::ExternalLinkage, "outputFloat", &g_Module);
		/// _outputFloat Function Decl End.
		args.clear();
		for (auto& element : _outputDouble->_method->_args)
			args.push_back(element->GetType());

		_outputDouble->_method->_funcType = llvm::FunctionType::get(_outputDouble->_method->_returnType, args, false);
		_outputDouble->_method->_func = llvm::Function::Create(_outputDouble->_method->_funcType, llvm::Function::ExternalLinkage, "outputDouble", &g_Module);
		/// _outputDouble Function Decl End.

		return nullptr;
	}
}
