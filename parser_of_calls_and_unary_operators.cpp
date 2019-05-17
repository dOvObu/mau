#include "parser_of_calls_and_unary_operators.h"

using shp_t = std::shared_ptr<Token>;

template <typename T>
void reduceCalls(
		std::vector<shp_t>& tokens,
		const Tok& opner,
		const Tok& clser,
		const Tok& separ,
		const Tok& ignor,
		const std::set<Tok>& trigger,
		std::vector<std::vector<shp_t>*>& lists
);

void reduceDotOpIfPossible (
		std::vector<shp_t>& tokens,
		unsigned into,
		const Tok& opType,
		const std::set<Tok>& trigger
);

void reduceArrays (
		std::vector<shp_t>& tokens,
		const Tok& opner,
		//const Tok& clser,
		const Tok& separ,
		//const Tok& ignor,
		std::vector<std::vector<shp_t>*>& lists
);

void reduceUnOps (
		std::vector<shp_t>& tokens,
		std::vector<std::vector<shp_t>*>& lists
);

// Переливаем из пустого в порожнее
void parser_1(std::vector <shp_t>& tokens, std::vector<std::vector<shp_t>*>& lists)
{
	if (tokens.size () > 2) // минимум [1]->'id' [2]->'.' [3]->'id'
		for (unsigned idx = 1; idx < tokens.size() - 2; ++idx)
			reduceDotOpIfPossible (tokens, idx, Tok::Dot, {Tok::Id});
	// теперь, нигде (в expr-ах) нет неосмысленных точек

	std::vector<std::vector<shp_t>*> lists2;
	reduceCalls<Call_t> (tokens, Tok::OpenParenthesis, Tok::CloseParenthesis, Tok::Comma, Tok::Space, {Tok::Call, Tok::ArrayCall, Tok::FieldCall}, lists2);
	// теперь, в lists2 находятся ссылки на списки токенов, которые не содержат неосмысленных вызовов функций

	for (auto& it : lists2)
		reduceArrays (*it, Tok::OpenParenthesis, Tok::Comma, lists);
	// теперь, в lists нет неосмысленных массивов

	lists2.clear();
	for (auto& it : lists)
		reduceCalls<ArrayCall_t> (*it, Tok::OpenBrackets, Tok::CloseBrackets, Tok::Colon, Tok::Space, {Tok::Call, Tok::ArrayCall, Tok::ArrayDef, Tok::FieldCall}, lists2);
	// теперь, в lists2 нет неосмысленных вызовов массивов


	lists.clear();
	for (auto& it : lists2) reduceUnOps (*it, lists);
	// теперь, в lists нет неосмысленных унарных операторов и скобок в выражениях

}//-----------------------------------------------------------------//

inline bool isOpener (Tok type){return type == Tok::OpenParenthesis || type == Tok::OpenBrackets || type == Tok::OpenCurlyBrackets;}
inline bool isCloser (Tok type){return type == Tok::CloseParenthesis || type == Tok::CloseBrackets || type == Tok::CloseCurlyBrackets;}

unsigned findCloser (std::vector<shp_t>& tokens, Tok opn, Tok cls, unsigned jdx) {
	const auto size = tokens.size();
	unsigned depth = 1, kdx = jdx + 1;
	for(;depth != 0 && kdx < size; ++kdx) {
		const auto type = tokens[kdx]->type();
		if (type == opn) ++depth;
		else if (type == cls) --depth;
	}
	return kdx;
}
unsigned findCloser (std::vector<shp_t>& tokens, unsigned jdx) {
	const auto size = tokens.size();
	unsigned depth = 1, kdx = jdx + 1;
	for(;depth != 0 && kdx < size; ++kdx) {
		const auto type = tokens[kdx]->type();
		if (isOpener (type)) ++depth;
		else if (isCloser (type)) --depth;
	}
	return kdx;
}
unsigned findOpener (std::vector<shp_t>& tokens, Tok opn, Tok cls, unsigned jdx) {
	unsigned depth = 1, kdx = jdx - 1;
	while (depth != 0) {
		const auto type = tokens[kdx]->type();
		if (type == cls) ++depth;
		else if (type == opn) --depth;
		if (kdx == 0) break;
		--kdx;
	}
	return kdx;
}
unsigned findOpener (std::vector<shp_t>& tokens, unsigned jdx) {
	unsigned depth = 1, kdx = jdx - 1;
	while (depth != 0) {
		const auto type = tokens[kdx]->type();
		if (isCloser (type)) ++depth;
		else if (isOpener (type)) --depth;
		if (kdx == 0) break;
		--kdx;
	}
	return kdx;
}

