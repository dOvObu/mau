#include "parser_of_conditional_and_loop_statements_and_lambda_defs.h"

using shp_t = std::shared_ptr<Token>;

void reduce_conditional_statements (std::vector<shp_t>& tokens);
void close_bodyes_of_lambdas (
    std::vector<shp_t>& tokens,
    std::vector<std::vector<std::shared_ptr<Token> >*>& lists
);

void parser_3 (std::vector<std::vector<std::shared_ptr<Token> >*>& lists) {
    for (auto& it : lists) reduce_conditional_statements (*it);
    for (auto& it : lists) reduce_conditional_statements (*it);
}

inline bool isOpener (Tok type) {return type == Tok::OpenParenthesis || type == Tok::OpenBrackets || type == Tok::OpenCurlyBrackets;}
inline bool isCloser (Tok type) {return type == Tok::CloseParenthesis || type == Tok::CloseBrackets || type == Tok::CloseCurlyBrackets;}
inline bool isOpenerUnsave (Tok type) {return type == Tok::OpenBody || isOpener (type);}
inline bool isCloserUnsave (Tok type) {return type == Tok::CloseBody || isCloser (type);}


void close_bodyes_of_lambdas (
    std::vector<shp_t>& tokens,
    std::vector<std::vector<std::shared_ptr<Token> >*>& lists)
{
    Tok prew = tokens[0]->type (), type;
    for (unsigned idx = 0; idx < tokens.size (); ++idx) {
        type = tokens[idx]->type();


        
        prew = tokens[0]->type ();
    }
}


void reduce_conditional_statements(std::vector<shp_t>& tokens) {
    // if
    Spy2 jamesBond;
    for (auto& it : tokens) it -> run (&jamesBond);
    std::cout << "\n\n\n";

    for (unsigned idx = 0; idx < tokens.size (); ++idx) {
        Tok type = tokens[idx] -> type ();
        if (type == Tok::If) { // [idx]->if ... [?]->{ ... }<-[?]
            unsigned jdx = idx + 1, depth = 0;
            while (jdx < tokens.size ()) {
                type = tokens[jdx] -> type ();
                if (isOpener (type)) ++depth;
                else if (isCloser (type)) --depth;
                if (depth == 0 && type == Tok::OpenBody) break;
                ++jdx;
            }
            unsigned kdx = jdx;
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
