#ifndef _SWING_OPERATOR_H_
#define _SWING_OPERATOR_H_

#include "Token.h"
#include <llvm/IR/Type.h>

namespace swing
{
	struct OperatorType
	{
		enum class OperatorLocation
		{
			Prefix,		/// 앞에 나오는 연산자
			Infix,		/// 중간에 나오는 연산자, 항이 두개 필요한 연산자
			Postfix		/// 뒤에 나오는 연산자
		};

		enum PrecedenceLevel
		{
			Precedence_Min = 1,
			Precedence_Assignment = 2,
			Precedence_Relational = 10,
			Precedence_Logical = 20,
			Precedence_Default = 30,
			Precedence_Bitwise = 40,
			Precedence_Additive = 50,
			Precedence_Multiplicative = 60,
			Precedence_Max = 100
		};

		std::string _opString;
		TokenID _tokenID;
		OperatorLocation _opLocation;
		int _precedence;
		llvm::Type* _returnType;
		llvm::Type* _typeOne;
		llvm::Type* _typeTwo;

		OperatorType() {}

		OperatorType(std::string opString, TokenID tokId, OperatorLocation location, int level = Precedence_Default) :
			_opString(opString), _tokenID(tokId), _opLocation(location), _precedence(level), _returnType(nullptr), _typeOne(nullptr), _typeTwo(nullptr)
		{
		}
	};

	inline std::string GetOpLocationString(OperatorType::OperatorLocation loc)
	{
		switch (loc)
		{
		case OperatorType::OperatorLocation::Prefix:
			return "Prefix";
		case OperatorType::OperatorLocation::Infix:
			return "Infix";
		case OperatorType::OperatorLocation::Postfix:
			return "Postfix";
		}
	}
}

#endif
