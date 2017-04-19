#ifndef _SWING_STORE_PROPERTY_H_
#define _SWING_STORE_PROPERTY_H_

#include "SwingCompiler.h"

#include <llvm/IR/Value.h>
#include "Variable.h"

namespace swing
{
	enum class AccessModifier
	{
		Private,
		Inherit,
		Public
	};

	inline std::string AccessModifierToString(AccessModifier access)
	{
		switch (access)
		{
		case AccessModifier::Private:
			return "Private";
		case AccessModifier::Inherit:
			return "Inherit";
		case AccessModifier::Public:
			return "Public";
		default:
			return "Error";
		}
	}

	class StoreProperty
	{
		AccessModifier _access;
		Variable _var;

		llvm::Function* _setter = nullptr;
		llvm::Function* _getter = nullptr;

		llvm::Function* _willSet = nullptr;
		llvm::Function* _didSet = nullptr;

		bool canAccess(AccessModifier auth)
		{
			switch (auth)
			{
			case AccessModifier::Private:		/// private can access any properties.
				break;
			case AccessModifier::Inherit:			/// inherit can access public, inherit
				if (_access == AccessModifier::Private)
					return false;
				break;
			case AccessModifier::Public:		/// public only access public
				if (_access != AccessModifier::Public)
					return false;
				break;
			}
			return true;
		}

	public:
		StoreProperty(AccessModifier access, Variable var) : _access(access), _var(var) {}

		llvm::Value* GetValue(AccessModifier auth)
		{
			if (!canAccess(auth)) { throw Error(0, this->_var.GetString() + "  Access Denied, Can`t access auth with " + AccessModifierToString(auth)); }

			return _getter == nullptr ? g_Builder.CreateCall(_getter) : _var.GetValue();
		}
	};
}
#endif

