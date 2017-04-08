#include "Type.h"

#include "SwingCompiler.h"

namespace swing
{
	Struct::Struct(std::string name, std::vector<llvm::Type*> val, std::vector<llvm::Function*> method) :
		Type(name, llvm::StructType::create(g_SwingCompiler.GetLLVMContext(), _mVal, name)),
		_mVal(val),
		_mMethod(method)
	{
	}

	Int::Int() : Struct("Int", { llvm::Type::getInt8Ty(g_SwingCompiler.GetLLVMContext()) }, {})
	{
	}
}