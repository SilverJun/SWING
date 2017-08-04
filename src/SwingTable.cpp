#include "SwingTable.h"

namespace swing
{

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
			auto* result = _childTable.back().Find(name);
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
		SwingTable* local = FindLocalTable();
		
		local->_childTable.push_back(*table);
	}

	void SwingTable::AddVariable(Variable* variable)
	{
		SwingTable* local = FindLocalTable();

		local->_variables.push_back(variable);
	}

	SwingTable* SwingTable::FindLocalTable()
	{
		SwingTable* local = this;
		while (!local->_childTable.empty())
			local = &local->_childTable.back();
		return local;
	}
}
