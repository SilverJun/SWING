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

		llvm::Value* value = _exprList.begin()->get()->CodeGen();
		llvm::Type* type;
		ExprList::iterator rhs = next(_exprList.begin());

		for (auto opIter = _opTypes.begin(); opIter != _opTypes.end(); ++opIter)
		{
			switch ((*opIter)->_tokenID)
			{
			case TokenID::Assignment:
			{
				if (_opTypes.size() > 1)
					throw Error("Only one Assignment per line is allowed.");

				VariableExprAST* varAST = dynamic_cast<VariableExprAST*>(_exprList[0].get());

				return g_Builder.CreateStore(rhs->get()->CodeGen(), varAST->CodeGenRef());
			}
			case TokenID::Arithmetic_Add:
				type = value->getType();

				if (type == Char || type == Int)
				{
					value = g_Builder.CreateAdd(value, rhs++->get()->CodeGen());
				}
				else if (type == Float || type == Double)
				{
					value = g_Builder.CreateFAdd(value, rhs++->get()->CodeGen());
				}
				else
				{
					/// TODO : User Defined Function Call.
				}
				break;
			case TokenID::Arithmetic_Subtract:
				type = value->getType();

				if (type == Char || type == Int)
				{
					value = g_Builder.CreateSub(value, rhs++->get()->CodeGen());
				}
				else if (type == Float || type == Double)
				{
					value = g_Builder.CreateFSub(value, rhs++->get()->CodeGen());
				}
				else
				{
					/// TODO : User Defined Function Call.
				}
				break;
			case TokenID::Arithmetic_Multiply:
				type = value->getType();

				if (type == Char || type == Int)
				{
					value = g_Builder.CreateMul(value, rhs++->get()->CodeGen());
				}
				else if (type == Float || type == Double)
				{
					value = g_Builder.CreateFMul(value, rhs++->get()->CodeGen());
				}
				else
				{
					/// TODO : User Defined Function Call.
				}
				break;
			case TokenID::Arithmetic_Divide:
				type = value->getType();

				if (type == Char || type == Int)
				{
					llvm::Value* rhsValue = rhs++->get()->CodeGen();
					if (rhsValue == llvm::ConstantInt::get(Char, llvm::APInt(8, 0)))
						throw Error("Expression is divided by zero!");
					if (rhsValue == llvm::ConstantInt::get(Int, llvm::APInt(32, 0)))
						throw Error("Expression is divided by zero!");
					value = g_Builder.CreateSDiv(value, rhsValue);
				}
				else if (type == Float || type == Double)
				{
					llvm::Value* rhsValue = rhs++->get()->CodeGen();
					if (rhsValue == llvm::ConstantFP::get(Float, 0.0f))
						throw Error("Expression is divided by zero!");
					if (rhsValue == llvm::ConstantFP::get(Double, 0.0f))
						throw Error("Expression is divided by zero!");
					value = g_Builder.CreateFDiv(value, rhsValue);
				}
				else
				{
					/// TODO : User Defined Function Call.
				}
				break;
			case TokenID::Arithmetic_Modulo:
				type = value->getType();

				if (type == Char || type == Int)
				{
					value = g_Builder.CreateSRem(value, rhs++->get()->CodeGen());
				}
				else if (type == Float || type == Double)
				{
					value = g_Builder.CreateFRem(value, rhs++->get()->CodeGen());
				}
				else
				{
					/// TODO : User Defined Function Call.
				}
				break;
			case TokenID::Arithmetic_Power:
				/// TODO : Lib Function call.
				break;
			case TokenID::Logical_And:
				/// TODO : Implement Logical And.
				break;
			case TokenID::Logical_Or:
				/// TODO : Implement Logical Or.
				break;
			case TokenID::Logical_Not:
				/// TODO : Implement Logical Not.
				break;
			case TokenID::Relational_Equal:
				/// TODO : Implement Relational Equal.
				break;
			case TokenID::Relational_NotEqual:
				/// TODO : Implement Relational NotEqual.
				break;
			case TokenID::Relational_Greater:
				/// TODO : Implement Relational Greater.
				break;
			case TokenID::Relational_GreaterEqual:
				/// TODO : Implement Relational GreaterEqual.
				break;
			case TokenID::Relational_Less:
				/// TODO : Implement Relational Less.
				break;
			case TokenID::Relational_LessEqual:
				/// TODO : Implement Relational LessEqual.
				break;

			default:
				throw Error("Unknown infix Operator");
			}
		}

		return value;
	}
}
