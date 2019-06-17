#include "parser_of_conditional_and_loop_statements_and_lambda_defs.h"

using shp_t = std::shared_ptr<Token>;
using vec_shp_t = std::vector<shp_t>;

void reduce_conditional_statements (std::vector<shp_t>& tokens);
void reduce_body_of_lambdas_conditions_and_loops (
	vec_shp_t& tokens,
	std::set<Tok> triggers,
	std::vector<vec_shp_t*>& lists
);


void parser_3 (std::vector<std::vector<std::shared_ptr<Token> >*>& lists) {
	std::vector<std::vector<std::shared_ptr<Token> >*> lists2;
	// for (auto& it : lists) reduce_conditional_statements (*it);
	for (auto& tokens : lists) { printTokens_ (*tokens); printf ("\n\n\n"); }
	dlog ("meh");
	//*
	for (auto& it : lists) {
		if (!it->empty())
			reduce_body_of_lambdas_conditions_and_loops (
				*it,
				{
					Tok::Lambda, Tok::WhileKey, Tok::ForKey,
					Tok::IfKey, Tok::ElseKey, Tok::ElifKey
				},
				lists2
			);
	}//*/
	dlog ("hmmm");
	// не осталось ни одной не осмысленной лямбды, цикла, или условного оператора
	// for (auto& tokens : lists) { printf ("\n\n\n"); printTokens (*tokens); printf ("\n\n\n"); }
}

inline bool isOpenerUnsave (Tok type) {return type == Tok::OpenBody || isOpener (type);}
inline bool isCloserUnsave (Tok type) {return type == Tok::CloseBody || isCloser (type);}

void packArguments (
	LambdaDef_t* p_lambda,
	vec_shp_t& la_args)
{
	// Упаковка id аргументов и их типов
	//std::remove_if (std::begin (la_args), std::end (la_args), [](auto& it) {return it->type () == Tok::Space; });
	bool its_type = false, ret_type = false;
	Tok prew_type = Tok::Space;
	unsigned depth = 0;
	size_t
		start_type = 0,	// попавшееся начало типа
		start_args = 0;	// аргумент, начиная с которого мы применяем тип

	Tok type = la_args[0]->type (); // текущий тип
	
	for (size_t mdx = 0; mdx < la_args.size (); ++mdx) {
		type = la_args[mdx] -> type ();
		if (type == Tok::Space) continue;

		if (its_type) {
			if (type == Tok::EndType) { // если перед нами завершение типа
				its_type = false; // снимаем флаг
				// и для каждого предшествующего аргумента
				if (!ret_type) {
					for (size_t idx = start_args; idx < p_lambda -> args.size (); ++idx) { // для каждого аргумента
						// сохраняем определённый тип
						size_t jdx = start_type;
						while (jdx + 1 < la_args.size() && la_args[jdx]->type () == Tok::Space)++jdx;
						p_lambda->args[idx].first = la_args[jdx];
						dlog (jdx);
						vec_shp_t tmp(std::begin (la_args) + start_type, std::begin (la_args) + mdx);
						printTokens ("\n---\n", tmp, "\n===\n");
					}
					start_args = p_lambda -> args.size ();
				} else {
					size_t jdx = start_type;
					while (jdx + 1 < la_args.size () && la_args[jdx]->type () == Tok::Space)++jdx;
					p_lambda->ret_type = la_args[jdx];
				}
			}
			continue;
		}
		// если мы не в зоне типа
		// если перед нами id, то это аргумент, который стоит запомнить
		else if (type == Tok::Id) {
			p_lambda->args.push_back({nullptr, la_args[mdx]}); // по умолчанию -- автотип
			continue;
		}
		// если перед нами начало описания возвращаемого типа
		else if (type == Tok::Sword || type == Tok::Arrow) {
			ret_type = true;
		}

		if (type == Tok::StartType) {
			its_type = true;
			start_type = mdx + 1;
			continue;
		}
		if (type == Tok::Comma) {
			//dlog ("COMMA!!1");
			its_type = false;
			start_args = p_lambda -> args.size ();
			continue;
		}
		if (isOpener(type)) {++depth; start_type = mdx + 1; continue;}
		if (isCloser(type)) {--depth; continue;}
	}
	//*/
	//dlog ("done");
}


