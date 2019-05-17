#ifndef LEXER_WITHOUT_KEYS_H
#define LEXER_WITHOUT_KEYS_H
#include <vector>
#include <iostream>
#include <memory>
#include <windows.h>
#include <fstream>

#include "dLog.h"
#include "tokens.h"
#include "gswstr.h"

void lexer_1 (const char path[], std::vector <std::shared_ptr<Token>>& tokens);

#endif // LEXER_WITHOUT_KEYS_H
