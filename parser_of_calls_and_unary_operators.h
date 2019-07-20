#ifndef PERSER_OF_CALLS_AND_UNARY_OPERATORS_H
#define PERSER_OF_CALLS_AND_UNARY_OPERATORS_H
#include "tokens.h"
#include "dLog.h"
#include <iostream>
#include <set>

void parser_1 (std::vector <std::shared_ptr<Token> >& tokens, std::vector<std::vector<std::shared_ptr<Token> >*>& lists);
Tok openerFor(Tok type);
size_t findOpener(std::vector<std::shared_ptr<Token> >&, Tok, Tok, size_t);

template<typename T>
void reduceDotOpIfPossible (
	std::vector<std::shared_ptr<Token> >& tokens,
	size_t into,
	const Tok& opType,
	const std::set<Tok>& trigger)
{
	if (tokens[into]->type () == opType) { // нашли точку
		size_t lshift = into - 1, rshift = into + 1;
		while (tokens[rshift]->type () == Tok::Space) ++rshift; // нашли id-шник справа
		while (tokens[lshift]->type () == Tok::Space) { if (lshift == 0) return; --lshift; } // нашли скобку, либо id-шник слева
		if (tokens[lshift]->type () == Tok::OpenBody || tokens[lshift]->type () == Tok::OpenBodyOfLambda) return; // какая-то странная точка (может из класса, а может из лямбды)

		Tok type = tokens[rshift]->type ();
		if (trigger.count (type) > 0) { // если справа от скобки id,
			type = tokens[lshift]->type (); // а слева, закрывающаяся скобка
			if (isCloser (type)) {
				// то ищем открытие этой скобки
				size_t idx = findOpener (tokens, openerFor (type), type, lshift);
				// запоминаем в буфера
				Expr_t* e_ptr;
				// содержимое скобок слева, в качестве вызвавщего,
				std::shared_ptr<Token> owner (e_ptr = new Expr_t ());
				e_ptr->l.reset (new std::vector<std::shared_ptr<Token> > (std::begin (tokens) + idx, std::begin (tokens) + lshift + 1));
				// затем, id, который нашли справа
				std::shared_ptr<Token> id = tokens[rshift];
				tokens.erase (std::begin (tokens) + idx + 1, std::begin (tokens) + rshift + 1);

				T* ptr;
				tokens[idx].reset (ptr = new T ());
				ptr->owner = owner;
				ptr->id = id;
			}
			else { // иначе, запоминаем в буфера 
				std::shared_ptr<Token> owner = tokens[into - lshift]; // первого попавшегося слева, в качестве вызвавщего,
				std::shared_ptr<Token> id = tokens[into + rshift]; // а затем id, найденный справа
				tokens.erase (std::begin (tokens) + into - lshift + 1, std::begin (tokens) + into + rshift + 1);
				T* ptr;
				tokens[into - lshift].reset (ptr = new T ());
				ptr->owner = owner;
				ptr->id = id;
			}
		}
	}
}

#endif // PERSER_OF_CALLS_AND_UNARY_OPERATORS_H
