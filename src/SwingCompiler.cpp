#include "SwingCompiler.h"

#include "llvm/Support/TargetSelect.h"
#include "Type.h"
#include "FunctionDeclAST.h"
#include <iostream>

namespace swing
{
	std::unique_ptr<SwingCompiler> SwingCompiler::_instance;
	std::once_flag SwingCompiler::_InitInstance;

	SwingCompiler::SwingCompiler() : _module("SwingCompiler", _llvmContext), _builder({ llvm::IRBuilder<>(_llvmContext) })
	{
		llvm::InitializeNativeTarget();
		llvm::InitializeNativeTargetAsmParser();
		llvm::InitializeNativeTargetAsmPrinter();
		llvm::InitializeNativeTargetDisassembler();
		
		/// built-in Operators
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Additive, { "+", TokenID::Arithmetic_Add, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Additive }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Additive, { "-", TokenID::Arithmetic_Subtract, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Additive }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Multiplicative, { "*", TokenID::Arithmetic_Multiply, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Multiplicative }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Multiplicative, { "/", TokenID::Arithmetic_Divide, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Multiplicative }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Multiplicative, { "%", TokenID::Arithmetic_Modulo, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Multiplicative }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Multiplicative, { "**", TokenID::Arithmetic_Power, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Multiplicative }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Assignment, { "=", TokenID::Assignment, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Assignment }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Bitwise, { "&", TokenID::Bitwise_And, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Bitwise }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Bitwise, { "|", TokenID::Bitwise_Or, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Bitwise }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Bitwise, { "^", TokenID::Bitwise_Xor, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Bitwise }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Bitwise, { ">>", TokenID::Bitwise_ShiftRight, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Bitwise }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Bitwise, { "<<", TokenID::Bitwise_ShiftLeft, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Bitwise }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Logical, { "&&", TokenID::Logical_And, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Logical }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Logical, { "||", TokenID::Logical_Or, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Logical }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Relational, { "==", TokenID::Relational_Equal, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Relational }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Relational, { "!=", TokenID::Relational_Equal, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Relational }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Relational, { ">", TokenID::Relational_Equal, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Relational }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Relational, { ">=", TokenID::Relational_Equal, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Relational }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Relational, { "<", TokenID::Relational_Equal, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Relational }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Relational, { "<=", TokenID::Relational_Equal, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Relational }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Default, { "...", TokenID::Range_Closed, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Default }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Default, { "..<", TokenID::Range_Opened, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Default }));
		_binOperators.insert(std::pair<int, OperatorType>(70, { "as", TokenID::Casting_As, OperatorType::OperatorLocation::Infix, 70 }));
		_binOperators.insert(std::pair<int, OperatorType>(70, { "is", TokenID::Casting_Is, OperatorType::OperatorLocation::Infix, 70 }));
	
		_preOperators.push_back(OperatorType("!", TokenID::Logical_Not, OperatorType::OperatorLocation::Prefix, OperatorType::Precedence_Logical));
		_preOperators.push_back(OperatorType("~", TokenID::Bitwise_Not, OperatorType::OperatorLocation::Prefix, OperatorType::Precedence_Bitwise));
		
		_postOperators.push_back(OperatorType("?", TokenID::Optional_Nilable, OperatorType::OperatorLocation::Postfix, OperatorType::Precedence_Default));
		_postOperators.push_back(OperatorType("!", TokenID::Optional_Binding, OperatorType::OperatorLocation::Postfix, OperatorType::Precedence_Default));
	}

	std::vector<OperatorType*> SwingCompiler::FindOps(int precedenceLevel)
	{
		auto range = _binOperators.equal_range(precedenceLevel);
		std::vector<OperatorType*> ops;

		if (precedenceLevel >= OperatorType::Precedence_Max)
			return ops;

		for (auto value = range.first; value != range.second; ++value)
			ops.push_back(&value->second);

		return ops;
	}

	OperatorType* SwingCompiler::FindPreFixOp(std::string op)
	{
		for (auto value : _preOperators)
		{
			if (value._opString == op)
				return &value;
		}
		return nullptr;
	}

	OperatorType* SwingCompiler::FindPostFixOp(std::string op)
	{
		for (auto value : _postOperators)
		{
			if (value._opString == op)
				return &value;
		}
		return nullptr;
	}

	std::string SwingCompiler::OpNameMangling(OperatorType* op)
	{
		/// Make Name Mangling.
		std::string mangled = GetOpLocationString(op->_opLocation);
		mangled += "@";
		mangled += GetTypeString(op->_returnType);
		mangled += "@";
		mangled += op->_opString;
		mangled += "@";
		mangled += GetTypeString(op->_typeOne);
		mangled += "@";
		mangled += GetTypeString(op->_typeTwo);

		return mangled;
	}

	void SwingCompiler::AddOperator(OperatorType* op)
	{
		/// TODO : 기능 구현.
	}

	void SwingCompiler::AddFunction(std::string name, FunctionDeclAST* func)
	{
		_functions[name] = func;
	}

	FunctionDeclAST* SwingCompiler::GetFunction(std::string name)
	{
		return _functions[name];
	}

	SwingCompiler* SwingCompiler::GetInstance()
	{
		std::call_once(_InitInstance, []()
	    {
		    _instance.reset(new SwingCompiler);
	    });

		return _instance.get();
	}

	SwingCompiler::~SwingCompiler()
	{
	}

	void SwingCompiler::PushIRBuilder(llvm::IRBuilder<> builder)
	{
		_builder.push_back(builder);
	}

	void SwingCompiler::PopIRBuilder()
	{
		_builder.pop_back();
	}

	void SwingCompiler::CompileSource(std::string name)
	{
		/// built-in types
		_types["void"] = Void;
		_types["bool"] = Bool;
		_types["char"] = Char;
		_types["int"] = Int;
		_types["float"] = Float;
		_types["double"] = Double;

		Source* src = new Source(name);
		Lexer lex;
		try
		{
			lex.LexSource(src);
			src->Parse();
			src->CodeGen();
		}
		catch (LexicalError& e)
		{
			std::cout << e.what() << std::endl;
			exit(-1);
		}
		catch (ParsingError& e)
		{
			std::cout << e.what() << std::endl;
			exit(-1);
		}
		catch (Error& e)
		{
			std::cout << e.what() << std::endl;
			exit(-1);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			exit(-1);
		}

		/// llc
		std::string cmd("llc");
		cmd += ' ';
		cmd += "-filetype=obj";
		cmd += ' ';
		cmd += "C:\\Users\\SilverJun\\SwingTestProject\\Test.ll";
		cmd += ' ';
		cmd += "-o C:\\Users\\SilverJun\\SwingTestProject\\Test.obj";

		system(cmd.c_str());

		/// clang-cl
		cmd = "clang-cl";
		cmd += ' ';
		cmd += "-o C:\\Users\\SilverJun\\SwingTestProject\\Test.exe";
		cmd += ' ';
		cmd += "C:\\Users\\SilverJun\\SwingTestProject\\Test.obj";
		cmd += ' ';
		cmd += "C:\\Users\\SilverJun\\SwingTestProject\\libcmt.lib";
		cmd += ' ';
		cmd += "C:\\Users\\SilverJun\\SwingTestProject\\libswing.o";
		cmd += ' ';
		cmd += "C:\\Users\\SilverJun\\SwingTestProject\\io.o";

		system(cmd.c_str());
	}

	void SwingCompiler::CompileProject(Project* project, int optLevel, std::string outputFormat)
	{
		project->CompileProject(optLevel, outputFormat);
	}

	void SwingCompiler::LinkProject(Project* project)
	{
		project->LinkProject();
	}

	void SwingCompiler::BuildProject(Project* project)
	{
		CompileProject(project, 0, ".obj");
		LinkProject(project);
	}
}
