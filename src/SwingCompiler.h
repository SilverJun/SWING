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


namespace swing
{
	class SwingCompiler
	{
		static std::unique_ptr<SwingCompiler> _instance;
		static std::once_flag _InitInstance;

		std::vector<Keyword> _keywordList;
		std::vector<Keyword> _operatorList;
		std::list<TokenList> _tokenLists;
		std::vector<Type> _types;

		Lexer* _lexer;

		//ProjectManager

		llvm::LLVMContext _llvmContext;
		llvm::Module _module;
		llvm::IRBuilder<> _builder;

		SwingCompiler();

		SwingCompiler(const SwingCompiler& src) = delete;
		SwingCompiler& operator=(const SwingCompiler& rhs) = delete;

	public:
		static SwingCompiler& GetInstance()
		{
			std::call_once(_InitInstance, []()
			{
				_instance.reset(new SwingCompiler);
			});

			return *_instance.get();
		}

		llvm::LLVMContext& GetLLVMContext()
		{
			return _llvmContext;
		}
		llvm::Module& GetModule()
		{
			return _module;
		}
		llvm::IRBuilder<>& GetBuilder()
		{
			return _builder;
		}
		//void SetProject(Project* project);
		void CompileProject();
		void CompileFile(std::string file);

		std::list<TokenList>* getTokenLists()
		{
			return &_tokenLists;
		}
		~SwingCompiler()
		{
			delete _lexer;
		}
	};

}

#define g_SwingCompiler	swing::SwingCompiler::GetInstance()

#endif
