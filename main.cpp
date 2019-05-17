#include <map>
#include <cstdio>
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <locale>

#include "gswstr.h"
#include "tokens.h"
#include "lexer_without_keys.h"
#include "lexer_detect_keys.h"
#include "parser_of_calls_and_unary_operators.h"
#include "parser_of_binary_operators.h"
#include "parser_of_conditional_and_loop_statements_and_lambda_defs.h"

#include "parser_nodes.h"



int main()
{
	using namespace std;
	setlocale (LC_ALL, "");
	using shp_t = std::shared_ptr<Token>;
	//SetConsoleCP (1251);
	//SetConsoleOutputCP (1251);

	loadABC ("ab.txt");
	loadKeyWords ("kw.txt");
	vector <shp_t> tokens;
	vector<vector<shp_t>*> lists;
	lexer_1 ("shit_0.txt", tokens);
	
	if (tokens.empty ()) {
		system ("pause");
		return 0;
	}
	cout << "tokens.size == " << tokens.size () << "\n";
	int co = 0;

	if (!lexer_2 (tokens)) { // adding key-words, finding unary minuses and deleting unary pluses
		system ("pause");
		return 1;
	}

	// for (auto& id : tokens)
	// 	if (id->type () == Tok::Id)
	// 		std::wcout << as<Id_t>(id)->getId() << std::endl;

	parser_1 (tokens, lists); // adding fieldCall, functionCall, arrayCall, vector definitions, dictionary definitions and unary operators
	parser_3 (lists); // adding if, if-else, if-elif, if-elif-else, while, for statements and lambda definitions
	//parser_2 (lists); // adding binary operators
	//parser_4 (tokens); // adding assignments
	//parser_5 (tokens); // adding class definitions

	//parse_to_tree(,)

	system ("pause");

	//SetConsoleCP (866);
	//SetConsoleOutputCP (866);
}
