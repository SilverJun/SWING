#include <iostream>
#include "Lexer.h"

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

int main(int argc, char* argv[])
{
	/*swing::Lexer lex;
	lex.Initialize();
	lex.LoadSourceFile("C:/Users/jange/Desktop/SWING/example/ex01.swing");
	lex.GenerateTokenList();
	auto lists = lex.GetTokenList();
	std::cout << std::endl;
	for (auto i = lists.begin(); i != lists.end(); i++)
	{
		std::cout << (*i)._name << " " << (*i)._number << std::endl;
	}*/

	/*std::string line("aasas \"asdfasdf asdfasdf\" asssas");
	std::regex reg("\"(.*)\"");
	std::smatch sm;

	while (regex_search(line, sm, reg))
	{
		std::string str = sm.str();

		std::cout << str << " ";

		line = sm.suffix();
	}*/

	//std::cout << std::stoi("fe10", nullptr, 16) << std::endl;

	system("pause");

    return 0;
}
