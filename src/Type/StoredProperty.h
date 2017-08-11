﻿#ifndef _SWING_STORE_PROPERTY_H_
#define _SWING_STORE_PROPERTY_H_

#include "SwingCompiler.h"
#include "Variable.h"

#include <memory>
#include <llvm/IR/Value.h>

namespace swing
{
	class StoredProperty
	{
		/// TODO : Think How to Add Access Control
	
	public:
		Variable _var;

		std::unique_ptr<llvm::Function> _setter = nullptr;
		std::unique_ptr<llvm::Function> _getter = nullptr;
		
		std::unique_ptr<llvm::Function> _willSet = nullptr;
		std::unique_ptr<llvm::Function> _didSet = nullptr;

		StoredProperty(Variable var) : _var(var) {}

		void SetValue(llvm::Value* value)
		{
			auto* oldValue = _var.GetValue();

			if (_setter == nullptr)
				g_Builder.CreateCall(_setter.get(), { value });
			else
				_var.SetValue(value);

			if (_didSet != nullptr)
				g_Builder.CreateCall(_setter.get(), { oldValue });
		}

		llvm::Value* GetValue() const
		{
			return _getter == nullptr ? g_Builder.CreateCall(_getter.get()) : _var.GetValue();
		}

		void SetSetter(llvm::Function* func)
		{
			_setter.reset(func);
		}
		void SetGetter(llvm::Function* func)
		{
			_getter.reset(func);
		}
		void SetWillSet(llvm::Function* func)
		{
			_willSet.reset(func);
		}
		void SetDidSet(llvm::Function* func)
		{
			_didSet.reset(func);
		}
	};
}
#endif

