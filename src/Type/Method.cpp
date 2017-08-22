#include "Method.h"
#include "StructType.h"
#include "SelfDeclAST.h"

namespace swing
{
	void Method::DeclareMethod(StructType* type)
	{
		_struct = type;
		

		std::vector<llvm::Type*> argTypes;

		for (auto& element : _args)
			argTypes.push_back(element->GetType());

		if (argTypes.size() != 0)
			_funcType = llvm::FunctionType::get(_returnType, argTypes, false);
		else
			_funcType = llvm::FunctionType::get(_returnType, false);

		_func = llvm::Function::Create(_funcType, llvm::Function::ExternalLinkage, _funcName, &g_Module);

		/// Create Self AST
		_funcBody->_astList.insert(_funcBody->_astList.begin(), SelfDeclAST::Create(this));
	}

	llvm::Value* Method::CodeGen()
	{
		if (!_func)
		{
			std::vector<llvm::Type*> argTypes;

			for (auto& element : _args)
				argTypes.push_back(element->GetType());

			if (argTypes.size() != 0)
				_funcType = llvm::FunctionType::get(_returnType, argTypes, false);
			else
				_funcType = llvm::FunctionType::get(_returnType, false);

			_func = llvm::Function::Create(_funcType, llvm::Function::ExternalLinkage, _funcName, &g_Module);
		}

		/// Table 등록.
		g_Table->AddVariable(_funcBody->_localTable);

		/// Function Body Block 삽입.
		auto blockInst = llvm::BasicBlock::Create(g_Context, "entry", _func);
		g_SwingCompiler->PushIRBuilder(llvm::IRBuilder<>(blockInst));
		g_Builder.SetInsertPoint(blockInst);

		llvm::IRBuilder<> TmpB(&_func->getEntryBlock(),
			_func->getEntryBlock().begin());
		llvm::AllocaInst* allocaInst = nullptr;

		/// 인자 등록하는 과정.
		int Idx = 0;
		for (auto& Arg : _func->args())
		{
			Arg.setName(_args[Idx]->GetName());
			
			/*if (_args[Idx]->GetName() == "self")
				continue;*/

			allocaInst = TmpB.CreateAlloca(Arg.getType(), nullptr, Arg.getName().str());

			/*if (_args[Idx]->isInout())
				Arg.addAttr(llvm::Attribute::Dereferenceable);*/

			g_Builder.CreateStore(&Arg, allocaInst);
			_args[Idx]->_value = allocaInst;
			//_args[Idx]->_type = allocaInst->getType();

			_funcBody->_localTable->_variables.push_back(_args[Idx]);
			Idx++;
		}
		
		_funcBody->_blockInst = blockInst;

		for (auto ast : _funcBody->_astList)
		{
			ast->CodeGen();
		}

		g_Table->PopLocalTable();

		llvm::raw_os_ostream os(std::cout);
		if (verifyFunction(*_func, &os))
			throw Error("Function Generate Error.");

		return _func;
	}
}
