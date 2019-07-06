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

void reduceLambdaType (
	std::vector<shp_t>& tokens,
	const Tok& opner,
	const Tok& clser,
	const Tok& separ,
	const Tok& ignor,
	std::vector<std::vector<shp_t>*>& lists
);

void reduceTemplateCalls (
	std::vector<shp_t>& tokens,
	const Tok& opner,
	const Tok& clser,
	const Tok& separ,
	const Tok& ignor,
	std::vector<std::vector<shp_t>*>& lists
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
	if (tokens.size () > 2) // минимум [1]->'id' [2]->'::' [3]->'id'
		for (size_t idx = 1; idx < tokens.size () - 2; ++idx)
			reduceDotOpIfPossible<TypeFieldCall_t> (
				tokens,
				idx,
				Tok::DoubleColon,
				{Tok::Id}
			);
	// теперь, нигде (в expr-ах) нет неосмысленных двойных двоеточий

	if (tokens.size () > 2) // минимум [1]->'id' [2]->'.' [3]->'id'
		for (size_t idx = 1; idx < tokens.size() - 2; ++idx)
			reduceDotOpIfPossible<FieldCall_t> (
				tokens,
				idx,
				Tok::Dot,
				{Tok::Id, Tok::TypeFieldCall}
			);
	// теперь, нигде (в expr-ах) нет неосмысленных точек
	
	reduceTemplateCalls (
		tokens,
		Tok::OpenTemplateType,
		Tok::CloseTemplateType,
		Tok::Comma,
		Tok::Space,
		lists
	);

	std::vector<std::vector<shp_t>*> lists2 {lists};
	lists.clear ();
	for (auto& tokens : lists2)
		reduceLambdaType (
			*tokens,
			Tok::OpenLambdaType,
			Tok::CloseLambdaType,
			Tok::TypeComma,
			Tok::Space,
			lists
		);
	dlog ("HEHEHEHE");
	for (auto& it : lists) printTokens ("\n", *it, "\n");
	dlog ("hehehe");

	lists2.clear ();
	for (auto& tokens : lists)
		reduceCalls<Call_t> (
			*tokens,
			Tok::OpenParenthesis,
			Tok::CloseParenthesis,
			Tok::Comma,
			Tok::Space,
			{Tok::Call, Tok::ArrayCall, Tok::FieldCall, Tok::TemplateCall},
			lists2
		);
	// теперь, в lists2 находятся ссылки на списки токенов,
	// которые не содержат неосмысленных вызовов функций
	lists.clear ();
	for (auto& it : lists2)
		reduceArrays (*it, Tok::OpenParenthesis, Tok::Comma, lists);
	// теперь, в lists нет неосмысленных массивов

	lists2.clear();
	for (auto& it : lists)
		reduceCalls<ArrayCall_t> (
			*it,
			Tok::OpenBrackets,
			Tok::CloseBrackets,
			Tok::Colon,
			Tok::Space,
			{Tok::Call, Tok::ArrayCall, Tok::ArrayDef, Tok::FieldCall},
			lists2
		);
	// теперь, в lists2 нет неосмысленных вызовов массивов

	lists.clear();
	for (auto& it : lists2) reduceUnOps (*it, lists);
	// теперь, в lists нет неосмысленных унарных операторов и скобок в выражениях

}//-----------------------------------------------------------------//

inline bool isOpener (Tok type){return type == Tok::OpenParenthesis || type == Tok::OpenBrackets || type == Tok::OpenCurlyBrackets;}
inline bool isCloser (Tok type){return type == Tok::CloseParenthesis || type == Tok::CloseBrackets || type == Tok::CloseCurlyBrackets;}

