#ifndef _SWING_VARIABLE_H_
#define _SWING_VARIABLE_H_

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include "SwingCompiler.h"

namespace swing
{
	class Variable
	{
		bool _isOptional;
		bool _isNil;

		std::string _name;
		llvm::Value* _value;
	public:
		Variable() = delete;
		
		explicit Variable(llvm::Type* type, std::string name, bool optional, bool nil = true) : _name(name), _isOptional(optional), _isNil(nil)
		{
			_value = llvm::Constant::getNullValue(type);
		}

		explicit Variable(llvm::Value* value, std::string name, bool optional, bool nil = false) : _value(value), _name(name), _isOptional(optional), _isNil(nil)
		{
		}

		~Variable() {}
		
		bool IsOptional() const { return _isOptional; }
		bool IsNil() const { return _isNil; }
	};
}

#endif