void reduceForLoopWithBody (
	vec_shp_t& tokens,
	size_t idx,
	size_t ldx,
	size_t jdx,
	size_t kdx)
{
    // [idx]->['при'или'инапри'] ... [jdx]->'{'...[kdx]->'} ELSE' {0}
    // или              -----------||-----------  [kdx]->'} ELIF' {1}
    // или              -----------||-----------    ';)'<-[kdx]   {2}
    // или              -----------||-----------    ';;'<-[kdx]   {3}
    //std::cout << "one\n";
	For_t* p_for;
	tokens[idx].reset (p_for = new For_t ());
    Tok type = tokens[kdx]->type ();
	{// записали название итератора и индекса
		bool first = true;
		for (size_t i = idx; i < ldx; ++i) {
			if (tokens[i]->type() == Tok::Id) {
				if (first) {
					p_for->iter = as<Id_t>(tokens[i]);
					first = false;
				} else {
					p_for->idx = as<Id_t>(tokens[i]);
					break;
				}
			}
		}
	}
	// записали источник ряда
    Expr_t* p_expr;
	p_for->range.reset(p_expr = new Expr_t());
	p_expr -> l.reset (
		new std::vector<std::shared_ptr<Token> > (
			std::begin(tokens) + ldx + 1,
			std::begin(tokens) + jdx));
	
	// записали тело
    p_for -> body.reset (p_expr = new Expr_t ());
    p_expr -> l.reset (
        new std::vector<std::shared_ptr<Token> > (
			std::begin(tokens) + jdx + 1,
			std::begin(tokens) + kdx)
    );
	// удалили всё, оставив сокращённый For_t в idx
    tokens.erase (
		std::begin(tokens) + idx + 1,
		std::begin(tokens) + kdx + 1);
}


