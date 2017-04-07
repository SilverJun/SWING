#ifndef _SWING_TYPE_H_
#define _SWING_TYPE_H_

#include <string>
#include <llvm/IR/Type.h>

namespace swing
{
	class Type
	{
		std::string _typeName;
		llvm::Type* _typeInfo;

	public:
		Type(std::string name, llvm::Type* type) : _typeName(name), _typeInfo(type)
		{
		}

		virtual ~Type()
		{
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
