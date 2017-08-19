#ifndef _SWING_METHOD_H_
#define _SWING_METHOD_H_

#include <string>
#include <llvm/IR/Value.h>
#include "BlockAST.h"
#include <iostream>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/IR/Verifier.h>

namespace swing
{
	class StructType;

	class Method
	{
	public:
		bool _isRequired;
		bool _isOverride;

		std::string _funcName;
		llvm::FunctionType* _funcType;
		llvm::Function* _func;
		llvm::Type* _returnType;

		std::vector<Variable*> _args;
		StructType* _struct = nullptr;
		BlockAST::BlockPtr _funcBody;

		void DeclareMethod(StructType* type);
		llvm::Value* CodeGen();
	};
}

#endif