void reduce_body_of_lambdas_conditions_and_loops (
	vec_shp_t& tokens,
	std::set<Tok> triggers,
	std::vector<vec_shp_t*>& lists)
{
	lists.push_back (&tokens);
	for (size_t idx = tokens.size () - 1;; --idx) {
		size_t tokens_size = tokens.size ();
		Tok type = tokens[idx]->type ();
		
		if (triggers.count (type) > 0) { // [idx]->trigger ... [?]->'{' ... '}'<-[?]
			unsigned depth = 0;
			auto jdx = idx;
			while (jdx < tokens_size) {
				Tok type = tokens[jdx] -> type ();
				if (isOpener (type)) ++depth;
				else if (isCloser (type)) --depth;
				if (depth == 0 && (type == Tok::OpenBody || type == Tok::OpenBodyOfLambda)) break;
				++jdx;
			}

			// [idx]->trigger ... [jdx]->'{' ... '}'<-[?]
			if (type == Tok::Lambda) { // trigger == 'ля'
				auto kdx = jdx + 1;
				// можно оставлять пустое пространство между открытием тела и сигналом о длине
				// (х.з. зачем оставляю это, но для хороших людей такого говна не жалко)
				while (kdx < tokens_size && tokens[kdx] -> type () == Tok::Space) ++kdx;

				//*
				// Если лямбда с несколькими statement-ами
				if (tokens[kdx] -> type () == Tok::Dot) { // [idx]->'ля' ... [jdx]->'{' [kdx]->'.' ... ';;'<-[?]
					auto ldx = kdx + 1;
					while (tokens_size > ldx && tokens[ldx]->type () == Tok::Space) ++ldx;
					bool emptyBody = true; // лямбда с пустым телом, если (ля х. ;) или (ля х.);

					Tok type = tokens[ldx]->type ();

					// если тело оказалось не пустым
					if (tokens_size > ldx && type != Tok::Semicolon && !isCloser (type)) { 
						emptyBody = false;
						depth = 0;
						Tok prew_type = Tok::OpenBodyOfLambda;
						while (ldx < tokens_size) {
							Tok type = tokens[ldx] -> type ();
							if (isOpener(type)) ++depth;
							else if (isCloser (type)) {if (depth != 0) --depth; else break;}
							if (depth == 0 && type == Tok::Semicolon && prew_type == Tok::Semicolon) break;
							// ';' ~whitespace~ ';' -- допустимо такое завершение тела
							if (type != Tok::Space) prew_type = type; 
							++ldx;
						}
					}
					// [idx]->'ля' ... [jdx]->'{' [kdx]->'.' ... [';;'  v  ';)']<-[ldx]
					// Упаковываем в лямбду аргументы [idx + 1 : jdx] и тело [kdx + 1 : ldx - 1] в виде необработанного набора токенов
					packLambdaExpr<Expr_t>(emptyBody, idx, jdx, kdx + 1, ldx, tokens, lists);
				}
				// Если лямбда из одного выражения
				else {
					auto ldx = kdx + 1;
					depth = 0;
					while (ldx < tokens_size) {
						Tok type = tokens[ldx] -> type ();
						if (isOpener (type)) ++depth;
						else if (isCloser (type)) {if (depth > 0) --depth; else break;}
						if (depth == 0 && type == Tok::Semicolon) break;
						++ldx;
					}
					// [idx]->'ля' ... [jdx]->'{' ... [';'  v  ')']<-[ldx]
					// Упаковываем в лямбду аргументы [idx + 1 : jdx] и возвращаемое значение [jdx + 1 : ldx]
					packLambdaExpr <Return_t>(false, idx, jdx, jdx + 1, ldx, tokens, lists);
				}
				//*/
			}
			
			else if (
				type == Tok::IfKey
				|| type == Tok::ElifKey
				|| type == Tok::WhileKey
				|| type == Tok::ElseKey)
			{
				// trigger == 'при' || trigger == 'инапри' || trigger == 'пока' || trigger == 'иначе'
				// [idx]->'при' ... [jdx]->'{' ... ';;'<-[?]
				// или -----------||-----------  [?]->'} ELSE'
				// или -----------||-----------  [?]->'} ELIF'
				// Поиск конца тела
				auto kdx = jdx + 1;
				while (tokens_size > kdx && tokens[kdx]->type () == Tok::Space) ++kdx;
				// тут условие с пустым телом, если первый элементв теле (при х==1 {: ->;) или (при х==0 {: ->);
				bool emptyBody = true;

				Tok type = tokens[kdx]->type ();
				int closerType = 0;
				if (tokens_size > kdx && type != Tok::Semicolon && !isCloser (type)) { // если тело оказалось не пустым
					emptyBody = false;
					depth = 0;
					Tok prew_type = Tok::OpenBodyOfLambda;
					while (kdx < tokens_size) {
						Tok type = tokens[kdx] -> type ();
						if (isOpener(type)) ++depth;
						else if (isCloser (type)) {if (depth != 0) --depth; else break;}
						// если мы на своей глубине встретили закрытие тела, либо две ';' подряд, то мы нашли тело
						if (depth == 0) {
							if (type == Tok::CloseBody) break;
							if (type == Tok::Semicolon && prew_type == Tok::Semicolon) {--kdx; break;}
						}
						if (type != Tok::Space) prew_type = type; // ';' ~whitespace~ ';' -- допустимо такое завершение тела
						++kdx;
					}
				}

				// [idx]->'при' ... [jdx]->'{'...[kdx]->'} ELSE'
				// или -----------||-----------  [kdx]->'} ELIF'
				// или -----------||-----------    ';)'<-[kdx]
				// или -----------||-----------    ';;'<-[kdx]
				//if (!emptyBody) {
					switch (tokens[idx]->type()) {
					case Tok::IfKey:    reduceConditionWithBody<If_t>   (tokens, idx, jdx, kdx); break;
					case Tok::ElifKey:  reduceConditionWithBody<Elif_t> (tokens, idx, jdx, kdx); break;
					case Tok::WhileKey: reduceConditionWithBody<While_t>(tokens, idx, jdx, kdx); break;
					case Tok::ElseKey:  reduceConditionWithBody<Else_t> (tokens, idx, jdx, kdx); break;
					default: break;
					}
				//} else {
				//}
			}
			
			else if (type == Tok::ForKey) {
				// TODO: Распознать конец тела
				// [idx]->'для' 'x_id' 'i_id' [?]->'in some_range' [jdx]->'{' ... ';;'<-[?]
				size_t ldx = idx + 1;
				while (ldx < jdx && tokens[ldx]->type() != Tok::In) ++ldx;
				// [idx]->'для' ... [ldx]->'in some_range' [jdx]->'{' ... ';;'<-[?]
				
				auto kdx = jdx+1;
				while (tokens_size > kdx && tokens[kdx]->type () == Tok::Space) ++kdx;
				// тут условие с пустым телом, если первый элементв теле (при х==1 {: ->;) или (при х==0 {: ->);
				bool emptyBody = true;

				Tok type = tokens[kdx]->type ();
				int closerType = 0;
				if (tokens_size > kdx && type != Tok::Semicolon && !isCloser (type)) { // если тело оказалось не пустым
					emptyBody = false;
					depth = 0;
					Tok prew_type = Tok::OpenBodyOfLambda;
					while (kdx < tokens_size) {
						Tok type = tokens[kdx] -> type ();
						if (isOpener(type)) ++depth;
						else if (isCloser (type)) {if (depth != 0) --depth; else break;}
						// если мы на своей глубине встретили закрытие тела, либо две ';' подряд, то мы нашли тело
						if (depth == 0) {
							if (type == Tok::CloseBody) break;
							if (type == Tok::Semicolon && prew_type == Tok::Semicolon) {--kdx; break;}
						}
						if (type != Tok::Space) prew_type = type; // ';' ~whitespace~ ';' -- допустимо такое завершение тела
						++kdx;
					}
				}
				// [idx]->'для' 'id' 'id' [ldx]->'in some_range' [jdx]->'{' ... ';;'<-[?]
				reduceForLoopWithBody (tokens, idx, ldx, jdx, kdx);
			}
		}

		if (idx == 0) break;
	}
}


void reduce_conditional_statements(std::vector<shp_t>& tokens) {
	// if

	for (size_t idx = 0; idx < tokens.size (); ++idx) {
		Tok type = tokens[idx] -> type ();
		if (type == Tok::If) { // [idx]->if ... [?]->{ ... }<-[?]
			unsigned depth = 0;
			auto jdx = idx + 1;
			while (jdx < tokens.size ()) {
				type = tokens[jdx] -> type ();
				if (isOpener (type)) ++depth;
				else if (isCloser (type)) --depth;
				if (depth == 0 && type == Tok::OpenBody) break;
				++jdx;
			}
			auto kdx = jdx;
			depth = 0;
			while (kdx < tokens.size ()) {
				type = tokens[kdx] -> type ();
				if (isOpenerUnsave (type)) ++depth;
				else if (isCloserUnsave (type)) --depth;
				if (depth == 0) break;
				++kdx;
			}
			// [idx]->if ... [jdx]->{ ... }<-[kdx]
			if (kdx != tokens.size ()) {
				If_t t;
			}
		}
	}
}
