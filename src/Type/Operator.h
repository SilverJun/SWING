#ifndef _SWING_OPERATOR_H_
#define _SWING_OPERATOR_H_

#include "Token.h"
#include <llvm/IR/Type.h>

namespace swing
{
	struct OperatorType
	{
		enum OperatorLocation
		{
			Prefix,		/// 앞에 나오는 연산자
			Infix,		/// 중간에 나오는 연산자, 항이 두개 필요한 연산자
			Postfix		/// 뒤에 나오는 연산자
		};

		OperatorLocation _opLocation;
		TokenID _tokenID;
		llvm::Type* _type;

		OperatorType()
		{
			
		}
	};
}

#endif
