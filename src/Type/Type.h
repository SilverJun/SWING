#ifndef _SWING_TYPE_H_
#define _SWING_TYPE_H_

#include "SwingCompiler.h"

#include <string>
#include <unordered_map>

namespace swing
{
	static std::unordered_map<std::string, llvm::Type*> BuiltinType;
}

#endif
