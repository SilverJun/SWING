#ifndef _SWING_TYPE_H_
#define _SWING_TYPE_H_

#include <string>
#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>

namespace swing
{
	class Type
	{
	protected:
		std::string _typeName;
		llvm::Type* _typeInfo;

	public:
		Type() : _typeName(""), _typeInfo() {}
		Type(std::string name, llvm::Type* type) : _typeName(name), _typeInfo(type) {}
		virtual ~Type(){}
	};

	enum class AccessModifier
	{
		Private,
		Inherit,
		Public
	};

	class Struct : Type
	{
	protected:
		std::vector<llvm::Type*> _mVal;
		std::vector<llvm::Function*> _mMethod;

		/// Todo : AccessModifier 적용하기.

	public:
		Struct(std::string name, std::vector<llvm::Type*> val, std::vector<llvm::Function*> method);
		virtual ~Struct(){}
	};

	class Int : Struct
	{
	public:
		Int();
	};
}

#endif
