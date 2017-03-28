#include <iostream>
#include "SwingCompiler.h"
#include "Lexer.h"

//#include "llvm/ADT/APFloat.h"
//#include "llvm/ADT/STLExtras.h"
//#include "llvm/IR/BasicBlock.h"
//#include "llvm/IR/Constants.h"
//#include "llvm/IR/DerivedTypes.h"
//#include "llvm/IR/Function.h"
//#include "llvm/IR/IRBuilder.h"
//#include "llvm/IR/LLVMContext.h"
//#include "llvm/IR/Module.h"
//#include "llvm/IR/Type.h"
//#include "llvm/IR/Verifier.h"

int main(int argc, char* argv[])
{
	swing::SwingCompiler compiler;

	compiler.InitializeCompiler();

	compiler.CompileFile("C:\\Users\\SilverJun\\Desktop\\프로젝트\\SWING\\example\\ex01.swing");

	for (auto i = compiler.getTokenLists()->begin()->begin(); i != compiler.getTokenLists()->begin()->end(); ++i)
	{
		std::cout << static_cast<int>((*i)._id) << " " << (*i)._name << " " << (*i)._iNumber << " " << (*i)._dNumber << std::endl;
	}

	system("pause");

    return 0;
}
