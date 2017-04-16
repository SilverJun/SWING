#include "Type.h"

#include "SwingCompiler.h"

namespace swing
{
	Struct::Struct(std::string name, std::vector<llvm::Type*> val, std::vector<llvm::Function*> method) :
		_value(),
		_method(method)
	{

	}

	String::String(std::string& str) : Struct("String", 
	{ llvm::VectorType::get(g_SwingCompiler._types["Char"], str.length()) },
	{
		llvm::Function::Create(llvm::FunctionType::get(g_SwingCompiler._types["Int"], false), llvm::GlobalValue::ExternalLinkage, "length", &g_SwingCompiler._module)
	})
	{
		
	}
}