size_t findCloser (std::vector<shp_t>& tokens, Tok opn, Tok cls, size_t jdx) {
	const auto size = tokens.size();
	unsigned depth = 1;
	size_t kdx = jdx + 1;
	for(;depth != 0 && kdx < size; ++kdx) {
		const auto type = tokens[kdx]->type();
		if (type == opn) ++depth;
		else if (type == cls) --depth;
	}
	return kdx;
}
size_t findCloser_ (std::vector<shp_t>& tokens, size_t jdx) {
	const auto size = tokens.size();
	unsigned depth = 1;
	size_t kdx = jdx + 1;
	for(;depth != 0 && kdx < size; ++kdx) {
		const auto type = tokens[kdx]->type();
		if (isOpener (type)) ++depth;
		else if (isCloser (type)) --depth;
	}
	return kdx;
}

size_t findOpener (std::vector<shp_t>& tokens, Tok opn, Tok cls, size_t jdx) {
	unsigned depth = 1;
	size_t kdx = jdx - 1;
	while (depth != 0) {
		const auto type = tokens[kdx]->type();
		if (type == cls) ++depth;
		else if (type == opn) --depth;
		if (kdx == 0) break;
		--kdx;
	}
	return kdx;
}
size_t findOpener (std::vector<shp_t>& tokens, size_t jdx) {
	unsigned depth = 1;
	size_t kdx = jdx - 1;
	while (depth != 0) {
		const auto type = tokens[kdx]->type();
		if (isCloser (type)) ++depth;
		else if (isOpener (type)) --depth;
		if (kdx == 0) break;
		--kdx;
	}
	return kdx;
}

Tok openerFor(Tok closer_type) {
	switch (closer_type) {
		case Tok::CloseBrackets: return Tok::OpenBrackets;
		case Tok::CloseParenthesis: return Tok::OpenParenthesis;
		case Tok::CloseCurlyBrackets: return Tok::OpenCurlyBrackets;
		default: return Tok::Dot;
	}
}


template <typename T>
void moveBracketsToUnOp (
		std::vector<shp_t>& tokens,
		size_t idx,
		size_t jdx,
		size_t kdx,
		std::vector<std::vector<shp_t>*>& lists)
{
	Expr_t* p;
	as<T>(tokens[idx])->right.reset (p = new Expr_t());
	p->l.reset (new std::vector<shp_t>(std::begin(tokens) + jdx + 1, std::begin(tokens) + kdx));
	tokens.erase (std::begin(tokens) + jdx, std::begin(tokens) + kdx + 1);
	lists.push_back(p->l.get ());
}

template<typename T>
bool reduceBracketsToUnOp (
		std::vector<shp_t>& tokens,
		size_t idx,
		size_t jdx,
		std::vector<std::vector<shp_t>*>& lists)
{
	bool done = false;
	if (tokens[jdx]->type()==Tok::OpenParenthesis) {
		size_t kdx = findCloser (tokens, Tok::OpenParenthesis, Tok::CloseParenthesis, jdx);
		moveBracketsToUnOp<T>(tokens, idx, jdx, kdx, lists);
		done = true;
	} else if (tokens[jdx]->type()==Tok::OpenCurlyBrackets) {
		size_t kdx = findCloser (tokens, Tok::OpenCurlyBrackets, Tok::CloseCurlyBrackets, jdx);
		moveBracketsToUnOp<T>(tokens, idx, jdx, kdx, lists);
		done = true;
	} else if (tokens[jdx]->type()==Tok::OpenBrackets) {
		size_t kdx = findCloser (tokens, Tok::OpenBrackets, Tok::CloseBrackets, jdx);
		moveBracketsToUnOp<T>(tokens, idx, jdx, kdx, lists);
		done = true;
	}
	return done;
}

