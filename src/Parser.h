#ifndef _SWING_PARSER_H_
#define _SWING_PARSER_H_
#include "BaseAST.h"

namespace swing
{
	class Parser
	{
		BaseAST* _rootTree;

	public:
		Parser();
		~Parser();

		void InitializeParser();

		void ParseTree(BaseAST* tree);
	};
}
#endif
