#ifndef _SWING_STRUCT_H_
#define _SWING_STRUCT_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "StoredProperty.h"

namespace swing
{
	class StructType
	{
	public:
		bool _isSetBody = false;
		llvm::StructType* _type;
		std::vector<StoredProperty> _value;
		std::vector<llvm::Type*> _typeLayout;
		std::unordered_map<std::string, llvm::Function* > _method;
		
		/// Protocol conform _protocols
		// std::vector<ProtocolType> _protocols; 

		StructType(std::string name, std::vector<llvm::Type*> val, std::unordered_map<std::string, llvm::Function* > method) :
			_value(),
			_typeLayout(val),
			_method(method)
		{
			_type = llvm::StructType::create(g_Context, name);
		}
		virtual ~StructType() {}

		void appendType(llvm::Type* type) { _typeLayout.push_back(type); }

		/**
		 * \brief Set struct body. this method is call once at final Generate time.
		 */
		void CreateStructType()
		{
			if (!_isSetBody) { return; }
			
			_isSetBody = true;
			_type->setBody(_typeLayout);
		}

		llvm::StructType* getStructType() const { return _isSetBody ? _type : nullptr; }
		
		/// TODO : Protocol conform
		void conformProtocol(/*Protocol* prot*/)
		{
		}

		llvm::Value* GetElement(std::string name)
		{
			StoredProperty member = std::find_if(_value.begin(), _value.end(), [](StoredProperty& value)
			{
				value.;
			});

			member
		}
	};
}

#endif