Tok openerFor(Tok type) {
	switch (type) {
		case Tok::CloseBrackets: return Tok::OpenBrackets;
		case Tok::CloseParenthesis: return Tok::OpenParenthesis;
		case Tok::CloseCurlyBrackets: return Tok::OpenCurlyBrackets;
		default: return Tok::Dot;
	}
}


template <typename T>
void moveBracketsToUnOp (
		std::vector<shp_t>& tokens,
		unsigned idx,
		unsigned jdx,
		unsigned kdx,
		std::vector<std::vector<shp_t>*>& lists)
{
	Expr_t* p;
	as<T>(tokens[idx])->right = shp_t(p = new Expr_t());
	p->l.reset (new std::vector<shp_t>(std::begin(tokens) + jdx + 1, std::begin(tokens) + kdx));
	tokens.erase (std::begin(tokens) + jdx, std::begin(tokens) + kdx + 1);
	lists.push_back(p->l.get ());
}

template<typename T>
bool reduceBracketsToUnOp (
		std::vector<shp_t>& tokens,
		unsigned idx,
		unsigned jdx,
		std::vector<std::vector<shp_t>*>& lists)
{
	bool done = false;
	if (tokens[jdx]->type()==Tok::OpenParenthesis) {
		unsigned kdx = findCloser (tokens, Tok::OpenParenthesis, Tok::CloseParenthesis, jdx);
		moveBracketsToUnOp<T>(tokens, idx, jdx, kdx, lists);
		done = true;
	} else if (tokens[jdx]->type()==Tok::OpenCurlyBrackets) {
		unsigned kdx = findCloser (tokens, Tok::OpenCurlyBrackets, Tok::CloseCurlyBrackets, jdx);
		moveBracketsToUnOp<T>(tokens, idx, jdx, kdx, lists);
		done = true;
	} else if (tokens[jdx]->type()==Tok::OpenBrackets) {
		unsigned kdx = findCloser (tokens, Tok::OpenBrackets, Tok::CloseBrackets, jdx);
		moveBracketsToUnOp<T>(tokens, idx, jdx, kdx, lists);
		done = true;
	}
	return done;
}

template <typename T>
bool tryReduceToUnOp (
		Tok type,
		unsigned idx,
		std::vector<shp_t>& tokens,
		std::vector<std::vector<shp_t>*>& lists)
{
	bool res = false;
	if (tokens[idx]->type() == type) {
		unsigned jdx = idx + 1;
		const auto size = tokens.size() - 1;
		while (tokens[jdx]->type() != Tok::Space && jdx < size) ++jdx;
		if (!reduceBracketsToUnOp<T>(tokens, idx, jdx, lists)) {
			as<T>(tokens[idx])->right = tokens[jdx];
			tokens.erase(std::begin(tokens) + jdx);
		}
		res = true;
	}
	return res;
}

void reduceUnOps (
		std::vector<shp_t>& tokens,
		std::vector<std::vector<shp_t>*>& lists)
{
	lists.push_back(&(tokens));
	for (unsigned idx = 0; idx < tokens.size(); ++idx) {
		tryReduceToUnOp<UnMinus_t> (Tok::UnMinus, idx, tokens, lists)
		|| tryReduceToUnOp<Decrement_t> (Tok::Decrement, idx, tokens, lists)
		|| tryReduceToUnOp<Increment_t> (Tok::Increment, idx, tokens, lists);
	}
}

