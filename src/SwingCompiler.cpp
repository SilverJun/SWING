#include "SwingCompiler.h"

#include "llvm/Support/TargetSelect.h"
#include "Type.h"
#include "Method.h"
#include "StructType.h"
#include "ProtocolType.h"
#include <iostream>
#include "Error.h"
#include "FunctionDeclAST.h"

namespace swing
{
	std::unique_ptr<SwingCompiler> SwingCompiler::_instance;
	std::once_flag SwingCompiler::_InitInstance;

	SwingCompiler::SwingCompiler() : _module("SwingCompiler", _llvmContext), _builder({ llvm::IRBuilder<>(_llvmContext) }), _src(nullptr)
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
		//_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Multiplicative, { "**", TokenID::Arithmetic_Power, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Multiplicative }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Assignment, { "=", TokenID::Assignment, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Assignment }));
		/*
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Bitwise, { "&", TokenID::Bitwise_And, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Bitwise }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Bitwise, { "|", TokenID::Bitwise_Or, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Bitwise }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Bitwise, { "^", TokenID::Bitwise_Xor, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Bitwise }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Bitwise, { ">>", TokenID::Bitwise_ShiftRight, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Bitwise }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Bitwise, { "<<", TokenID::Bitwise_ShiftLeft, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Bitwise }));
		*/
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Logical, { "&&", TokenID::Logical_And, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Logical }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Logical, { "||", TokenID::Logical_Or, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Logical }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Relational, { "==", TokenID::Relational_Equal, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Relational }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Relational, { "!=", TokenID::Relational_NotEqual, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Relational }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Relational, { ">", TokenID::Relational_Greater, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Relational }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Relational, { ">=", TokenID::Relational_GreaterEqual, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Relational }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Relational, { "<", TokenID::Relational_Less, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Relational }));
		_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Relational, { "<=", TokenID::Relational_LessEqual, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Relational }));
		//_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Default, { "...", TokenID::Range_Closed, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Default }));
		//_binOperators.insert(std::pair<int, OperatorType>(OperatorType::Precedence_Default, { "..<", TokenID::Range_Opened, OperatorType::OperatorLocation::Infix, OperatorType::Precedence_Default }));
		_binOperators.insert(std::pair<int, OperatorType>(70, { "as", TokenID::Casting_As, OperatorType::OperatorLocation::Infix, 70 }));
		_binOperators.insert(std::pair<int, OperatorType>(70, { "is", TokenID::Casting_Is, OperatorType::OperatorLocation::Infix, 70 }));
		_binOperators.insert(std::pair<int, OperatorType>(80, { ".", TokenID::MemberReference, OperatorType::OperatorLocation::Infix, 80 }));


		_preOperators.push_back(OperatorType("!", TokenID::Logical_Not, OperatorType::OperatorLocation::Prefix, OperatorType::Precedence_Logical));
		//_preOperators.push_back(OperatorType("~", TokenID::Bitwise_Not, OperatorType::OperatorLocation::Prefix, OperatorType::Precedence_Bitwise));
		
		//_postOperators.push_back(OperatorType("?", TokenID::Optional_Nilable, OperatorType::OperatorLocation::Postfix, OperatorType::Precedence_Default));
		//_postOperators.push_back(OperatorType("!", TokenID::Optional_Binding, OperatorType::OperatorLocation::Postfix, OperatorType::Precedence_Default));
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
		for (auto value = _preOperators.begin(); value != _preOperators.end(); ++value)
		{
			if (value->_opString == op)
				return &*value;
		}
		return nullptr;
	}

	OperatorType* SwingCompiler::FindPostFixOp(std::string op)
	{
		for (auto value = _postOperators.begin(); value != _postOperators.end(); ++value)
		{
			if (value->_opString == op)
				return &*value;
		}
		return nullptr;
	}

	void SwingCompiler::AddOperator(OperatorType* op)
	{
		/// TODO : 기능 구현.
	}

	void SwingCompiler::AddFunction(std::string name, Method* func)
	{
		_functions[name] = func;
	}

	Method* SwingCompiler::GetFunction(std::string name)
	{
		return _functions[name];
	}

	void SwingCompiler::ImplementFunctionLazy(Method* method)
	{
		auto ast = new FunctionDeclAST();
		ast->_method = method;
		_src->_sourceAST.push_back(BaseAST::BasePtr(ast));
		_src->_sourceAST.shrink_to_fit();
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

	void SwingCompiler::Initialize()
	{
		/// built-in types
		_types["void"] = Void;
		_types["bool"] = Bool;
		_types["char"] = Char;
		_types["int"] = Int;
		_types["float"] = Float;
		_types["double"] = Double;

		SwingTable::_localTable.push_back(&_globalTable);
	}

	void SwingCompiler::PushIRBuilder(llvm::IRBuilder<> builder)
	{
		_builder.push_back(builder);
	}

	void SwingCompiler::PopIRBuilder()
	{
		_builder.pop_back();
	}

	llvm::Type * SwingCompiler::GetType(std::string name)
	{
		llvm::Type* type = nullptr;
		type = _types[name];
		if (type == nullptr)
		{
			_structs[name]->CreateStructType();
			type = _types[name];
			//type = _structs[name]->_type;
		}
		return type;
	}

	void SwingCompiler::BreakCurrentBlock()
	{
		if (_breakBlocks.size() == 0)
			throw Error("Can't apply break statement, not in the loop.");

		_builder.back().CreateBr(_breakBlocks.back());
		_breakBlocks.pop_back();
	}

	void SwingCompiler::CompileSource(std::string name)
	{
		Initialize();

		_src = new Source(name);
		Lexer lex;
		try
		{
			lex.LexSource(_src);
			_src->Parse();
			_src->CodeGen();
		}
		catch (LexicalError& e)
		{
			std::cout << e.what() << std::endl;
			system("pause");
			exit(-1);
		}
		catch (ParsingError& e)
		{
			std::cout << e.what() << std::endl;
			system("pause");
			exit(-1);
		}
		catch (Error& e)
		{
			std::cout << e.what() << std::endl;
			system("pause");
			exit(-1);
		}
		/*catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			system("pause");
			exit(-1);
		}*/

		std::string folder = name.substr(0, name.length() - 10);

		/// llc
		std::string cmd("llc");
		cmd += ' ';
		cmd += "-filetype=obj";
		cmd += ' ';
		cmd += folder + "Test.ll";
		cmd += ' ';
		cmd += "-o " + folder + "Test.obj";

		system(cmd.c_str());

		/// clang-cl
		cmd = "clang-cl";
		cmd += ' ';
		cmd += "-o" + folder + "Test.exe";
		cmd += ' ';
		cmd += folder + "Test.obj";
		cmd += ' ';
		cmd += "C:\\Users\\SilverJun\\Desktop\\SWING\\LibSwing\\libcmt.lib";
		cmd += ' ';
		cmd += "C:\\Users\\SilverJun\\Desktop\\SWING\\LibSwing\\libswing.o";
		cmd += ' ';
		cmd += "C:\\Users\\SilverJun\\Desktop\\SWING\\LibSwing\\io.o";
		system(cmd.c_str());

		std::cout << "Successfully Compiled." << std::endl;

		cmd = folder + "Test.exe";

		int retval = system(cmd.c_str());
		std::cout << std::endl;
		std::cout << "SwingCompiler> Program Return " << retval << std::endl << std::endl;
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
