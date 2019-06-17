#ifndef PERSER_OF_CALLS_AND_UNARY_OPERATORS_H
#define PERSER_OF_CALLS_AND_UNARY_OPERATORS_H
#include "tokens.h"
#include "dLog.h"
#include <iostream>
#include <set>

void parser_1 (std::vector <std::shared_ptr<Token> >& tokens, std::vector<std::vector<std::shared_ptr<Token> >*>& lists);

Tok openerFor(Tok closer_type);

template<typename T>
void reduceDotOpIfPossible (
	std::vector<std::shared_ptr<Token> >& tokens,
	size_t into,
	const Tok& opType,
	const std::set<Tok>& trigger)
{
	if (tokens[into]->type () == opType) { // ����� �����
		size_t lshift = into - 1, rshift = into + 1;
		while (tokens[rshift]->type () == Tok::Space) ++rshift; // ����� id-���� ������
		while (tokens[lshift]->type () == Tok::Space) { if (lshift == 0) return; --lshift; } // ����� ������, ���� id-���� �����
		if (tokens[lshift]->type () == Tok::OpenBody || tokens[lshift]->type () == Tok::OpenBodyOfLambda) return; // �����-�� �������� ����� (����� �� ������, � ����� �� ������)

		auto type = tokens[rshift]->type ();
		if (trigger.count (type) > 0) { // ���� ������ �� ������ id,
			type = tokens[lshift]->type (); // � �����, ������������� ������
			if (isCloser (type)) {
				// �� ���� �������� ���� ������
				size_t idx = findOpener (tokens, openerFor (type), type, lshift);
				// ���������� � ������
				Expr_t* e_ptr;
				// ���������� ������ �����, � �������� ����������,
				std::shared_ptr<Token> owner (e_ptr = new Expr_t ());
				e_ptr->l.reset (new std::vector<std::shared_ptr<Token> > (std::begin (tokens) + idx, std::begin (tokens) + lshift + 1));
				// �����, id, ������� ����� ������
				std::shared_ptr<Token> id = tokens[rshift];
				tokens.erase (std::begin (tokens) + idx + 1, std::begin (tokens) + rshift + 1);

				T* ptr;
				tokens[idx].reset (ptr = new T ());
				ptr->owner = owner;
				ptr->id = id;
			}
			else { // �����, ���������� � ������ 
				std::shared_ptr<Token> owner = tokens[into - lshift]; // ������� ����������� �����, � �������� ����������,
				std::shared_ptr<Token> id = tokens[into + rshift]; // � ����� id, ��������� ������
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
