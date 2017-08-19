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
		for (auto protocol : _protocols)
			protocol.ConformCheck(this);
		
		_isSetBody = true;
		_type = llvm::StructType::create(g_Context, _typeLayout, _name);
		g_SwingCompiler->_types[_name] = _type;
		g_SwingCompiler->_structs[_name] = this;

		for (auto iter = _value.begin(); iter != _value.end(); ++iter)
		{
			iter->_type = _type;
		}

		for (auto iter = _method.begin(); iter != _method.end(); ++iter)
		{
			/// Self arg, localTable insert
			Variable* self = new Variable(llvm::PointerType::get(_type, 0), "self", false, false, false);
			iter->second._funcBody->_localTable->AddVariable(self);
			iter->second._args.insert(iter->second._args.begin(), self);

			g_SwingCompiler->AddFunction(_name + "." + iter->first, &_method[iter->first]);
		}
	}

	llvm::StructType* StructType::GetStructType() const
	{
		return _isSetBody ? _type : nullptr;
	}

	void StructType::conformProtocol(ProtocolType* prot)
	{
		_protocols.push_back(*prot);
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

	llvm::Value* StructType::GetElementPtr(llvm::Value* structPtr, std::string variableName)
	{
		return g_Builder.CreateStructGEP(_type, structPtr, GetElement(variableName)->_idx);
	}
}
