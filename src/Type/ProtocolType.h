#ifndef _SWING_PROTOCOL_TYPE_H_
#define _SWING_PROTOCOL_TYPE_H_

#include <string>
#include <unordered_map>
#include "Property.h"
#include "Method.h"

namespace swing
{
	class ProtocolType
	{
	public:
		std::unordered_map<std::string, Property*> _requirePropertys;
		std::unordered_map<std::string, Method*> _requireMethods;
		std::vector<llvm::Type*> _typeLayout;

		std::string _name;
		llvm::StructType* _type;

		void CreateProtocolType();
	};
}

#endif
