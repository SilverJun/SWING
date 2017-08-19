#include "StructType.h"

namespace swing
{
	StructType::StructType() : _type(nullptr)
	{
	}

	void StructType::AppendElement(std::string name, llvm::Type* type)
	{
		if (!type)
			throw Error("StructType error!, " + name + " type is null!");

		_typeLayout.push_back(type);
		_value.push_back(Property(_value.size(), name));
	}

	void StructType::CreateStructType()
	{
		_type = llvm::StructType::create(g_Context, _typeLayout, _name);
		g_SwingCompiler->_types[_name] = _type;
	}

	llvm::StructType* StructType::GetStructType() const
	{
		return _type;
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

	void StructType::UpdateType()
	{
		if (_protocols.size() != 0)
		{
			for (auto protocol : _protocols)
				protocol.ConformCheck(this);
		}

		g_SwingCompiler->_structs[_name] = this;

		for (auto iter = _value.begin(); iter != _value.end(); ++iter)
		{
			iter->_type = _type;
		}

		for (auto iter = _method.begin(); iter != _method.end(); ++iter)
		{
			if (!g_SwingCompiler->GetFunction(_name + "." + iter->first))
			{
				/// Self arg, localTable insert
				/*Variable* self = new Variable(_name, "self", false, false, false);
				iter->second._funcBody->_localTable->AddVariable(self);
				iter->second._args.insert(iter->second._args.begin(), self);*/

				g_SwingCompiler->AddFunction(_name + "." + iter->first, &_method[iter->first]);
			}
		}
	}
}
