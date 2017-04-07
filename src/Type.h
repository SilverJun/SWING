#ifndef _SWING_TYPE_H_
#define _SWING_TYPE_H_

#include "SwingCompiler.h"

#include <string>
#include <llvm/IR/Type.h>

namespace swing
{
	struct Type
	{
		std::string _typeName;
		llvm::Type* _typeInfo;

		Type() : _typeName(""), _typeInfo(nullptr) {}
		virtual ~Type(){}
	};

	struct Int : Type
	{
		Int() : Type()
		{
			this->_typeName = "Int";
			this->_typeInfo = llvm::StructType::create();
		}
	};


	/*
	 * struct Int{
	 * 
	 * var data: int4
	 * 
	 * infix operator + (lhs: Int, rhs: Int) -> Int
	 * {
	 *     return lhs.data + rhs.data
	 * }
	 * 
	 * }
	 */

	/*
	 * class Int : Type {
	 * public:
	 * Int() : Type()
	 * {
	 *     _typeName = "Int";
	 *     _typeInfo = llvm::StructType....;
	 *     std::vector<llvm::Type*> structMember;
	 *     structMember.push_back(....);
	 *     llvm::StructType::create(GetLLVMContext(), structMember, _typeName);
	 * }
	 * 
	 * }
	 */
}

#endif
