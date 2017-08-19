#include "Source.h"
#include <iostream>
#include <fstream>
#include "SwingCompiler.h"
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/Verifier.h>
#include "SwingLibDeclAST.h"

namespace swing
{
	Source::Source(std::string fullpath) : _name(fullpath), _fullPath(fullpath)
	{
		std::ifstream file(fullpath);

		if (!file.is_open())
		{
			std::cout << "File open Error, " << fullpath << std::endl;
			exit(1);
		}

		_code = std::string(std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>());
	}

	Source::~Source()
	{
	}

	void Source::Dump()
	{
		for (auto value : _sourceAST)
			value->Dump();
	}

	void Source::Parse()
	{
		/// 자동으로 swinglib를 등록해주는 AST를 넣는다.
		_sourceAST.push_back(BaseAST::BasePtr(SwingLibDeclAST::Create()));

		/// 파싱된 토큰에 맞게 AST를 생성한다.
		for (auto iter = _tokenList.begin(); iter != _tokenList.end() && iter->_id != TokenID::Eof;)
			_sourceAST.push_back(BaseAST::Create(iter));
	}

	void Source::CodeGen()
	{
		for (int i = 0; i < _sourceAST.size(); ++i)
			_sourceAST[i]->CodeGen();

		std::string folder = _name.substr(0, _name.length() - 10);

		llvm::raw_os_ostream os(std::cout);
		verifyModule(g_Module, &os);

		std::error_code EC;
		std::string file = folder + "Test.ll";
		
		llvm::raw_fd_ostream OS(file, EC, llvm::sys::fs::F_None);
		g_SwingCompiler->_module.print(OS, nullptr);
		OS.flush();
	}
}
