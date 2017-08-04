#ifndef _SWING_STRING_TYPE_H_
#define _SWING_STRING_TYPE_H_

#include "SwingCompiler.h"
#include "StructType.h"
#include <iostream>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_os_ostream.h>

namespace swing
{
	class StringType : StructType
	{
		std::string _str;

	public:
		StringType(std::string& str) : StructType("String",
		{ llvm::VectorType::get(g_SwingCompiler->_types["char"], str.length()) },
		{
			{ "length", llvm::make_unique<llvm::Function>(llvm::Function::Create(llvm::FunctionType::get(g_SwingCompiler->_types["int"], false), llvm::GlobalValue::LinkOnceAnyLinkage, "length", &g_Module)) }
		}), _str(str)
		{
			/// Built-In member methods implementation

			/// func length() -> Int
			llvm::BasicBlock* funcBody = llvm::BasicBlock::Create(g_Context, "entry", _method["length"].get());
			g_Builder.SetInsertPoint(funcBody);
			g_Builder.CreateRet(llvm::ConstantInt::get(g_Context, llvm::APInt(32, _str.length(), true)));
			///

			llvm::raw_os_ostream ros(std::cout);
			std::for_each(_method.begin(), _method.end(), [&ros](std::pair<std::string, llvm::Function*> method)
			{
				if (verifyFunction(*method.second, &ros))
				{
					throw Error("Verify Function Error, " + method.first);
				}
			});
		}
		virtual ~StringType() {}
	};
}

#endif
