#ifndef _SWING_TABLE_H_
#define _SWING_TABLE_H_

#include "Variable.h"
#include <unordered_map>

namespace swing
{
	class SwingTable
	{
	public:
		static std::vector<SwingTable*> _localTable;

		std::vector<SwingTable*> _childTable;
		std::vector<Variable*> _variables;

		SwingTable();
		~SwingTable();

		Variable* Find(std::string name);
		void AddVariable(SwingTable* table);
		void AddVariable(Variable* variable);
		void PopLocalTable();
	};
}

#endif
