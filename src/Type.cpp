#include "Type.h"

#include "SwingCompiler.h"
#include <iostream>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_os_ostream.h>

namespace swing
{
	Struct::Struct(std::string name, std::vector<llvm::Type*> val, std::unordered_map<std::string, llvm::Function*> method) :
		_value(),
		_method(method)
	{
	}

	String::String(std::string& str) : Struct("String", 
	{ llvm::VectorType::get(g_SwingCompiler._types["Char"], str.length()) },
	{
		{ "length", llvm::Function::Create(llvm::FunctionType::get(g_SwingCompiler._types["Int"], false), llvm::GlobalValue::LinkOnceAnyLinkage, "length", &g_Module) }
	}), _str(str)
	{
		/// Built-In member methods implementation

		/// func length() -> Int
		llvm::BasicBlock* funcBody = llvm::BasicBlock::Create(g_Context, "entry", _method["length"]);
		g_Builder.SetInsertPoint(funcBody);
		g_Builder.CreateRet(llvm::ConstantInt::get(g_Context, llvm::APInt(32, _str.length(), true)));
		llvm::raw_os_ostream ros(std::cout);
		std::for_each(_method.begin(), _method.end(), [&ros](std::unordered_map<std::string, llvm::Function*>::iterator& method) { verifyFunction(*method->second, &ros); });
		///

	}
}
