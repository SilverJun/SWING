#ifndef _SWING_TYPE_H_
#define _SWING_TYPE_H_

#include "SwingCompiler.h"

#include <string>
#include <unordered_map>

namespace swing
{
	const std::unordered_map<std::string, llvm::Type*> BuiltinType = {
		{ "Void", llvm::Type::getVoidTy(g_Context) },
		{ "Bool", llvm::Type::getInt8Ty(g_Context) },
		{ "Char", llvm::Type::getInt8Ty(g_Context) },
		{ "Int", llvm::Type::getInt32Ty(g_Context) },
		{ "Int8", llvm::Type::getInt64Ty(g_Context) },
		{ "UInt", llvm::Type::getInt32Ty(g_Context) },
		{ "UInt8", llvm::Type::getInt64Ty(g_Context) },
		{ "Float", llvm::Type::getFloatTy(g_Context) },
		{ "Double", llvm::Type::getDoubleTy(g_Context) }
	};
}

#endif
