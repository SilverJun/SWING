#ifndef _SWING_STRUCT_TYPE_H_
#define _SWING_STRUCT_TYPE_H_

#include <string>
#include <vector>
#include <unordered_map>
#include "ProtocolType.h"
#include "Property.h"

namespace swing
{
	class StructType
	{
	public:
		std::string _name;
		llvm::StructType* _type;
		std::vector<Property> _value;
		std::vector<llvm::Type*> _typeLayout;
		std::unordered_map<std::string, Method> _method;
		
		/// ProtocolType conform _protocols
		std::vector<ProtocolType> _protocols;

		StructType();
		virtual ~StructType() {}

		void CreateStructType();
		void UpdateType();
		llvm::StructType* GetStructType() const;

		/// ProtocolType conform
		void conformProtocol(ProtocolType* prot);
		
		void AppendElement(std::string name, llvm::Type* type);

		Property* GetElement(std::string name);

		llvm::Value* GetElementPtr(llvm::Value* structPtr, std::string variableName);
	};
}

#endif
