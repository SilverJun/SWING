#ifndef _SWING_VARIABLE_H_
#define _SWING_VARIABLE_H_

#include <memory>
#include "Error.h"
#include <llvm/ADT/Optional.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace swing
{
	/**
	 * \brief SWING basic variable implement class.
	 */
	class Variable
	{
		bool _isOptional;
		bool _isLet;
		std::string _name;
		llvm::Type* _type;
		llvm::Optional<llvm::Value*> _value;
	public:
		Variable() = delete;
		
		/**
		 * \brief Type only variable.
		 * variable will be optional.
		 * variable can`t be let type.
		 * this variable init with nil.
		 */
		explicit Variable(llvm::Type* type, std::string name) : 
			_isOptional(true),
			_isLet(false),
			_name(name),
			_type(type),
			_value(llvm::NoneType::None)
		{
		}

		/**
		 * \brief Initial value variable.
		 * variable can be let, optional. it`s choice.
		 */
		explicit Variable(llvm::Value* value, std::string name, bool let, bool optional) :  
			_isOptional(optional),
			_isLet(let),
			_name(name),
			_type(value->getType()),
			_value(value)
		{
		}

		/**
		 * \brief Full option variable.
		 */
		explicit Variable(llvm::Type* type, llvm::Value* value, std::string name, bool let, bool optional) :
			_isOptional(optional),
			_isLet(let),
			_name(name),
			_type(type),
			_value(value)
		{
		}

		~Variable() {}

		void SetValue(llvm::Value* value)
		{
			if (!_isOptional && value == nullptr) 
				throw Error(0, "Variable can`t be nil. Variable is not optional.");

			_value = value;
		}

		bool IsOptional() const { return _isOptional; }
		bool IsNil() const { return !_value.hasValue(); }
		bool isLet() const { return _isLet; }
		std::string GetName() const { return _name; }
		llvm::Value* GetValue() const { return _value.getValue(); }
	};
}

#endif
