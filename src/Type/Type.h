#ifndef _SWING_TYPE_H_
#define _SWING_TYPE_H_

#include "SwingCompiler.h"

#include <string>
#include <unordered_map>

namespace swing
{
	namespace BuiltInType
	{
		inline llvm::Value* Nil(llvm::Type* type)
		{
			return llvm::Constant::getNullValue(type);
		}
		
	#define Void llvm::Type::getVoidTy(g_Context)
	#define Bool llvm::Type::getInt8Ty(g_Context)
	#define Char llvm::Type::getInt8Ty(g_Context)
	#define Int llvm::Type::getInt32Ty(g_Context)
	#define Float llvm::Type::getFloatTy(g_Context)
	#define Double llvm::Type::getDoubleTy(g_Context)
	}

	inline std::string GetTypeString(llvm::Type* type)
	{
		if (type == nullptr)
			return "";

		if (type == Void)
			return "Void";
		if (type == Bool)
			return "Bool";
		if (type == Char)
			return "Char";
		if (type == Int)
			return "Int";
		if (type == Float)
			return "Float";
		if (type == Double)
			return "Double";

		return type->getStructName();
	}
}

#endif
