#ifndef _SWING_VARIABLE_H_
#define _SWING_VARIABLE_H_

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
		friend class VariableDeclAST;

		bool _isOptional;
		bool _isLet;
		bool _isInout;

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
		Variable(llvm::Type* type, std::string name) : 
			_isOptional(true),
			_isLet(false),
			_isInout(false),
			_name(name),
			_type(type),
			_value(llvm::NoneType::None)
		{
		}

		/**
		* \brief blueprint variable. no real value.
		* variable can be let, optional. it`s choice.
		*/
		Variable(llvm::Type* type, std::string name, bool let, bool inout, bool optional) :
			_isOptional(optional),
			_isLet(let),
			_isInout(inout),
			_name(name),
			_type(type),
			_value(nullptr)
		{
		}

		/**
		 * \brief Full option variable.
		 */
		Variable(llvm::Type* type, llvm::Value* value, std::string name, bool let, bool inout, bool optional) :
			_isOptional(optional),
			_isLet(let),
			_isInout(inout),
			_name(name),
			_type(type),
			_value(value)
		{
		}

		~Variable()
		{
			_value.reset();
		}

		void SetValue(llvm::Value* value)
		{
			if (!_isOptional && value == nullptr) 
				throw Error("Variable can`t be nil. Variable is not optional.");

			_value = value;
		}

		void SetNil()
		{
			if (_isOptional)
				_value.reset();
		}

		bool IsOptional() const { return _isOptional; }
		bool IsNil() const { return !_value.hasValue(); }
		bool isLet() const { return _isLet; }
		bool isInout() const { return _isInout; }
		std::string GetName() const { return _name; }
		llvm::Type* GetType() const { return _type; }
		llvm::Value* GetValue() const { return _value.getValue(); }

		Variable* operator=(Variable& rhs)
		{
			if (rhs.IsNil() == true && this->IsOptional() == false)
				throw Error("can't assign Nil value to not optional value");

			/// TODO : assign implement

			return this;
		}
	};
}

#endif
