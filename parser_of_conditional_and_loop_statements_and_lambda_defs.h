#ifndef PARSER_OF_CONDITIONAL_AND_LOOP_STATEMENTS_AND_LAMBDA_DEFS
#define PARSER_OF_CONDITIONAL_AND_LOOP_STATEMENTS_AND_LAMBDA_DEFS

#include "tokens.h"
#include "dLog.h"
#include "spy2.h"

#include <algorithm>

void parser_3(std::vector<std::vector<std::shared_ptr<Token> >*>& lists);

using vec_shp_t = std::vector<std::shared_ptr<Token> >;

void packArguments (
	LambdaDef_t* p_lambda,
	vec_shp_t& la_args
);

template<typename T>
void packLambdaExpr (
    bool emptyBody,
    
    size_t la_start,
    size_t arg_end,
    size_t body_start,
    size_t body_end,

    std::vector<std::shared_ptr<Token> > &tokens,
    std::vector<std::vector<std::shared_ptr<Token> >*>& lists)
{
    using shp_t = std::shared_ptr<Token>;
    using vec_shp_t = std::vector<shp_t>;

    LambdaDef_t* p_lambda;
    shp_t lambda (p_lambda = new LambdaDef_t ());

    vec_shp_t la_args (std::begin (tokens) + la_start + 1, std::begin (tokens) + arg_end);
	packArguments (p_lambda, la_args);
    T* p_la_body;
    p_lambda -> body.reset (p_la_body = new T());
    if (!emptyBody) {
        p_la_body -> l.reset (new vec_shp_t (std::begin (tokens) + body_start, std::begin (tokens) + body_end));
        lists.push_back (p_la_body -> l.get ());
    }
	 std::cout << "empty body: " << emptyBody << std::endl;
    tokens[la_start] = lambda;
    tokens.erase (std::begin (tokens) + la_start + 1, std::begin (tokens) + body_end);
};

template <typename T>
void reduceConditionWithBody (
    std::vector<std::shared_ptr<Token> >& tokens,
    size_t idx,
    size_t jdx,
    size_t kdx )
{
    // [idx]->['при'или'инапри'] ... [jdx]->'{'...[kdx]->'} ELSE' {0}
    // или              -----------||-----------  [kdx]->'} ELIF' {1}
    // или              -----------||-----------    ';)'<-[kdx]   {2}
    // или              -----------||-----------    ';;'<-[kdx]   {3}
    //std::cout << "one\n";
	T* p_if;
	tokens[idx].reset (p_if = new T ());
    Tok type = tokens[kdx]->type ();
    // записали условие
    Expr_t* p_expr;
    static_if <!(std::is_same<T, Else_t>::value)> ([&](auto f) {
        p_if -> condition.reset (p_expr = new Expr_t ());
        p_expr -> l.reset (
            new std::vector<std::shared_ptr<Token> > (std::begin(tokens) + idx + 1, std::begin(tokens) + jdx)
        );
    });
    // записали тело
    p_if -> body.reset(p_expr = new Expr_t ());
    p_expr -> l.reset (
        new std::vector<std::shared_ptr<Token> > (std::begin(tokens) + jdx + 1, std::begin(tokens) + kdx)
    );
    // записали альтернативную ветку (работает только для if и elif)
    static_if <!(std::is_same<T, While_t>::value || std::is_same<T, Else_t>::value)> ([&](auto f) {
        if (type == Tok::CloseBody) {
            type = tokens[kdx + 1]->type ();
            if (type == Tok::Elif || type == Tok::Else) { // {0} или {1}
                ++kdx;
                p_if -> alternative = tokens[kdx];
            }
        }
	});
    //std::cout << "two\n";
    tokens.erase (std::begin(tokens) + idx + 1, std::begin(tokens) + kdx + 1);
}

#endif
