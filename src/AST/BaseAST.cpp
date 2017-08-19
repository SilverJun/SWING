#include "BaseAST.h"
#include "Error.h"
#include "FunctionDeclAST.h"
#include "VariableDeclAST.h"
#include "ExprAST.h"
#include "ReturnAST.h"
#include "StructDeclAST.h"
#include "ExtensionDeclAST.h"
#include "ProtocolDeclAST.h"

namespace swing
{
	BaseAST::BasePtr BaseAST::Create(TokenIter& iter)
	{
		/// 하나의 처리 단위가 될법한 애들을 케이스별로 나눠서 생성해준다.
		switch (iter->_id)
		{
		case TokenID::Func_Decl:
			return FunctionDeclAST::Create(iter);

		case TokenID::Type_Var:
		//case TokenID::Type_Let:
			return VariableDeclAST::Create(iter);

		case TokenID::Protocol_Decl:
			return ProtocolDeclAST::Create(iter);

		case TokenID::Struct_Decl:
			return StructDeclAST::Create(iter);

		case TokenID::Extension_Decl:
			return ExtensionDeclAST::Create(iter);
		
		case TokenID::Stmt_Return:
			return ReturnAST::Create(iter);

		case TokenID::Operator:
		case TokenID::Boolean_Value:
		case TokenID::OpenSmall:
		case TokenID::Literal_Integer:
		case TokenID::Literal_Float:
		case TokenID::Literal_Double:
		case TokenID::Literal_Letter:
		case TokenID::Literal_String:
		case TokenID::Identifier:	/// Maybe assign or member call, function call.
			return ExprAST::CreateTopLevelExpr(iter);

		default:
			throw ParsingError(*iter, "Unexpected Token");
		}
	}
}
