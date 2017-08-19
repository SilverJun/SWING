#include "Token.h"
#include "Error.h"
#include "Type.h"
#include "SwingCompiler.h"

namespace swing
{
	void Token::Expect(const TokenID id) const
	{
		if (this->_id != id)
			throw ParsingError(*this, "Unexpected Token");
	}

	bool Token::Is(const TokenID id) const
	{
		return this->_id == id;
	}

	llvm::Type* Token::GetType() const
	{
		switch (this->_type)
		{
		case TokenTypeTag::_char:
			return Char;
		case TokenTypeTag::_int:
			return Int;
		case TokenTypeTag::_float:
			return Float;
		case TokenTypeTag::_double:
			return Double;
		case TokenTypeTag::_notuse:
			{
				switch (this->_id)
				{
				case TokenID::Type_Void:
					return Void;
				case TokenID::Type_Bool:
				case TokenID::Boolean_Value:
					return Bool;
				case TokenID::Type_Char:
					return Char;
				case TokenID::Type_Int:
					return Int;
				case TokenID::Type_Float:
					return Float;
				case TokenID::Type_Double:
					return Double;
				case TokenID::Identifier:
					{
					llvm::Type* type = nullptr;
					type = g_SwingCompiler->_globalTable.Find(this->_name)->GetType();
					if (type != nullptr)
						return type;
					type = g_SwingCompiler->GetType(this->_name);
					if (type != nullptr)
						return type;
					}
				default:
					return nullptr;
				}
			}
		}
	}

	bool IsSamePattern(TokenIter iter, TokenPattern pattern)
	{
		for (auto id : pattern)
		{
			if (iter->Is(id))
				return false;
			iter = std::next(iter);
		}
		return true;
	}

	std::ostream& operator<<(std::ostream& os, Token& token)
	{
		os << token._name << ":" << std::to_string(token._line) << "> Token id:" << static_cast<int>(token._id) << ", ";
		switch (token._type)
		{
		case Token::TokenTypeTag::_notuse:
			os << token._name << std::endl;
			break;
		case Token::TokenTypeTag::_char:
			os << token._char << std::endl;
			break;
		case Token::TokenTypeTag::_int:
			os << token._int << std::endl;
			break;
		case Token::TokenTypeTag::_float:
			os << token._float << std::endl;
			break;
		case Token::TokenTypeTag::_double:
			os << token._double << std::endl;
			break;
		}
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Token& token)
	{
		os << token._name << ":" << std::to_string(token._line) << "> Token id:" << static_cast<int>(token._id) << ", ";
		switch (token._type)
		{
		case Token::TokenTypeTag::_notuse:
			os << token._name << std::endl;
			break;
		case Token::TokenTypeTag::_char:
			os << token._char << std::endl;
			break;
		case Token::TokenTypeTag::_int:
			os << token._int << std::endl;
			break;
		case Token::TokenTypeTag::_float:
			os << token._float << std::endl;
			break;
		case Token::TokenTypeTag::_double:
			os << token._double << std::endl;
			break;
		}
		return os;
	}
}
