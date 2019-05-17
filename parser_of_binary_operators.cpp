#include "parser_of_binary_operators.h"

using shp_t = std::shared_ptr<Token>;

void addParenthesisBinOps (
	std::vector <shp_t>& tokens,
	std::vector<std::set<Tok>>& ops,
	std::vector<std::vector<shp_t>*>& lists
);

void rmSenselessParenthesis (std::vector<shp_t>& tokens);

void reduceParenthesisWithBinOps (
	std::vector <shp_t>& tokens,
	std::set <Tok>& binops,
	std::vector<std::vector<shp_t>*>& lists
);


void parser_2 (std::vector<std::vector<shp_t>*>& lists) // сокращает бинарные операторы lists
{
	std::vector<std::vector<shp_t>*> lists2;
	std::vector<std::set<Tok>> priority { // приоритет бинарных операторов
		{Tok::Power},
		{Tok::Multiply, Tok::Devide, Tok::Mod},
		{Tok::Plus, Tok::Minus},
		{Tok::Less, Tok::LessOrEqual, Tok::More, Tok::MoreOrEqual},
		{Tok::Equal, Tok::NotEqual}
	};
	std::set<Tok> binops;
	for (auto& it : priority) for (auto& jt : it) binops.insert (jt);
	for (auto& it : lists) addParenthesisBinOps (*it, priority, lists2);
	lists.clear ();
	for (auto& it : lists2) rmSenselessParenthesis (*it);
	for (auto& it : lists2) reduceParenthesisWithBinOps (*it, binops, lists);
}

void rmSenselessParenthesis (std::vector<shp_t>& tokens)
{
	std::vector<std::pair<unsigned, unsigned>> opn;
	for (unsigned idx = 0; idx < tokens.size (); ++idx) {
		auto type = tokens[idx]->type ();
		if (type == Tok::Space) continue;
		if (type == Tok::OpenParenthesis) {
			opn.push_back ({idx, 0}); // запомнили
			continue;
		}
		if (type == Tok::CloseParenthesis) {
			if (opn.back ().second == 1) { // раскрыли не нужные скобки
				tokens.erase (std::begin (tokens) + idx);
				tokens.erase (std::begin (tokens) + opn.back ().first);
				--idx;
			}
			opn.pop_back ();
			for (auto& lt : opn) ++(lt.second);
			continue;
		}
		if (!opn.empty()) ++(opn.back ().second);
	}
}

void reduceBasicParenthesisWithBinOps (
	unsigned idx,
	std::vector <shp_t>& tokens,
	std::vector<unsigned>& binopPos,
	std::vector<unsigned>& closer,
	std::vector<std::vector<shp_t>*>& lists)
{
	// [idx]->'('  [binopPos.back () - shift]->'+'  [closer.back() - shift]->')'
	Expr_t *left, *right;
	binop_t *p;
	shp_t binop (p = new binop_t ());
	p -> left = shp_t (left = new Expr_t ());
	p -> right = shp_t (right = new Expr_t ());
	p -> opType = tokens[binopPos.back ()] -> type ();
	
	// [idx+1 : binopPos.back()]			<-	left
	// [binopPos.back()+1 : closer.back()]	<-	right
	const auto from1 = idx + 1, to1 = binopPos.back ();
	auto from2 = to1 + 1;
	left -> l.reset (new std::vector<shp_t> (std::begin (tokens) + from1, std::begin (tokens) + to1));
	right -> l.reset (new std::vector<shp_t> (std::begin (tokens) + from2, std::begin (tokens) + closer.back ()));
	lists.push_back (left -> l.get ());
	lists.push_back (right -> l.get ());

	
	tokens[idx] = binop; // вместо открывающей скобки вставили бинарный оператор
	tokens.erase (std::begin (tokens) + idx+1, std::begin (tokens) + closer.back ()+1); // всё остальное удалили
}


