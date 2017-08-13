#ifndef _SWING_VARIABLE_H_
#define _SWING_VARIABLE_H_

#include <llvm/ADT/Optional.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace swing
{
	/**
	 * \brief SWING basic variable implement class.
	 */
	class Variable
	{
	public:
		friend class VariableDeclAST;
		bool _isOptional;
		bool _isLet;
		bool _isInout;

		std::string _name;
		llvm::Type* _type;
		llvm::Value* _value;

		Variable() = delete;
		/**
		 * \brief Type only variable.
		 * variable will be optional.
		 * variable can`t be let type.
		 * this variable init with nil.
		 */
		Variable(llvm::Type* type, std::string name);

		/**
		* \brief blueprint variable. no real value.
		* variable can be let, optional. it`s choice.
		*/
		Variable(llvm::Type* type, std::string name, bool let, bool inout, bool optional);

		/**
		 * \brief Full option variable.
		 */
		Variable(llvm::Type* type, llvm::Value* value, std::string name, bool let, bool inout, bool optional);

		~Variable();

		void CreateAlloca();
		void SetValue(llvm::Value* value);
		void SetNil();

		bool IsOptional() const { return _isOptional; }
		bool IsNil() const { return _value == nullptr; }
		bool isLet() const { return _isLet; }
		bool isInout() const { return _isInout; }
		std::string GetName() const { return _name; }
		llvm::Type* GetType() const { return _type; }
		llvm::Value* GetValue() const;

		Variable* operator=(Variable& rhs);
	};
}

#endif
