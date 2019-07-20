#ifndef CIRSTR_H
#define CIRSTR_H
#include <string>
#include "gswstr.h"


struct cirStr
{
	cirStr(std::wstring s);
	cirStr(wchar_t s[]);
	cirStr& operator=(std::wstring s);
	cirStr& operator=(const std::string& s);
	std::wstring w();
	cirStr(){}
	cirStr(const std::string& _s) : s (_s){}
	std::string s;
};
std::string cirToLat(const std::wstring& cir);
std::wstring latToCir (const std::string& s);

#endif // CIRSTR_H