void reduceParenthesisWithBinOps (
	std::vector <shp_t>& tokens,
	std::set <Tok>& binops,
	std::vector<std::vector<shp_t>*>& lists)
{
	std::vector<unsigned> binopPos;
	std::vector<unsigned> closer;
	

	lists.push_back(&(tokens));
	// -<-----<----<--
	// 0:a   1:+   2:b
	// ищем скобки и операторы и запоминаем их в стек
	// min_size=3 , start=size-1
	if (tokens.size() > 2) {
		
		for (unsigned idx = tokens.size () - 1; idx > 0; --idx) {
			
			const auto type = tokens[idx] -> type ();

			if (type == Tok::CloseParenthesis) { // наткнулись на закрывающую скобку
				if (idx == 0) break; // если это -- первый символ, то это не имеет смысла
				closer.push_back (idx); // иначе, запомнили, её положение
				continue;
			}

			if (!closer.empty ()) { // // если мы глубоко

				if (binops.count (type)) { // и наткнулись на бинарный опиратор

					if (idx == 0) break; // если это -- первый символ, то это не имеет смысла
					binopPos.push_back (idx); // иначе, запомнили, где он нам встретился
					continue;
				}

				if (type == Tok::OpenParenthesis) { // и наткнулись на открывающую скобку, то

					reduceBasicParenthesisWithBinOps (idx, tokens, binopPos, closer, lists);
					// (:0 a:1 +:2 b:3 +:4 (:5 c:6 +:7 d:8 ):9 ):10 ===-----> idx = 5, closer.back1() = 9, closer.back0() = 10
					// (:0 a:1 +:2 b:3 +:4 binop:5 ):6 ===-----> closer.back0() = 10, а должно быть closer.back0() = 6, т.е. shift = 4
					// т.е. shift := closer.back() - idx
					unsigned shift = closer.back() - idx;
					for (auto& jt : closer) jt -= shift;
					for (auto& jt : binopPos) jt -= shift;
					closer.pop_back ();
					binopPos.pop_back ();
				}
			}
			if (idx == 0) break;
		}
		
		// Сокращение последней скобки с бинарным оператором
		if (tokens.size () > 2) {
			if (tokens[0] -> type () == Tok::OpenParenthesis && binopPos.size() == closer.size () == 1) {
				reduceBasicParenthesisWithBinOps (0, tokens, binopPos, closer, lists);
			}
		}
		closer.clear();
		binopPos.clear();
	}
}

bool inParenthesis (Tok type, unsigned& depth)
{
	if (type == Tok::CloseParenthesis) ++depth;
	if (type == Tok::OpenParenthesis) --depth;
	return depth != 0;
}

void addParenthesisBinOps (
	std::vector <shp_t>& tokens,
	std::vector<std::set<Tok>>& opss,
	std::vector<std::vector<shp_t>*>& lists)
{
	for (auto& ops : opss) {
		
		for (unsigned idx = 1; idx < tokens.size() - 1; ++idx) {
			
			const auto type = tokens[idx]->type();
			if (ops.count (type) != 0) { // '(' 'a' ')' [idx]->'+' '(' 'b' ')'

				unsigned depth = 0, jdx = idx-1, kdx = idx+1, ldx = jdx, mdx = kdx;
				// '(' 'a' [jdx/ldx]->')' [idx]->'+' [kdx/mdx]->'(' 'b' ')'

				bool first_time = true;
				
				for (;jdx > 0; --jdx) {
					const auto type = tokens[jdx]->type();
					if (type == Tok::Space) continue;
					else if (first_time) { ldx = jdx; first_time = false; } // ldx в самое начало левой скобки
					if (!inParenthesis(type, depth)) break;
				}
				depth = 0;
				first_time = true;
				
				for (;kdx > 0; ++kdx) {
					const auto type = tokens[kdx]->type();
					if (type == Tok::Space) continue;
					else if (first_time) { mdx = kdx; first_time = false; } // mdx в самое начало правой скобки
					if (!inParenthesis (type, depth)) break;
				}

				// [jdx]->'(' 'a' [ldx]->')' [idx]->'+' [mdx]->'(' 'b' [kdx]->')'
				tokens.insert (std::begin (tokens) + jdx, shp_t (new OpenParenthesis_t ()));
				++kdx;
				++idx;

				if (tokens.size () == kdx + 1) {
					tokens.push_back (shp_t (new CloseParenthesis_t ()));
				} else {
					tokens.insert (std::begin (tokens) + kdx + 1, shp_t (new CloseParenthesis_t ()));
				}
			}
		}
	}
	lists.push_back (&tokens);
}
