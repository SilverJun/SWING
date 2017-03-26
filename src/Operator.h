#ifndef _SWING_OPERATOR_H_
#define _SWING_OPERATOR_H_

#include <string>
#include "Token.h"

namespace swing
{
	struct OperatorData
	{
		enum OperatorType
		{
			Prefix,		/// 앞에 나오는 연산자
			Infix,		/// 중간에 나오는 연산자, 항이 두개 필요한 연산자
			Postfix		/// 뒤에 나오는 연산자
		};

		std::string _operatorName;
		OperatorType _opType;
		TokenID _tokenID;

	public:
		OperatorData()
		{
			
		}
	};
}

#endif
