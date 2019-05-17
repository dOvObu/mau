#ifndef LEXER_DETECT_KEYS_H
#define LEXER_DETECT_KEYS_H
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "tokens.h"
#include "lexer_without_keys.h"
#include "dLog.h"

bool loadKeyWords (const char path[]);
bool lexer_2 (std::vector<std::shared_ptr<Token> >& tokens);

#endif // LEXER_DETECT_KEYS_H
