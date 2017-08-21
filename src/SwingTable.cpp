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
		if (!_localTable.front()->_childTable.empty())
		{
			auto result = _localTable.front()->_childTable.back()->FindInLocalTable(name);
			if (result != nullptr)
				return result;
		}
		
		for (auto elem = _localTable.front()->_variables.begin(); elem != _localTable.front()->_variables.end(); ++elem)
			if ((*elem)->GetName() == name)
				return *elem;

		return nullptr;
	}

	Variable* SwingTable::FindInLocalTable(std::string name)
	{
		if (!_childTable.empty())
		{
			auto result = _childTable.back()->FindInLocalTable(name);
			if (result != nullptr)
				return result;
		}

		for (auto elem = _variables.begin(); elem != _variables.end(); ++elem)
			if ((*elem)->GetName() == name)
				return *elem;

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
		_localTable.pop_back();
	}
}
