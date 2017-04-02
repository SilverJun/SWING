#ifndef _SWING_COMPILER_H_
#define _SWING_COMPILER_H_

#include "Lexer.h"
#include "Operator.h"
#include "Token.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"

namespace swing
{
	class SwingCompiler
	{
		std::vector<Keyword> _keywordList;
		std::vector<Keyword> _operatorList;
		std::list<TokenList> _tokenLists;

		Lexer* _lexer;

		//ProjectManager

		static llvm::LLVMContext _llvmContext;
		static llvm::Module _module;
		static llvm::IRBuilder<> _builder;

	public:
		static llvm::LLVMContext& GetLLVMContext()
		{
			return _llvmContext;
		}
		static llvm::Module& GetModule()
		{
			return _module;
		}
		static llvm::IRBuilder<>& GetBuilder()
		{
			return _builder;
		}

		SwingCompiler()
		{
			_tokenLists.push_back(TokenList());
			_lexer = new Lexer(&_tokenLists.back(), &_keywordList, &_operatorList);
		}

		~SwingCompiler()
		{
			delete _lexer;
		}

		void InitializeCompiler();
		
		//void SetProject(Project* project);
		void CompileProject();
		void CompileFile(std::string file);

		std::list<TokenList>* getTokenLists()
		{
			return &_tokenLists;
		}

	};
}

#endif
