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
		Assignment = '=',
		Quotmark = '"',
		Plus = '+',
		Minus = '-',
		Multi = '*',
		Divide = '/',
		Mod = '%',
		And = '&',
		Or = '|',
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
		Type_UserType,

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
		Class_Decl,
		Protocol_Decl,
		Extension_Decl,

		Operator_Prefix,
		Operator_Infix,
		Operator_Postfix,

		Identifier,	//변수나 클래스나 함수등 사용자 지정 이름

		Literal_Integer, //정수
		Literal_Double, //부동소수점
		Literal_Letter,	//문자
		Literal_String,	//문자열

		Annotation_Line,	//주석
		Annotation_Block_Open,	// /*
		Annotation_Block_Close,	// */

		LessEqual,
		GreatEqual,
		Equal,
		NotEqual,

		Bitwise_And,
		Bitwise_Or,
		Bitwise_Not,

		Logical_And,
		Logical_Or,
		Logical_Not,

		Optional_Nilable,		/// ?
		Optional_Binding,		/// !

		Power,		/// ^

		Range_Closed,	/// m...n : [m,n]
		Range_Opend,	/// m..<n : [m,n)

		User_Operator,
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

	struct Keyword
	{
		TokenID _id;
		std::string _word;

		Keyword(TokenID id, std::string word) : _id(id), _word(word) {}
	};
}

#endif
