#ifndef _SWING_SOURCE_H_
#define _SWING_SOURCE_H_

#include <string>
#include "BaseAST.h"
#include "Token.h"

namespace swing
{
	class Source
	{
	public:
		/// file option
		std::string _name;
		std::string _fullPath;

		/// source handle
		std::string _code;
		TokenList _tokenList;
		ASTList _sourceAST;

		///Open and Copy source code
		Source(std::string fullpath);
		~Source();

		void Dump();
		void Parse();
		void CodeGen();
	};

	using SourceList = std::vector<Source*>;
	using SourceIter = SourceList::iterator;
}

#endif
