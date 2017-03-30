#ifndef _SWING_TOKEN_H_
#define _SWING_TOKEN_H_

#include <list>
#include <string>

namespace swing
{
	enum class TokenID
	{
		Eof = 0,

		Unknown,

		Comma = ',',
		Equal = '=',
		Quotmark = '"',
		Cross = '+',
		Hyphen = '-',
		Asterisk = '*',
		ForwardSlash = '/',
		Percent = '%',
		Ampersand = '&',
		Bar = '|',
		Circumflex = '^',
		Less = '<',
		Great = '>',
		Exclamation = '!',
		OpenSmall = '(',
		CloseSmall = ')',
		OpenMedium = '{',
		CloseMedium = '}',
		OpenBig = '[',
		CloseBig = ']',
		Colon = ':',
		Dot = '.',
		wave = '~',
		Question = '?',

		Type_Var = 256,
		Type_Let,
		Type_Nil,
		Type_Int,
		Type_Double,
		Type_String,
		Type_Array,
		Type_Dictionary,
		Type_Tuple,
		Type_UserDefined,

		Stmt_If,
		Stmt_Else,
		Stmt_Guard,
		Stmt_While,
		Stmt_For,
		Stmt_In,

		Stmt_Public,
		Stmt_Private,
		Stmt_Inherit,	//protected

		Func_Decl,
		Func_ReturnType,
		Func_Call,
		Func_Return,

		Struct_Decl,
		Enum_Decl,
		Class_Decl,
		Protocol_Decl,
		Extension_Decl,

		Operator_Prefix,
		Operator_Infix,
		Operator_Postfix,

		Operator_UserDefined,

		Identifier,	//변수나 클래스나 함수등 사용자 지정 이름

		Literal_Integer, //정수
		Literal_Double, //부동소수점
		Literal_Letter,	//문자
		Literal_String,	//문자열

		StringInterpolation_Start,
		StringInterpolation_End,

		Assignment,

		Arithmetic_Add,
		Arithmetic_Subtract,
		Arithmetic_Multiply,
		Arithmetic_Divide,
		Arithmetic_Modulo,
		Arithmetic_Power,

		Relational_Equal,
		Relational_NotEqual,
		Relational_Greater,
		Relational_Less,
		Relational_GreaterEqual,
		Relational_LessEqual,

		Bitwise_And,
		Bitwise_Or,
		Bitwise_Not,
		Bitwise_Xor,
		Bitwise_ShiftRight,
		Bitwise_ShiftLeft,

		Logical_And,
		Logical_Or,
		Logical_Not,

		Optional_Nilable,		/// ?
		Optional_Binding,		/// !

		Range_Closed,	/// m...n : [m,n]
		Range_Opend,	/// m..<n : [m,n)

	};

	struct Token
	{
		TokenID _id;
		int _line;
		int _iNumber;
		char _char;
		double _dNumber;
		std::string _name;

		Token(TokenID id, int line, double number = 0, std::string name = "") :
			_id(id),
			_line(line),
			_iNumber(0),
			_char(0),
			_dNumber(number),
			_name(name)
		{ }

		Token(TokenID id, int line, int number = 0, std::string name = "") :
			_id(id),
			_line(line),
			_dNumber(0),
			_char(0),
			_iNumber(number),
			_name(name)
		{ }

		Token(TokenID id, int line, char number = 0, std::string name = "") :
			_id(id),
			_line(line),
			_iNumber(0),
			_dNumber(0),
			_char(number),
			_name(name)
		{ }

		Token(TokenID id, int line, std::string name = "") :
			_id(id),
			_line(line),
			_iNumber(0),
			_char(0),
			_dNumber(0),
			_name(name)
		{ }
	};

	using TokenList = std::list<Token>;
	using TokenListIter = TokenList::iterator;

	inline std::ostream& operator<<(std::ostream& os, TokenList& list)
	{
		for (auto iter = list.begin(); iter != list.end(); ++iter)
		{
			os << static_cast<int>((*iter)._id) << " " << (*iter)._name << " " << (*iter)._iNumber << (*iter)._dNumber << (*iter)._char << std::endl;
		}
		return os;
	}

	struct Keyword
	{
		TokenID _id;
		std::string _word;

		Keyword(TokenID id, std::string word) : _id(id), _word(word) {}
	};
}

#endif