template <typename T>
bool tryReduceToUnOp (
		Tok type,
		size_t idx,
		std::vector<shp_t>& tokens,
		std::vector<std::vector<shp_t>*>& lists)
{
	bool res = false;
	if (tokens[idx]->type() == type) {
		auto jdx = idx + 1;
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
	bool typeDef = false;
	for (size_t idx = 0; idx < tokens.size(); ++idx) {
		Tok type = tokens[idx]->type();
		if (type == Tok::nye) tokens[idx].reset (new Not_t());
		if (type == Tok::EndType) typeDef = false;
		else if (type == Tok::StartType) typeDef = true;
		if (!typeDef) {
			tryReduceToUnOp<UnMinus_t> (Tok::UnMinus, idx, tokens, lists)
			|| tryReduceToUnOp<Not_t> (Tok::Not, idx, tokens, lists)
			|| tryReduceToUnOp<Decrement_t> (Tok::Decrement, idx, tokens, lists)
			|| tryReduceToUnOp<Increment_t> (Tok::Increment, idx, tokens, lists);
		}
		else if (type == Tok::UnMinus) typeDef = false;
	}
}

void reduceArrays (
		std::vector<shp_t>& tokens,
		const Tok& opner,
		const Tok& separ,
		std::vector<std::vector<shp_t>*>& lists)
{
	lists.push_back(&(tokens));

	if (tokens.size() > 1) // минимум [1]->'(' ')'<-[2]
	{
		size_t idx = tokens.size () - 1; // если пятимся, то собираем все вложенные вызовы
		bool needToWorkOn = true;
		while (true) {
			auto type = tokens[idx] -> type ();
			// Для объявления аргументов лямбды или переменной, обработка не ведётся
			if (type == Tok::OpenBodyOfLambda || type == Tok::Assign) {
				needToWorkOn = false;
				if (idx == 0) break;
				--idx;
				continue;
			}

			if (!needToWorkOn) {
				if (type == Tok::Lambda || type == Tok::Semicolon) needToWorkOn = true;
			}
			else {
				if (type == opner) {
					//				текущий тип данных
					enum class val_t {unknown, array, dict} val_type{val_t::unknown};

					std::shared_ptr<ArrayDef_t> arr (new ArrayDef_t());
					std::vector<shp_t> keys;

					unsigned depth = 0;
					auto jdx = idx, kdx = idx;
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
									for (auto ldx = jdx-1; ldx > idx; --ldx) {
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
									auto ldx = jdx-1;
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
								tokens[idx].reset (p = new FieldDef_t());
								for (size_t jdx = 0; jdx < keys.size(); ++jdx)
									p->cells[as<Id_t>(keys[jdx])] = arr->cells[jdx];
								for (auto&it : p->cells)
									lists.push_back (it.second.l.get ());
							}
						}
					}
				}
			}
			if (idx == 0) break;
			--idx;
		}
	}
}

void packArgs (
	std::vector<shp_t>& args,
	Tok separ,
	std::vector<shp_t>& toks,
	std::vector<std::vector<shp_t>*>& lists)
{
	size_t ldx = 0, mdx = 0, ndx = 0;
	bool need_pair = false;
	unsigned depth = 0;
	for (; ldx < toks.size (); ++ldx) {
		auto type = toks[ldx]->type ();
		if (isOpener (type)) depth++;
		else if (isCloser (type)) depth--;
		else if (!need_pair && type == Tok::Id) ndx = ldx;
		else if (depth == 0) {
			if (type == Tok::Colon) {
			mdx = ldx + 1;
			need_pair = true;
			} else if (type == separ) {
				Expr_t* ptr;
				if (need_pair) {
					InCall_is_t* ptr_is;
					args.push_back (shp_t (ptr_is = new InCall_is_t ()));
					ptr_is->id = toks[ndx];
					ptr_is->expr.reset (ptr = new Expr_t ());
					need_pair = false;
				} else {
					args.push_back (shp_t (ptr = new Expr_t ()));
				}
				ptr->l.reset (new std::vector<shp_t> (std::begin (toks) + mdx, std::begin (toks) + ldx));
				lists.push_back (ptr->l.get ());
				mdx = ldx + 1;
			}
		}
	}
	if (ldx >= mdx) {
		Expr_t* ptr;;
		if (need_pair) {
			InCall_is_t* ptr_is;
			args.push_back (shp_t (ptr_is = new InCall_is_t ()));
			ptr_is->id = toks[ndx];
			ptr_is->expr.reset (ptr = new Expr_t ());
			need_pair = false;
		} else {
			args.push_back (shp_t (ptr = new Expr_t ()));
		}
		ptr->l.reset (new std::vector<shp_t> (std::begin (toks) + mdx, std::begin (toks) + ldx));
		printTokens ("\n\t-----=== F ===-----\n", *(ptr->l.get()), "\n");
		lists.push_back (ptr->l.get ());
	}
};

