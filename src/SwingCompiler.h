#ifndef _SWING_COMPILER_H_
#define _SWING_COMPILER_H_

#include <memory>
#include <mutex>
#include <map>
#include <unordered_map>

#include "Token.h"

#include "Lexer.h"
#include "Operator.h"

#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "Project.h"
#include "SwingTable.h"

namespace swing
{
	class FunctionDeclAST;
	class StructType;
	class ProtocolType;

	class SwingCompiler
	{
		static std::unique_ptr<SwingCompiler> _instance;
		static std::once_flag _InitInstance;

		SwingCompiler();

		SwingCompiler(const SwingCompiler& src) = delete;
		SwingCompiler& operator=(const SwingCompiler& rhs) = delete;

	public:
		llvm::LLVMContext _llvmContext;
		llvm::Module _module;
		std::vector<llvm::IRBuilder<> > _builder;

		/// compiler context
		std::unordered_map<std::string, llvm::Type*> _types;
		std::unordered_map<std::string, FunctionDeclAST*> _functions;
		std::unordered_map<std::string, StructType*> _structs;
		std::unordered_map<std::string, ProtocolType*> _protocols;

		std::multimap<int, OperatorType> _binOperators;
		std::vector<OperatorType> _preOperators;
		std::vector<OperatorType> _postOperators;

		SwingTable _globalTable;

		static SwingCompiler* GetInstance();
		~SwingCompiler();

		/// IRBuilder
		void PushIRBuilder(llvm::IRBuilder<> builder);
		void PopIRBuilder();

		/// Types.
		llvm::Type* GetType(std::string name);

		/// Operators.
		std::vector<OperatorType*> FindOps(int precedenceLevel);
		OperatorType* FindPreFixOp(std::string op);
		OperatorType* FindPostFixOp(std::string op);
		void AddOperator(OperatorType* op);

		/// Functions.
		void AddFunction(std::string name, FunctionDeclAST* func);
		FunctionDeclAST* GetFunction(std::string name);

		/// Command Line Interfaces.
		void CompileSource(std::string name);
		void CompileProject(Project* project, int optLevel, std::string outputFormat);
		void LinkProject(Project* project);
		void BuildProject(Project* project);
	};
}

#define g_SwingCompiler	swing::SwingCompiler::GetInstance()
#define g_Context	swing::SwingCompiler::GetInstance()->_llvmContext
#define g_Module	swing::SwingCompiler::GetInstance()->_module
#define g_Builder	swing::SwingCompiler::GetInstance()->_builder.back()
#define g_Table	swing::SwingCompiler::GetInstance()->_globalTable

#endif
