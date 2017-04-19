﻿#ifndef _SWING_VARIABLE_H_
#define _SWING_VARIABLE_H_

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace swing
{
	class Variable
	{
		bool _isOptional;
		bool _isNil;

		bool _isLet;
		std::string _name;
		llvm::Value* _value;
	public:
		Variable() = delete;
		
		/**
		 * \brief Variable for Type only define like this,
		 * var [name]:[Type]
		 * this variable init nil.
		 */
		explicit Variable(llvm::Type* type, std::string name, bool optional = false) : 
		_isOptional(optional), 
		_isNil(true), 
		_isLet(false), 
		_name(name)
		{
			_value = llvm::Constant::getNullValue(type);
		}


		explicit Variable(llvm::Value* value, std::string name, bool let, bool optional = false, bool nil = false) :  
		_isOptional(optional),
		_isNil(nil), 
		_isLet(let), 
		_name(name), 
		_value(value)
		{
		}

		~Variable() {}
		
		bool IsOptional() const { return _isOptional; }
		bool IsNil() const { return _isNil; }
		bool isLet() const { return _isLet; }
		std::string GetString() const { return _name; }
		llvm::Value* GetValue() { return _value; }
	};
}

#endif