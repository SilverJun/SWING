#ifndef _SWING_FUNC_CALL_AST_H_
#define _SWING_FUNC_CALL_AST_H_

#include "ExprAST.h"
#include "Error.h"
#include "FunctionDeclAST.h"

namespace swing
{
	class FunctionCallAST : public ExprAST
	{
		std::string _funcName;
		std::map<std::string, ExprPtr> _args;

	public:

		static ExprPtr Create(TokenIter& iter)
		{
			/*
			 * (const std::string &Callee, std::vector<ExprPtr> Args) :
			_callee(Callee), _args(Args)
			 */
			auto* ast = new FunctionCallAST();

			iter->Expect(TokenID::Identifier);
			ast->_funcName = iter++->_name;
			iter++->Expect(TokenID::OpenSmall);

			while (!iter->Is(TokenID::CloseSmall))
			{
				iter->Expect(TokenID::Identifier);
				std::string argName = iter++->_name;
				iter++->Expect(TokenID::Colon);
				ast->_args[argName] = CreateTopLevelExpr(iter);
				++iter;
				if (!iter->Is(TokenID::Comma))
					break;
			}
			++iter;

			return ExprPtr(ast);
		}

		virtual ~FunctionCallAST() {}

		llvm::Value* CodeGen() override
		{
			FunctionDeclAST* functionAST = g_SwingCompiler->GetFunction(_funcName);
			llvm::Function* callFunc = functionAST->_func;
			if (!callFunc)
				throw Error("FunctionCall Error! in CalleeF");

			if (callFunc->arg_size() != _args.size())
				throw Error("FunctionCall Error! argument mismatch");
			
			/// 인자 순서 맞추기.

			std::vector<llvm::Value*> callArgs;
			auto declArgs = functionAST->_args;
			
			for (auto arg = declArgs.begin(); arg != declArgs.end(); ++arg)
			{
				/// 키가 존재하는지.
				if (_args.count((*arg)->GetName()))
				{
					llvm::Value* value = _args[(*arg)->GetName()]->CodeGen();
					
					if (value->getType() == (*arg)->GetType())
					{
						callArgs.push_back(value);
					}
				}
				else
					throw Error("FunctionCall Error!, there is no argument: " + (*arg)->GetName());
			}

			return g_Builder.CreateCall(callFunc->getFunctionType(), callFunc, callArgs);
		}
	};
}

#endif
