#ifndef _SWING_STORE_PROPERTY_H_
#define _SWING_STORE_PROPERTY_H_

#include <llvm/IR/Value.h>

namespace swing
{

	enum class AccessModifier
	{
		Private,
		Inherit,
		Public
	};

	class StoreProperty
	{
		AccessModifier _access;
		llvm::Value* _value;

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
		StoreProperty(AccessModifier access, llvm::Value* value) : _access(access), _value(value) {}

		llvm::Value* GetValue(AccessModifier auth)
		{
			assert(auth == _access && "StoreProperty Access Denied.");

			return nullptr;
		}


	};

}
#endif
