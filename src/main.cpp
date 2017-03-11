#include <iostream>
#include "Lexer.h"
#include <regex>

int main(int argc, char* argv[])
{
	swing::Lexer lex;
	lex.Initialize();
	lex.LoadSourceFile("C:/Users/jange/Desktop/SWING/example/ex01.swing");
	lex.GenerateTokenList();
	auto lists = lex.GetTokenList();
	std::cout << std::endl;
	for (auto i = lists.begin(); i != lists.end(); i++)
	{
		std::cout << (*i)._name << " " << (*i)._number << std::endl;
	}

	/*std::string line("aasas \"asdfasdf asdfasdf\" asssas");
	std::regex reg("\"(.*)\"");
	std::smatch sm;

	while (regex_search(line, sm, reg))
	{
		std::string str = sm.str();

		std::cout << str << " ";

		line = sm.suffix();
	}*/

	system("pause");

    return 0;
}
