#ifndef _SWING_FUNC_CALL_AST_H_
#define _SWING_FUNC_CALL_AST_H_

#include "ExprAST.h"
#include "Error.h"
#include "FunctionDeclAST.h"

namespace swing
{
	class FunctionCallAST : public ExprAST
	{
	public:
		std::string _funcName;
		std::map<std::string, ExprPtr> _args;
		std::vector<llvm::Value*> _callArgs;

		static ExprPtr Create(TokenIter& iter)
		{
			/// TODO : Struct에 있는 멤버 함수인지 체크를 해야 한다.
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
				if (iter->Is(TokenID::Comma))
					++iter;
			}
			++iter;

			return ExprPtr(ast);
		}

		virtual ~FunctionCallAST() {}

		llvm::Value* CodeGen() override
		{
			Method* method = g_SwingCompiler->GetFunction(_funcName);
			llvm::Function* callFunc = method->_func;
			if (!callFunc)
				throw Error("FunctionCall Error! in CalleeF");

			if (callFunc->arg_size() != _args.size())
				throw Error("FunctionCall Error! argument mismatch");
			
			/// 인자 순서 맞추기.

			auto declArgs = method->_args;
			
			for (auto arg = declArgs.begin(); arg != declArgs.end(); ++arg)
			{
				if ("self" == (*arg)->GetName())
					continue;

				/// 키가 존재하는지.
				if (_args.count((*arg)->GetName()))
				{
					llvm::Value* value = _args[(*arg)->GetName()]->CodeGen();
					
					if (value->getType() == (*arg)->GetType())
						_callArgs.push_back(value);
				}
				else
					throw Error("FunctionCall Error!, there is no argument: " + (*arg)->GetName());
			}

			return g_Builder.CreateCall(callFunc->getFunctionType(), callFunc, _callArgs);
		}
	};
}

#endif
