#ifndef _SWING_STORE_PROPERTY_H_
#define _SWING_STORE_PROPERTY_H_

#include "SwingCompiler.h"

#include <llvm/IR/Value.h>
#include "Variable.h"

namespace swing
{
	class StoredProperty
	{
		/// TODO : Think How to Add Access Control

		Variable _var;

		std::unique_ptr<llvm::Function> _setter = nullptr;
		std::unique_ptr<llvm::Function> _getter = nullptr;
		
		std::unique_ptr<llvm::Function> _willSet = nullptr;
		std::unique_ptr<llvm::Function> _didSet = nullptr;

	public:
		StoredProperty(Variable var) : _var(var) {}

		void SetValue(llvm::Value* value)
		{
			if (_setter == nullptr)
			{
				g_Builder.CreateCall(_setter.get(), {value});
			}
			else
			{
				_var.SetValue(value);
			}
		}

		llvm::Value* GetValue()
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