void reduceArrays (
		std::vector<shp_t>& tokens,
		const Tok& opner,
		//const Tok& clser,
		const Tok& separ,
		//const Tok& ignor,
		std::vector<std::vector<shp_t>*>& lists)
{
	lists.push_back(&(tokens));

	if (tokens.size() > 1) // минимум [1]->'(' ')'<-[2]
	{
		unsigned idx = static_cast<unsigned> (tokens.size () - 1); // если пятимся, то собираем все вложенные вызовы
		while (true)
		{
			auto type = tokens[idx] -> type ();
			if (type == opner) {

				//				текущий тип данных
				enum class val_t {unknown, array, dict} val_type{val_t::unknown};

				std::shared_ptr<ArrayDef_t> arr (new ArrayDef_t());
				std::vector<shp_t> keys;

				unsigned depth = 0;
				unsigned jdx = idx, kdx = idx;
				//bool tr = false;

				for (; jdx < tokens.size(); ++jdx)
				{
					auto type = tokens[jdx] -> type ();

					// подсчёт
					if (isOpener (type)) ++depth;
					else if (isCloser (type)) --depth;
					// текущей глубины

					else if (depth == 1) { // если глубина подходящая, подбираем тип под семантику
						// если тип
						//					 -- ещё не известен
						if (val_type == val_t::unknown) {
							if (type == separ) val_type = val_t::array; // если встретилась запятая, то это -- массив
							if (type == Tok::Colon) { // если встретилось двоеточие, то возможно это -- хэш таблица
								bool is_dict = false;
								for (unsigned ldx = jdx-1; ldx > idx; --ldx) {
									const auto type = tokens[ldx]->type();
									if (type != Tok::Space && type != Tok::EndString) {
										is_dict = type == Tok::String;
										break;
									}
								}
								if (!is_dict) break;
								val_type = val_t::dict;
							}
						}
						// если тип
						//					 -- массив
						if (val_type == val_t::array) {
							if (type == separ) { // [kdx]->'(' [jdx]->',' ...
								arr->cells.push_back(Expr_t());
								arr->cells.back ().l.reset (new std::vector<shp_t>(std::begin(tokens)+kdx+1, std::begin(tokens)+jdx));
								kdx = jdx;
							}
							// если тип
							//				  -- хэш таблица
						} else if (val_type == val_t::dict) {
							if (type == Tok::Colon){ // [kdx]->'(' [jdx]->':' ...
								bool allright = true;
								unsigned ldx = jdx-1;
								for (;ldx > idx; --ldx) {
									const auto type = tokens[ldx]->type();
									if (type != Tok::Space && type != Tok::EndString) {
										allright = type == Tok::String;
										break;
									}
								}
								if (!allright) {
									val_type = val_t::unknown;
									break;
								}
								keys.push_back (tokens[ldx]);
								kdx = jdx;
							} else if (type == separ) { // [kdx]->':' [jdx]->',' ...
								arr->cells.push_back(Expr_t());
								arr->cells.back().l.reset (new std::vector<shp_t>(std::begin(tokens)+kdx+1, std::begin(tokens)+jdx));
							}
						}
					}
					if (depth == 0) { // [kdx]->',' [jdx]->')'
						arr->cells.push_back(Expr_t());
						arr->cells.back().l.reset (new std::vector<shp_t>(std::begin(tokens)+kdx+1, std::begin(tokens)+jdx));
						break;
					}
				}

				if (val_type != val_t::unknown){
					if (val_type == val_t::array) {
						if (arr->cells.size() > 1) { // это реально массив [idx]->'('...')'<-[jdx]
							tokens.erase (std::begin(tokens)+idx+1, std::begin(tokens) + jdx + 1);
							tokens[idx] = arr;
							for (auto&it : arr->cells)
								lists.push_back (it.l.get ());
						}
					} else { // это реально библиотека [idx]->'('...')'<-[jdx]
						if (keys.size() == arr->cells.size()) {
							tokens.erase (std::begin(tokens)+idx+1, std::begin(tokens) + jdx + 1);
							FieldDef_t* p;
							tokens[idx] = shp_t(p = new FieldDef_t());
							for (unsigned jdx = 0; jdx < keys.size(); ++jdx)
								p->cells[as<Id_t>(keys[jdx])] = arr->cells[jdx];
							for (auto&it : p->cells)
								lists.push_back (it.second.l.get ());
						}
					}
				}
			}
			if (idx == 0) break;
			--idx;
		}
	}
}

