#include <iostream>
#include "SwingCompiler.h"
#include "Lexer.h"
#include "Project.h"


int main(int argc, char* argv[])
{
	/*swing::SwingCompiler compiler;

	compiler.InitializeCompiler();

	compiler.CompileFile("../../example/ex01.swing");

	for (auto i = compiler.getTokenLists()->begin()->begin(); i != compiler.getTokenLists()->begin()->end(); ++i)
	{
		std::cout << static_cast<int>((*i)._id) << "\t" << (*i)._name << "\t" << (*i)._iNumber << "\t" << (*i)._dNumber << std::endl;
	}*/

	swing::Project("Test","C:/Users/smart/Desktop/test");


	system("pause");

    return 0;
}
