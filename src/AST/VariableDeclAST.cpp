#include "VariableDeclAST.h"

namespace swing
{
	DeclAST::DeclPtr VariableDeclAST::Create(TokenIter& iter)
	{
		/// TODO : Struct를 만들 때 Struct에 해당하는 변수여야 하니까 이거 처리해야함.
		/// TODO : 현재 콘텍스트가 전역인지 로컬인지 Struct안인지 알아야 한다.
		auto* ast = new VariableDeclAST();
		
		std::string name;
		llvm::Type* type = nullptr;
		bool optional = false;

		if (iter->Is(TokenID::Type_Var))
		{
			++iter;
			iter->Expect(TokenID::Identifier);
			name = iter++->_name;

			/// 타입을 명시적으로 선언한 경우,
			if (iter->Is(TokenID::Colon))
			{
				++iter;
				type = g_SwingCompiler->_types[iter++->_name];
				if (iter->Is(TokenID::Optional_Nilable))
					optional = true;

				if (iter++->Is(TokenID::Assignment))
				{
					ast->_initValue = ExprAST::CreateTopLevelExpr(iter);
					if (type != ast->_initValue->GetType())
						throw ParsingError(*iter, "VariableDeclAST error, expression type is different from the specified type.");
				}
			}
			/// 타입 추론이 필요한 경우,
			else
			{
				iter++->Expect(TokenID::Assignment);
				ast->_initValue = ExprAST::CreateTopLevelExpr(iter);
				type = ast->_initValue->GetType();
			}

			g_SwingCompiler->_globalTable.AddVariable(new Variable(type, name, false, false, optional));
			ast->_variable = g_SwingCompiler->_globalTable.Find(name);
		}
		else if (iter->Is(TokenID::Type_Let))
		{
			g_SwingCompiler->_globalTable.AddVariable(new Variable(type, name, true, false, optional));
		}
		else
			throw ParsingError(*iter, "Unexpected Token, VariableDeclAST, expect var or let.");

		return DeclPtr(ast);
	}

	llvm::Value* VariableDeclAST::CodeGen()
	{
		/// Alloca 수행.
		_variable->CreateAlloca();

		/// 초기값이 있으면 초기값을 할당. (Store)
		if (_initValue != nullptr)
			_variable->SetValue(_initValue->CodeGen());
		return nullptr;
	}
}
