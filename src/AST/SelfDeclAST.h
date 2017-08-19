#ifndef _SWING_SELF_DECL_AST_H_
#define _SWING_SELF_DECL_AST_H_
#include "DeclAST.h"

namespace swing
{
	class SelfDeclAST : public DeclAST
	{
	public:
		Method* _method;

		static DeclPtr Create(Method* method)
		{
			auto ast = new SelfDeclAST();
			ast->_method = method;

			return DeclPtr(ast);
		}

		llvm::Value* CodeGen() override
		{
			/// Self 등록.


			Variable* selfValue = _method->_funcBody->_localTable->Find("self");
			selfValue->_value = g_Builder.CreateLoad(selfValue->GetValue());
			selfValue->_type = selfValue->_value->getType();
			/*
			llvm::Value* selfAddr = g_Builder.CreateAlloca(selfValue->GetType(), nullptr, "self.addr");
			g_Builder.CreateStore(selfValue->_value, selfAddr);
			
			selfValue->_value = g_Builder.CreateLoad(selfAddr);
			selfValue->_type = selfValue->_value->getType();
			*/
			/// StructVariable 을 넣는 과정.
			if (_method->_struct != nullptr)
			{
				for (auto value : _method->_struct->_value)
				{
					llvm::Value* ptr = g_Builder.CreateStructGEP(_method->_struct->_type, selfValue->GetValue(), _method->_struct->GetElement(value._name)->_idx);
					_method->_funcBody->_localTable->_variables.push_back(new Variable(ptr, value._name, false, false, false));
				}
			}

			return nullptr;
		}
	};
}

#endif