void reduceLambdaType (
	std::vector<shp_t>& tokens,
	const Tok& opner,
	const Tok& clser,
	const Tok& separ,
	const Tok& ignor,
	std::vector<std::vector<shp_t>*>& lists)
{
	lists.push_back (&tokens);
	if (tokens.size () > 1) // минимум [1]->'\(' ')'<-[2]
	{
		size_t idx = tokens.size () - 2; // если пятимся, то собираем все вложенные вызовы
		bool needToWorkOn = true;
		while (true)
		{
			auto type = tokens[idx] -> type ();
			if (type == opner) // если наткнулись на открывающую скобку '\('
			{
				// есть вызов функции [idx]->'\(' ... ')'<-[?]
				size_t kdx = findCloser (tokens, opner, clser, idx);
				// [idx]->([idx + 1 : kdx - 2])<-[kdx-1]
				std::vector<shp_t> toks (
					std::begin (tokens) + idx + 1,
					std::begin (tokens) + kdx - 1);
				tokens.erase (
					std::begin (tokens) + idx,
					std::begin (tokens) + kdx - 1);

				LambdaType_t* ptr;
				tokens[idx].reset (ptr = new LambdaType_t ());
				packArgs (ptr -> args, separ, toks, lists);
				kdx = idx + 1;
				type = ignor;
				auto const size = tokens.size ();
				bool isVoid = false;
				while (true) {
					type = tokens[kdx] -> type ();
					if (type != ignor) {
						if (type == Tok::EndType
							|| kdx == size
							|| isCloser (type)
							|| isOpener (type))
						{
							isVoid = true;
						}
						break;
					}
					++kdx;
				}

				if (isVoid) {
					ptr -> ret = nullptr;
				} else {
					ptr -> ret = tokens[kdx];
					tokens.erase (std::begin (tokens) + kdx);
				}
			}
			if (idx == 0) break;
			--idx;
		}
	}
}

