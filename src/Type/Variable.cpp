#include "Variable.h"
#include "Error.h"
#include "SwingCompiler.h"

namespace swing
{
	Variable::Variable(llvm::Type* type, std::string name):
		_isOptional(true),
		_isLet(false),
		_isInout(false),
		_name(name),
		_type(type),
		_value(nullptr)
	{
	}

	Variable::Variable(llvm::Type* type, std::string name, bool let, bool inout, bool optional):
		_isOptional(optional),
		_isLet(let),
		_isInout(inout),
		_name(name),
		_type(type),
		_value(nullptr)
	{
	}

	Variable::Variable(llvm::Type* type, llvm::Value* value, std::string name, bool let, bool inout, bool optional):
		_isOptional(optional),
		_isLet(let),
		_isInout(inout),
		_name(name),
		_type(type)
	{
	}

	Variable::~Variable()
	{
	}

	void Variable::CreateAlloca()
	{
		_value = g_Builder.CreateAlloca(_type, nullptr, _name);
	}

	void Variable::SetValue(llvm::Value* value)
	{
		if (!_isOptional && value == nullptr)
			throw Error("Variable can`t be nil. Variable is not optional.");

		_value = value;
	}

	void Variable::SetNil()
	{
		if (_isOptional)
			_value = nullptr;
		else
			throw Error("SetNil Error!, " + _name + " is not optional type.");
	}

	llvm::Value* Variable::GetValue() const
	{
		return _value;
	}

	Variable* Variable::operator=(Variable& rhs)
	{
		if (rhs.IsNil() == true && this->IsOptional() == false)
			throw Error("can't assign Nil value to not optional value");

		g_Builder.CreateStore(rhs.GetValue(), this->_value);

		return this;
	}
}
