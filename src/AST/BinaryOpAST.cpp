#include "BinaryOpAST.h"
#include "UnaryOpAST.h"
#include "VariableAST.h"
#include "Type.h"

namespace swing
{
	ExprAST::ExprPtr BinaryOpAST::Create(TokenIter& iter, int PrecedenceLevel)
	{
		auto ast = std::shared_ptr<BinaryOpAST>();
		ast.reset(new BinaryOpAST());

		/// 연산자 우선순위가 높은 항 부터 찾아서 파싱해야 한다.
		do
		{
			ast->_opCandidates = g_SwingCompiler->FindOps(++PrecedenceLevel);
		}
		while (PrecedenceLevel < OperatorType::Precedence_Max && ast->_opCandidates.size() == 0);

		/// LHS항 넣기.
		if (PrecedenceLevel >= OperatorType::Precedence_Max)
			ast->_exprList.push_back(UnaryOpAST::Create(iter));
		else
			ast->_exprList.push_back(BinaryOpAST::Create(iter, PrecedenceLevel));

		while (true)
		{
			/// operator 찾기.
			int size = ast->_opTypes.size();
			for (auto op : ast->_opCandidates)
			{
				if (iter->_name == op->_opString)
				{
					ast->_opTypes.push_back(op);
					break;
				}
			}

			if (size == ast->_opTypes.size())
				break;

			++iter;

			/// RHS항 넣기.
			ast->_exprList.push_back(BinaryOpAST::Create(iter, PrecedenceLevel));
		}
		
		return ast->_opTypes.size() == 0 ? ast->_exprList.front() : ExprPtr(ast);
	}

	BinaryOpAST::~BinaryOpAST()
	{
	}

	llvm::Type* BinaryOpAST::GetType()
	{
		return _exprList.begin()->get()->GetType();
	}

	llvm::Value* BinaryOpAST::CodeGen()
	{
		/// Built-in 한 op들은 if else를 통해 문자열 비교해서 codegen한다.
		/// 아닌것들은 opmangling된 이름을 가지고 function call 한다.

		/// _exprList의 항이 하나만 있으면 걍 해당식 CodeGen을 리턴한다. 부가연산 없다.

		switch (_opTypes.front()->_tokenID)
		{
		case TokenID::Assignment:
		{
			VariableExprAST* varAst = dynamic_cast<VariableExprAST*>(_exprList.front().get());
			g_SwingCompiler->_globalTable.Find(varAst->_variableName)->SetValue(_exprList.back().get()->CodeGen());
			return nullptr;
		}
		case TokenID::Arithmetic_Add:
		{
			auto* value = _exprList.begin()->get()->CodeGen();
			auto* type = value->getType();
			auto rhs = ++_exprList.begin();

			if (type == Int)
			{
				while (rhs == _exprList.end())
					value = g_Builder.CreateAdd(value, rhs++->get()->CodeGen(), "additmp");
			}
			else if(type == Float || type == Double)
			{
				
			}
			else
			{
			}
		}
		case TokenID::Arithmetic_Subtract:
		{

		}
		case TokenID::Arithmetic_Multiply:
		{
		}
		case TokenID::Arithmetic_Divide:
		{
		}
		case TokenID::Arithmetic_Modulo:
		{
		}
		case TokenID::Arithmetic_Power:
		{
		}
		default:
			throw Error("Unknown infix Operator");
		}


	}
}
