#ifndef _SWING_STRUCT_H_
#define _SWING_STRUCT_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "StoredProperty.h"

namespace swing
{

	class Struct
	{
	protected:
		std::vector<StoredProperty> _value;
		std::unordered_map<std::string, std::unique_ptr<llvm::Function> > _method;

		/// Protocol conform _protocols

	public:
		Struct(std::string name, std::vector<llvm::Type*> val, std::unordered_map<std::string, std::unique_ptr<llvm::Function> > method) :
			_value(),
			_method(method)
		{
			llvm::StructType::create()

		}

		virtual ~Struct() {}
	};
}

#endif
