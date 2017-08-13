#ifndef _SWING_PROPERTY_H_
#define _SWING_PROPERTY_H_

#include "SwingCompiler.h"
#include "Variable.h"

#include <llvm/IR/Value.h>

namespace swing
{
	class Property
	{
		llvm::Value* GetElementPtr(llvm::Value* structPtr) const
		{
			return g_Builder.CreateStructGEP(_type, structPtr, _idx);
		}

	public:
		int _idx;
		std::string _name;
		llvm::Type* _type;

		llvm::Function* _setter;
		llvm::Function* _getter;
		
		llvm::Function* _willSet;
		llvm::Function* _didSet;

		Property(int idx, std::string name) : 
			_idx(idx), _name(name), _type(nullptr), _setter(nullptr), _getter(nullptr), _willSet(nullptr), _didSet(nullptr)
		{}

		void SetValue(llvm::Value* structPtr, llvm::Value* value)
		{
			auto* oldValue = g_Builder.CreateLoad(GetElementPtr(structPtr));
			
			if (_willSet != nullptr)
				g_Builder.CreateCall(_willSet, { value });
			if (_setter == nullptr)
				g_Builder.CreateCall(_setter, { value });
			else
				g_Builder.CreateStore(value, GetElementPtr(structPtr));
			if (_didSet != nullptr)
				g_Builder.CreateCall(_didSet, { oldValue });
		}

		llvm::Value* GetValue(llvm::Value* structPtr) const
		{
			return _getter != nullptr ? g_Builder.CreateCall(_getter) : GetElementPtr(structPtr);
		}

		void SetSetter(llvm::Function* func)
		{
			_setter = func;
		}
		void SetGetter(llvm::Function* func)
		{
			_getter = func;
		}
		void SetWillSet(llvm::Function* func)
		{
			_willSet = func;
		}
		void SetDidSet(llvm::Function* func)
		{
			_didSet = func;
		}
	};
}
#endif

