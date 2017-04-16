#ifndef _SWING_COMPILER_H_
#define _SWING_COMPILER_H_

#include <memory>
#include <mutex>

#include "Lexer.h"
#include "Operator.h"
#include "Token.h"

#include "Type.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include <unordered_map>
#include "Project.h"


namespace swing
{
	class SwingCompiler
	{
		static std::unique_ptr<SwingCompiler> _instance;
		static std::once_flag _InitInstance;

		SwingCompiler();

		SwingCompiler(const SwingCompiler& src) = delete;
		SwingCompiler& operator=(const SwingCompiler& rhs) = delete;

	public:
		Lexer* _lexer = nullptr;
		Project* _project = nullptr;

		llvm::LLVMContext _llvmContext;
		llvm::Module _module;
		llvm::IRBuilder<> _builder;

		std::vector<Keyword> _keywordList;
		std::vector<Keyword> _operatorList;
		std::list<TokenList> _tokenLists;

		std::unordered_map<std::string, llvm::Type*> _types;
		std::unordered_map<std::string, llvm::Value*> _symbolTable;

		static SwingCompiler& GetInstance()
		{
			std::call_once(_InitInstance, []()
			{
				_instance.reset(new SwingCompiler);
			});

			return *_instance.get();
		}
		~SwingCompiler()
		{
			delete _lexer;
		}

		void SetProject(Project* project);
		void CompileProject();
		void CompileFile(std::string file);

		std::string GenerateNameMangling(llvm::Function* func);
	};

}

#define g_SwingCompiler	swing::SwingCompiler::GetInstance()

#endif
