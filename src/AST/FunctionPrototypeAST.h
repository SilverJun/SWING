#ifndef _SWING_FUNC_PROTO_AST_H_
#define _SWING_FUNC_PROTO_AST_H_

#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include "SwingCompiler.h"
#include "StmtAST.h"

namespace swing
{
	class FunctionProtoAST : StmtAST
	{
		std::string _funcName;
		std::vector<std::string> _args;
	public:
		llvm::Value* CodeGen() override
		{
			std::vector<llvm::Type *> arg;
			llvm::FunctionType *FT =
				llvm::FunctionType::get(llvm::StructType::get(llvm::Type::getInt8Ty(g_Context)), false);

			llvm::Function *F =
				llvm::Function::Create(FT, llvm::Function::ExternalLinkage, _funcName, &g_Module);
			
			unsigned Idx = 0;
			for (auto &Arg : F->args())
				Arg.setName(_args[Idx++]);

			return F;
		}
	};
}

#endif
