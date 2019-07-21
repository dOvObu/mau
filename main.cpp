#include "main.h"



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


	printf ("tokens.size == %zu\n", tokens.size ());
	if (tokens.empty ()) {
		#ifndef __unix__
		system ("pause");
		#endif
		return 0;
	}
	
	//printTokens ("\n\n\n===----- after lexer_1 -----===\n\n", tokens, "\n\n\n");
	//> добавление key-слов
	//> поиск унарных минусов
	//> удаление унарных плюсов
	//> установка границ типов
	//> поиск скобок типа лямбд \() и типа шаблонов !()
	try {
		if (!lexer_2 (tokens)) {
			#ifndef __unix__
			system ("pause");
			#endif
			return 1;
		}
	}
	catch (std::string str) {
		puts (str.c_str ());
		#ifndef __unix__ 
		system ("pause");
		#endif
		return 1;
	}


	printTokens ("\n\n\n===----- after lexer_2 -----===\n\n", tokens, "\n\n\n");

	// Добавление fieldCall obj.kek, functionCall, arrayCall, vectorDef +(1, 2, 3)+,
	// dictionaryDef +("one" : 10, "two" : 20)+ и унарных операторов
	parser_1 (tokens, lists);
	std::remove_if (std::begin (lists), std::end (lists), [](auto* t) {return t->empty (); });

	puts ("\n\n\n===----- after parser_1 -----===");
	//for (auto& it : lists) printTokens ("\n", *it, "\n");
	puts ("\n");

	// Добавление if, if-else, if-elif, if-elif-else, while, for statements
	// and lambda definitions
	parser_3 (lists);
	std::remove_if (std::begin (lists), std::end (lists), [](auto* t) {return t->empty (); });


	puts ("\n\n\n===----- after parser_3 -----===");
	for (auto& it : lists) printTokens ("\n", *it, "\n");
	puts ("\n");

	showTokens (*(lists[0]));


	// Добавление бинарных операторов
	////                                      parser_2 (lists);
	
	//parser_4 (tokens); // adding assignments
	//parser_5 (tokens); // adding struct and impl definitions
	//parser_6 (tokens); // adding templateDef
	//analysis_1 (tokens); // вывод типов и генерация функций на основе шаблонов

	//parse_to_tree(,)
	#ifndef __unix__
	system ("pause");
	#endif\

	//SetConsoleCP (866);
	//SetConsoleOutputCP (866);
}
