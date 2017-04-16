#ifndef _SWING_TYPE_H_
#define _SWING_TYPE_H_

#include <string>
#include <unordered_map>
#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include "SwingCompiler.h"

namespace swing
{
	enum class TypeKind
	{
		Unknown,
		Void,
		Int,
		Double,
		String,
		Array,
		Dictionary,
		Tuple,
		Struct,
		Class,
		Enum,
		Protocol,
		UserDefined
	};

	enum class AccessModifier
	{
		Private,
		Inherit,
		Public
	};

	class Struct
	{
	protected:
		std::vector<llvm::Value*> _value;
		std::unordered_map<std::string, llvm::Function*> _method;
		/// Todo : AccessModifier 적용하기.

	public:
		Struct(std::string name, std::vector<llvm::Type*> val, std::unordered_map<std::string, llvm::Function*> method);
		virtual ~Struct(){}
	};

	class String : Struct
	{
		String(std::string& str);
		virtual ~String() {}

		std::string _str;
	};
}

#endif