void reduceDotOpIfPossible (
		std::vector<shp_t>& tokens,
		unsigned into,
		const Tok& opType,
		const std::set<Tok>& trigger)
{
	if (tokens[into] -> type () == opType) { // нашли точку
		unsigned lshift = into-1, rshift = into+1;
		while (tokens[rshift]->type() == Tok::Space) ++rshift; // нашли id-шник справа
		while (tokens[lshift]->type() == Tok::Space) {if (lshift == 0) return; --lshift;} // нашли скобку, либо id-шник слева

		auto type = tokens[rshift] -> type ();
		if (trigger.count (type) > 0) { // если справа от скобки id,
			type = tokens[lshift] -> type (); // а слева, закрывающаяся скобка
			if (isCloser (type)) {
				// то ищем открытие этой скобки
				unsigned idx = findOpener(tokens, openerFor (type), type, lshift);
				// запоминаем в буфера
				Expr_t* e_ptr;
				// содержимое скобок слева, в качестве вызвавщего,
				shp_t owner (e_ptr = new Expr_t ());
				e_ptr->l.reset (new std::vector<shp_t> (std::begin (tokens) + idx, std::begin (tokens) + lshift + 1));
				// затем, id, который нашли справа
				shp_t id = tokens[rshift];
				tokens.erase (std::begin(tokens) + idx + 1, std::begin(tokens) + rshift + 1);
				

				FieldCall_t* ptr;
				tokens[idx] = shp_t (ptr = new FieldCall_t());
				ptr->owner = owner;
				ptr->id = id;
			} else { // иначе, запоминаем в буфера 
				shp_t owner = tokens[into - lshift]; // первого попавшегося слева, в качестве вызвавщего,
				shp_t id = tokens[into +  rshift]; // а затем id, найденный справа
				tokens.erase (std::begin(tokens) + into - lshift + 1, std::begin(tokens) + into + rshift + 1);
				FieldCall_t* ptr;
				tokens[into-lshift] = shp_t(ptr = new FieldCall_t());
				ptr->owner = owner;
				ptr->id = id;
			}
		}
	}
}

