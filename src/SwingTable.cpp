#include "SwingTable.h"
#include "SwingCompiler.h"

namespace swing
{
	std::vector<SwingTable*> SwingTable::_localTable = {};

	SwingTable::SwingTable()
	{
		_childTable = {};
		_variables = {};
	}

	SwingTable::~SwingTable()
	{
		if (_variables.size() != 0)
			_variables.clear();

		if (_childTable.size() != 0)
			_childTable.clear();
	}

	Variable* SwingTable::Find(std::string name)
	{
		if (!_childTable.empty())
		{
			auto result = _childTable.back()->Find(name);
			if (result != nullptr)
				return result;
		}
		
		for (auto elem : _variables)
			if (elem->GetName() == name)
				return elem;

		return nullptr;
	}

	void SwingTable::AddVariable(SwingTable* table)
	{
		g_Table->_childTable.push_back(table);
		_localTable.push_back(table);
	}

	void SwingTable::AddVariable(Variable* variable)
	{
		g_Table->_variables.push_back(variable);
	}

	void SwingTable::PopLocalTable()
	{
		g_SwingCompiler->_globalTable._localTable.pop_back();
	}
}
