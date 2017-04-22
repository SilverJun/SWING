#ifndef _SWING_TYPE_H_
#define _SWING_TYPE_H_

#include "SwingCompiler.h"

#include <string>
#include <unordered_map>
#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include "StoredProperty.h"

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

	class Struct
	{
	protected:
		std::vector<StoredProperty> _value;
		std::unordered_map<std::string, std::unique_ptr<llvm::Function> > _method;

		/// Protocol conform _protocols

	public:
		Struct(std::string name, std::vector<llvm::Type*> val, std::unordered_map<std::string, std::unique_ptr<llvm::Function> > method);
		virtual ~Struct(){}
	};

	class String : Struct
	{
		std::string _str;

	public:
		String(std::string& str);
		virtual ~String() {}
	};
}

#endif
