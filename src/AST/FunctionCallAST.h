#ifndef _SWING_FUNC_CALL_AST_H_
#define _SWING_FUNC_CALL_AST_H_

#include "ExprAST.h"
#include "Error.h"

namespace swing
{
	class FunctionCallAST : public ExprAST
	{
		std::string _callee;
		std::vector<std::unique_ptr<ExprAST>> _args;

	public:
		FunctionCallAST(const std::string &Callee, std::vector<std::unique_ptr<ExprAST>> Args)
		: _callee(Callee), _args(move(Args))
		{
		}

		virtual ~FunctionCallAST() {}

		llvm::Value* CodeGen() override
		{
			llvm::Function* CalleeF = g_SwingCompiler.GetModule().getFunction(_callee);
			if (!CalleeF)
				throw Error(__LINE__, "FunctionCall Error! in CalleeF");

			if (CalleeF->arg_size() != _args.size())
				throw Error(__LINE__, "FunctionCall Error! argument mismatch");

			std::vector<llvm::Value*> ArgsV;
			for (size_t i = 0; i != _args.size(); ++i) {
				ArgsV.push_back(_args[i]->CodeGen());
				if (!ArgsV.back())
					return nullptr;
			}
			return g_SwingCompiler.GetBuilder().CreateCall(CalleeF, ArgsV, _callee.c_str());
		}
	};
}

#endif
