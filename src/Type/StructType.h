#ifndef _SWING_STRUCT_H_
#define _SWING_STRUCT_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Property.h"

namespace swing
{
	class StructType
	{
	public:
		bool _isSetBody = false;
		std::string _name;
		llvm::StructType* _type;
		std::vector<Property> _value;
		std::vector<llvm::Type*> _typeLayout;
		std::unordered_map<std::string, llvm::Function* > _method;
		
		/// Protocol conform _protocols
		// std::vector<ProtocolType> _protocols;
		StructType();
		virtual ~StructType() {}

		/**
		 * \brief Set struct body. this method is call once at final Generate time.
		 */
		void CreateStructType();
		llvm::StructType* GetStructType() const;

		/// TODO : Protocol conform
		//void conformProtocol(/*Protocol* prot*/)
		//{
		//}
		void AppendElement(std::string name, llvm::Type* type);

		Property* GetElement(std::string name);

		llvm::Value* GetElementPtr(std::vector<std::string> variableNames);
	};
}

#endif