void reduceTemplateCalls (
	std::vector<shp_t>& tokens,
	const Tok& opner,
	const Tok& clser,
	const Tok& separ,
	const Tok& ignor,
	std::vector<std::vector<shp_t>*>& lists)
{
	lists.push_back (&(tokens));
	if (tokens.size () > 2) // минимум [1]->'id' [2]->'(' ')'<-[3]
	{
		size_t idx = tokens.size () - 2; // если пятимся, то собираем все вложенные вызовы
		bool needToWorkOn = true;
		while (true)
		{
			auto type = tokens[idx + 1]->type ();

			// Для объявления аргументов или связывания, обработка ведётся
			if (type == opner) { // если наткнулись на открывающую скобку

				auto jdx = idx;

				while (true) {
					auto type = tokens[jdx]->type ();
					if (type != ignor) {
						if (type == Tok::Id) { // есть вызов функции [idx+1]->(...)<-[?]

							auto kdx = findCloser (tokens, opner, clser, idx + 1);
							// [jdx]->id [idx+1]->([idx + 2 : kdx - 1])<-[kdx-1]
							std::vector<shp_t> toks (
								std::begin (tokens) + idx + 2,
								std::begin (tokens) + kdx - 1);
							tokens.erase (
								std::begin (tokens) + idx + 1,
								std::begin (tokens) + kdx);

							shp_t id = tokens[jdx];
							TemplateCall_t* ptr;
							tokens[jdx].reset (ptr = new TemplateCall_t ());
							ptr->id = as<Id_t> (id);
							packArgs (ptr -> args, separ, toks, lists);

							break; // сохранили вызов функции
						}
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
		size_t idx = tokens.size () - 2; // если пятимся, то собираем все вложенные вызовы
		bool needToWorkOn = true;
		while (true)
		{
			auto type = tokens[idx + 1] -> type ();

			// Для объявления аргументов или связывания, обработка не ведётся
			if (type == Tok::EndType) {
				needToWorkOn = false;
				if (idx == 0) break;
				--idx;
				continue;
			}
			if (type == Tok::StartType) {
				needToWorkOn = true;
				if (idx == 0) break;
				--idx;
				continue;
			}
			if (!needToWorkOn) { // если смотрим не на тип
				if (idx == 0) break;
				--idx;
				continue;
			}
			if (type == opner) { // если наткнулись на открывающую скобку

				auto jdx = idx;

				while (true) {
					auto type = tokens[jdx] -> type ();
					if (type != ignor) {
						if (type == Tok::Id) { // есть вызов функции [idx+1]->(...)<-[?]

							auto kdx = findCloser (tokens, opner, clser, idx + 1);
							// [jdx]->id [idx+1]->([idx + 2 : kdx - 1])<-[kdx-1]
							std::vector<shp_t> toks (
								std::begin (tokens) + idx + 2,
								std::begin (tokens) + kdx - 1);
							tokens.erase (
								std::begin (tokens) + idx + 1,
								std::begin (tokens) + kdx);

							shp_t id = tokens[jdx];
							T* ptr;
							tokens[jdx].reset (ptr = new T ());
							ptr->id = as<Id_t>(id);
							packArgs (as<T> (tokens[jdx])->args,separ,toks,lists);
							break; // сохранили вызов функции
						}
						else if (trigger.count(type) > 0) {
							// есть вызов функции [jdx]->trigger [idx+1]->(...)<-[?]
							auto kdx = findCloser_ (tokens, idx + 1);
							auto ndx = jdx;
							// [ndx]->(...)<-[jdx] [idx+1]->(...)<-[kdx - 1]
							std::vector<shp_t> toks (
								std::begin (tokens) + idx + 2,
								std::begin (tokens) + kdx-1);

							tokens.erase (
								std::begin (tokens) + idx + 1,
								std::begin (tokens) + kdx);
							T* ptr;
							shp_t call_tok(ptr = new T ());
								
							ptr->id.reset (new Id_t ());
							ptr->id -> setStr (type == Tok::TemplateCall ? ">=-tmplt-=<" : ">=-expr-=<");
							auto& args = ptr -> args;

							args.push_back (tokens[jdx]);
								
							tokens[jdx] = call_tok;

							packArgs (args, separ, toks, lists);
							break;
						}
						// обработка варианта, когда что-то (лямбда / массив) вылетело из скобок
						else if (isCloser (type)) {
							// есть вызов функции [?]->(...)<-[jdx] [idx+1]->(...)<-[?]
							auto kdx = findCloser_ (tokens, idx + 1);
							auto ndx = findOpener (tokens, jdx);
							// [ndx]->(...)<-[jdx] [idx+1]->(...)<-[kdx - 1]
							std::vector<shp_t> toks (
								std::begin (tokens) + idx + 2,
								std::begin (tokens) + kdx - 1);
							
							tokens.erase (
								std::begin (tokens) + idx + 1,
								std::begin (tokens) + kdx);
							T* ptr;
							shp_t call_tok(ptr = new T ());
								

							ptr->id.reset (new Id_t ());
							
							ptr->id -> setStr (">=-expr-=<");
							auto& args = ptr -> args;

							Expr_t* e_ptr;
							args.push_back (shp_t (e_ptr = new Expr_t ()));
							e_ptr->l = std::shared_ptr<std::vector<shp_t>>(new std::vector<shp_t> (std::begin(tokens) + ndx, std::begin(tokens) + jdx + 1));
								
							tokens.erase (
								std::begin (tokens) + ndx + 1,
								std::begin (tokens) + jdx + 1);

							tokens[ndx] = call_tok;

							lists.push_back (e_ptr->l.get ());

							packArgs (args, separ, toks, lists);
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