template <typename T>
void reduceCalls(
		std::vector<shp_t>& tokens,
		const Tok& opner,
		const Tok& clser,
		const Tok& separ,
		const Tok& ignor,
		const std::set<Tok>& trigger,
		std::vector<std::vector<shp_t>*>& lists)
{
	lists.push_back(&(tokens));
	if (tokens.size() > 2) // минимум [1]->'id' [2]->'(' ')'<-[3]
	{
		unsigned idx = static_cast<unsigned> (tokens.size () - 2); // если пятимся, то собираем все вложенные вызовы
		while (true)
		{
			auto type = tokens[idx + 1] -> type ();
			if (type == opner) {

				auto jdx = idx;

				while (true)
				{
					auto type = tokens[jdx] -> type ();
					if (type != ignor) {

						if (type == Tok::Id) { // есть вызов функции [idx+1]->(...)<-[?]
							auto kdx = findCloser (tokens, opner, clser, idx + 1);
							// [jdx]->id [idx+1]->(...)<-[kdx]
							std::vector<shp_t> toks (std::begin (tokens) + idx + 2, std::begin (tokens) + kdx - 1);
							tokens.erase (std::begin (tokens) + idx + 1, std::begin (tokens) + kdx + 1);
							shp_t id = tokens[jdx];
							T* ptr;
							tokens[jdx] = shp_t (ptr = new T ());
							ptr->id = as<Id_t>(id);
							auto& args = as<T>(tokens[jdx])->args;
							unsigned ldx = 0, mdx = 0;
							unsigned depth = 0;
							for (; ldx < toks.size(); ++ldx) {
								auto type = toks[ldx]->type();
								if (isOpener (type)) depth++;
								else if (isCloser (type)) depth--;
								else if (type == separ && depth == 0){
									Expr_t* ptr;
									args.push_back (shp_t (ptr = new Expr_t ()));
									ptr->l.reset (new std::vector<shp_t> (std::begin (toks) + mdx, std::begin (toks) + ldx));
									lists.push_back (ptr->l.get());
									mdx = ldx + 1;
								}
							}
							if (ldx >= mdx) {
								Expr_t* ptr;
								args.push_back (shp_t (ptr = new Expr_t ()));
								ptr->l.reset (new std::vector<shp_t> (std::begin (toks) + mdx, std::begin (toks) + ldx));
								lists.push_back (ptr->l.get ());
							}

							break; // сохранили вызов функции
						}
						else if (trigger.count(type) > 0) {
							// есть вызов функции [jdx]->trigger [idx+1]->(...)<-[?]
							auto kdx = findCloser (tokens, idx + 1);
							auto ndx = jdx;
							// [ndx]->(...)<-[jdx] [idx+1]->(...)<-[kdx]
							std::vector<shp_t> toks (std::begin (tokens) + idx + 2, std::begin (tokens) + kdx-1);
							tokens.erase (std::begin (tokens) + idx + 1, std::begin (tokens) + kdx + 1);
							T* ptr;
							shp_t call_tok(ptr = new T ());
							
							ptr->id.reset (new Id_t ());
							ptr->id -> setStr (">=-expr-=<");
							auto& args = ptr -> args;

							args.push_back (tokens[jdx]);
							
							tokens[jdx] = call_tok;

							unsigned ldx = 0, mdx = 0;
							unsigned depth = 0;
							for (; ldx < toks.size(); ++ldx) {
								auto type = toks[ldx]->type();
								if (isOpener (type)) depth++;
								else if (isCloser (type)) depth--;
								else if (type == separ && depth == 0){
									Expr_t* ptr;
									args.push_back (shp_t (ptr = new Expr_t ()));
									ptr->l.reset (new std::vector<shp_t> (std::begin (toks) + mdx, std::begin (toks) + ldx));
									lists.push_back (ptr->l.get());
									mdx = ldx + 1;
								}
							}
							if (ldx >= mdx) {
								Expr_t* ptr;
								args.push_back (shp_t (ptr = new Expr_t ()));
								ptr->l.reset (new std::vector<shp_t> (std::begin (toks) + mdx, std::begin (toks) + ldx));
								lists.push_back (ptr->l.get ());
							}
							break;
						}
						// обработка варианта, когда что-то (лямбда / массив) вылетело из скобок
						else if (isCloser (type)) {
							// есть вызов функции [?]->(...)<-[jdx] [idx+1]->(...)<-[?]
							auto kdx = findCloser (tokens, idx + 1);
							auto ndx = findOpener (tokens, jdx);
							// [ndx]->(...)<-[jdx] [idx+1]->(...)<-[kdx]
							std::vector<shp_t> toks (std::begin (tokens) + idx + 2, std::begin (tokens) + kdx - 1);
							tokens.erase (std::begin (tokens) + idx + 1, std::begin (tokens) + kdx + 1);
							T* ptr;
							shp_t call_tok(ptr = new T ());
							

							ptr->id.reset (new Id_t ());
							ptr->id -> setStr (">=-expr-=<");
							auto& args = ptr -> args;

							Expr_t* e_ptr;
							args.push_back (shp_t (e_ptr = new Expr_t ()));
							e_ptr->l = std::shared_ptr<std::vector<shp_t>>(new std::vector<shp_t> (std::begin(tokens) + ndx, std::begin(tokens) + jdx + 1));
							
							tokens.erase (std::begin (tokens) + ndx + 1, std::begin (tokens) + jdx + 1);
							tokens[ndx] = call_tok;

							lists.push_back (e_ptr->l.get ());

							unsigned ldx = 0, mdx = 0;
							unsigned depth = 0;
							for (; ldx < toks.size(); ++ldx) {
								auto type = toks[ldx]->type();
								if (isOpener (type)) depth++;
								else if (isCloser (type)) depth--;
								else if (type == separ && depth == 0){
									Expr_t* ptr;
									args.push_back (shp_t (ptr = new Expr_t ()));
									ptr->l.reset (new std::vector<shp_t> (std::begin (toks) + mdx, std::begin (toks) + ldx));
									lists.push_back (ptr->l.get ());
									mdx = ldx + 1;
								}
							}
							if (ldx >= mdx) {
								Expr_t* ptr;
								args.push_back (shp_t (ptr = new Expr_t ()));
								ptr->l.reset (new std::vector<shp_t> (std::begin (toks) + mdx, std::begin (toks) + ldx));
								lists.push_back (ptr->l.get ());
							}
							break;
						}//*/

						else break;

					}

					if (jdx == 0) break;
					--jdx;
				}
			}
			if (idx == 0) break;
			--idx;
		}
	}
}
