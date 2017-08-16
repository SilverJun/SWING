#include "StructType.h"

namespace swing
{
	StructType::StructType() : _type(nullptr)
	{
	}

	void StructType::AppendElement(std::string name, llvm::Type* type)
	{
		_typeLayout.push_back(type);
		_value.push_back(Property(_value.size(), name));
	}

	void StructType::CreateStructType()
	{
		/// TODO : ProtocolType 요구사항 구현되었는지 체크.
		_isSetBody = true;
		_type = llvm::StructType::create(g_Context, _typeLayout, _name);
		g_SwingCompiler->_types[_name] = _type;
		g_SwingCompiler->_structs[_name] = this;

		for (auto iter = _value.begin(); iter != _value.end(); ++iter)
		{
			iter->_type = _type;
		}
	}

	llvm::StructType* StructType::GetStructType() const
	{
		return _isSetBody ? _type : nullptr;
	}

	Property* StructType::GetElement(std::string name)
	{
		for (auto iter = _value.begin(); iter != _value.end(); ++iter)
		{
			if (iter->_name == name)
				return &*iter;
		}
		return nullptr;
	}

	llvm::Value* StructType::GetElementPtr(std::vector<std::string> variableNames)
	{
		Property* element;
		std::string structName;
		StructType* structType;
		llvm::Value* elementPtr;

		auto iter = variableNames.begin();
		++iter;

		/// 1차 멤버 참조
		structType = this;
		elementPtr = g_Table.Find(variableNames.front())->GetValue();
		element = structType->GetElement(*iter);
		elementPtr = element->GetValue(elementPtr);
		++iter;

		/// 2~n차 멤버 참조
		for (; iter != variableNames.end(); ++iter)
		{
			structName = element->_type->getStructName();
			structType = g_SwingCompiler->_structs[structName];
			element = structType->GetElement(*iter);
			elementPtr = element->GetValue(elementPtr);
		}

		return elementPtr;
	}
}
