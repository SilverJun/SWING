#include "BinaryOpAST.h"
#include "UnaryOpAST.h"
#include "VariableAST.h"
#include "Type.h"
#include "Error.h"

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
			/// 더 똑똑해져야 한다.
			/// 1. 일반 변수인지 확인해야 한다.
			/// 2. 멤버변수인지 확인해줘야 한다.

			VariableExprAST* varAst = dynamic_cast<VariableExprAST*>(_exprList.front().get());
			
			return g_Builder.CreateStore(_exprList.back().get()->CodeGen(), g_SwingCompiler->_globalTable.Find(varAst->_variableName)->GetValue());
		}
		case TokenID::Arithmetic_Add:
		{
			auto* value = _exprList.begin()->get()->CodeGen();
			auto* type = value->getType();
			auto rhs = ++_exprList.begin();

			if (type == Char || type == Int)
			{
				while (rhs == _exprList.end())
					value = g_Builder.CreateAdd(value, rhs++->get()->CodeGen(), "additmp");
			}
			else if(type == Float || type == Double)
			{
				while (rhs == _exprList.end())
					value = g_Builder.CreateFAdd(value, rhs++->get()->CodeGen(), "addftmp");
			}
			else
			{
				/// TODO : User Defined Function Call.
			}
		}
		case TokenID::Arithmetic_Subtract:
		{
			auto* value = _exprList.begin()->get()->CodeGen();
			auto* type = value->getType();
			auto rhs = ++_exprList.begin();

			if (type == Char || type == Int)
			{
				while (rhs == _exprList.end())
					value = g_Builder.CreateSub(value, rhs++->get()->CodeGen(), "subitmp");
			}
			else if (type == Float || type == Double)
			{
				while (rhs == _exprList.end())
					value = g_Builder.CreateFSub(value, rhs++->get()->CodeGen(), "subftmp");
			}
			else
			{
				/// TODO : User Defined Function Call.
			}
		}
		case TokenID::Arithmetic_Multiply:
		{
			auto* value = _exprList.begin()->get()->CodeGen();
			auto* type = value->getType();
			auto rhs = ++_exprList.begin();

			if (type == Char || type == Int)
			{
				while (rhs == _exprList.end())
					value = g_Builder.CreateMul(value, rhs++->get()->CodeGen(), "mulitmp");
			}
			else if (type == Float || type == Double)
			{
				while (rhs == _exprList.end())
					value = g_Builder.CreateFMul(value, rhs++->get()->CodeGen(), "mulftmp");
			}
			else
			{
				/// TODO : User Defined Function Call.
			}
		}
		case TokenID::Arithmetic_Divide:
		{
			auto* value = _exprList.begin()->get()->CodeGen();
			auto* type = value->getType();
			auto rhs = ++_exprList.begin();

			if (type == Char || type == Int)
			{
				while (rhs == _exprList.end())
					value = g_Builder.CreateSDiv(value, rhs++->get()->CodeGen(), "divitmp");
			}
			else if (type == Float || type == Double)
			{
				while (rhs == _exprList.end())
					value = g_Builder.CreateFDiv(value, rhs++->get()->CodeGen(), "divftmp");
			}
			else
			{
				/// TODO : User Defined Function Call.
			}
		}
		case TokenID::Arithmetic_Modulo:
		{
			/// TODO : Modulo Define
		}
		case TokenID::Arithmetic_Power:
		{
			/// TODO : Lib Function call.
		}
		default:
			throw Error("Unknown infix Operator");
		}
	}
}
