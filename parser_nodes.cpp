#include "parser_nodes.h"


/*
using t = Tok;
static std::vector<std::pair<Tok,std::vector<std::vector<t> > > > rools{
        {Tok::Stmt, {	{t::ClassDef},
                                                                {t::Body},
                                                                {t::AssignOp},
                                                                {t::IfStmt},
                                                                {t::Assert},
                                                                {t::Expr}
        }},
        {t::Body, {{t::startRep, t::Stmt, t::Semicolon, t::endRep}}},
        {t::AssignOp, {{t::Id, t::Assign, t::Expr}}},
        {t::Expr, {	{t::binop},
                                                        {t::Expr, t::Power, t::Expr},
                                                        {t::unop},
                                                        {t::OpenParenthesis, t::Expr, t::CloseParenthesis},
                                                        {t::Call},
                                                        {t::Id},
                                                        {t::Int},
                                                        {t::Float},
                                                        {t::String},
                                                        {t::ArrayDef},
                                                        {t::Prototype},
                                                        {t::ArrayCall},
                                                        {t::LambdaDef}
        }},
        {t::unop, {{t::loperation, t::Expr}}},
        {t::binop, {{t::Expr, t::operation, t::Expr}}},
        {t::operation, {{t::Plus}, {t::Minus}, {t::Multiply}, {t::Devide}}},
        {t::loperation, {{t::Plus}, {t::Minus}, {t::Decrement},{t::Increment}}},
        {t::Call, {{t::Expr, t::OpenParenthesis, t::startRep, t::Expr, t::Comma, t::endRep, t::CloseParenthesis}}},
        {t::ArrayDef, {{t::OpenBrackets, t::startRep, t::Expr, t::Comma, t::endRep, t::CloseBrackets}}},
        {t::Prototype, {{t::OpenCurlyBrackets, t::startRep, t::Id, t::Colon, t::Expr, t::Comma, t::endRep, t::CloseCurlyBrackets}}},
        {t::ArrayCall, {{t::Expr, t::OpenBrackets, t::Expr, t::CloseBrackets}}},
        {t::CallField, {{t::Expr, t::Dot, t::Id}}},
        {t::LambdaDef, {{t::Lambda, t::startRep, t::Space, t::Id, t::endRep, t::Dot, t::Body}}},
        {t::ClassDef,	{{t::Class,t::Space,t::Id, t::Colon,t::mightBe,t::Id,t::Colon,t::startRep,t::Assign,t::Semicolon,t::endRep}}}
};

void parse_to_tree (std::vector<std::shared_ptr<Token> >& tokens, nodes::Node& root)
{

}
*/
