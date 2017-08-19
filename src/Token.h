#ifndef _SWING_TOKEN_H_
#define _SWING_TOKEN_H_

#include <vector>
#include <string>
#include <llvm/IR/Type.h>

namespace swing
{
	enum class TokenID
	{
		Eof = 0,

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
		Wave = '~',
		Question = '?',

		Type_Var = 256,
		Type_Let,
		Type_Nil,

		Type_Void,
		Type_Bool,
		Type_Char,
		Type_Int,
		Type_Float,
		Type_Double,
		Type_String,
		Type_Array,
		Type_Dictionary,
		Type_Tuple,

		Type_UserDefined,

		Stmt_If,
		Stmt_Else,
		Stmt_Switch,
		Stmt_Case,
		Stmt_Default,
		Stmt_Guard,
		Stmt_While,
		Stmt_For,
		Stmt_In,
		Stmt_Return,

		Stmt_Public,
		Stmt_Private,
		Stmt_Inherit,	//protected

		Func_Decl,
		Func_Call,
		Func_Inout,

		Struct_Decl,
		Enum_Decl,
		Class_Decl,
		Protocol_Decl,
		Extension_Decl,

		Operator_Prefix,
		Operator_Infix,
		Operator_Postfix,
		Operator_Decl,
		Operator_Precedence,

		Operator,
		Operator_UserDefined,

		Identifier,	//변수나 클래스나 함수등 사용자 지정 이름

		Literal_Integer, //정수
		Literal_Float,
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

		Boolean_Value,		/// true, false

		Optional_Nilable,		/// ?
		Optional_Binding,		/// !

		Range_Closed,	/// m...n : [m,n]
		Range_Opened,	/// m..<n : [m,n)

		Arrow,

		Casting_As,
		Casting_Is,

		MemberReference,
	};

	struct Token
	{
		TokenID _id;
		int _line;
		union
		{
			int _int;
			char _char;
			float _float;
			double _double;
		};
		std::string _sourceName;
		std::string _name;

		enum class TokenTypeTag
		{
			_notuse,
			_char,
			_int,
			_float,
			_double
		} _type;

		explicit Token(TokenID id, int line, std::string sourceName, int number, std::string name = "") :
			_id(id),
			_line(line),
			_int(number),
			_sourceName(sourceName),
			_name(name),
			_type(TokenTypeTag::_int)
		{ }

		explicit Token(TokenID id, int line, std::string sourceName, char number, std::string name = "") :
			_id(id),
			_line(line),
			_char(number),
			_sourceName(sourceName),
			_name(name),
			_type(TokenTypeTag::_char)
		{ }

		explicit Token(TokenID id, int line, std::string sourceName, float number, std::string name = "") :
			_id(id),
			_line(line),
			_float(number),
			_sourceName(sourceName),
			_name(name),
			_type(TokenTypeTag::_float)
		{ }

		explicit Token(TokenID id, int line, std::string sourceName, double number, std::string name = "") :
			_id(id),
			_line(line),
			_double(number),
			_sourceName(sourceName),
			_name(name),
			_type(TokenTypeTag::_double)
		{ }

		Token(TokenID id, int line, std::string sourceName, std::string name = "") :
			_id(id),
			_line(line),
			_double(0),
			_sourceName(sourceName),
			_name(name),
			_type(TokenTypeTag::_notuse)
		{ }

		void Expect(const TokenID id) const;
		bool Is(const TokenID id) const;
		llvm::Type* GetType() const;
	};

	using TokenList = std::vector<Token>;
	using TokenIter = TokenList::iterator;
	using TokenPattern = std::vector<TokenID>;
	bool IsSamePattern(TokenIter iter, TokenPattern pattern);

	std::ostream& operator<<(std::ostream& os, Token& token);
	std::ostream& operator<<(std::ostream& os, const Token& token);

	struct Keyword
	{
		TokenID _id;
		std::string _word;

		Keyword(TokenID id, std::string word) : _id(id), _word(word) {}
	};
}

#endif
