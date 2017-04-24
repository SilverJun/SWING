#ifndef _SWING_METHOD_H_
#define _SWING_METHOD_H_

#include <string>
#include <llvm/IR/Value.h>

struct Method
{
	bool _isInit;
	bool _isDeInit;
	bool _isRequired;
	bool _isOverride;

	std::string _name;
	llvm::Function* _func;
};

#endif
