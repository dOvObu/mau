#ifndef SWSTR_H
#define SWSTR_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <codecvt>
#include <locale>
#include <vector>
#include <set>

static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

static std::wstring stows (std::string& s) { return converter.from_bytes (s); }
static std::wstring stows (std::string&& s) { return converter.from_bytes (s); }
static std::string wstos (std::wstring& ws) { return converter.to_bytes (ws); }
static std::string wstos (std::wstring&& ws) { return converter.to_bytes (ws); }

bool isDigit (wchar_t ch);
bool isDigit (char ch);
bool isLetter (wchar_t ch);
void loadABC (const char path[]);
void cToL (wchar_t c, std::string* s);
void lToC (char c, std::wstring* s);

#endif // SWSTR_H
