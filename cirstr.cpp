#include "cirstr.h"


cirStr::cirStr(std::wstring _s):s(cirToLat(_s)){}
cirStr::cirStr(wchar_t _s[]){std::wstring __s (_s); s = cirToLat(__s);}
std::wstring cirStr::w() {return latToCir(s);}


cirStr& cirStr::operator=(std::wstring _s) {s = cirToLat(_s); return *this;}
cirStr& cirStr::operator=(const std::string& _s) {s = _s; return *this;}

namespace cirstr_private {
	static char c_c_c{' '};
	static wchar_t wc_wc_wc{L' '};
	static std::string* s_s_s{nullptr};
	static std::wstring* ws_ws_ws{nullptr};
}

bool wctoc (wchar_t&& wch, char&& ch) {
	using namespace cirstr_private;
	bool res = wc_wc_wc == wch;
	if (res) s_s_s->push_back (ch);
	return res;
}

std::string cirToLat(const std::wstring& s) {
	using namespace cirstr_private;
	std::string res;

	for (const wchar_t& c : s) {
		if (isLetter (c)) {cToL (c, &res); continue;}
		if (c == L'_' || c == L' ' || c == L'\n' || c == L'\t') {
			res.push_back (c);
			continue;
		}
		wc_wc_wc = c;
		s_s_s = &res;
		if (wctoc (L'.', '.')
			|| wctoc (L'0', '0') || wctoc (L'1', '1') || wctoc (L'2', '2') || wctoc (L'3', '3') || wctoc (L'4', '4')
			|| wctoc (L'5', '5') || wctoc (L'6', '6') || wctoc (L'7', '7') || wctoc (L'8', '8') || wctoc (L'9', '9')) continue;
	}
	return res;
}


bool ctowc (char&& ch, wchar_t&& wch) {
	using namespace cirstr_private;
	bool res = c_c_c == ch;
	if (res) ws_ws_ws->push_back (wch);
	return res;
}

std::wstring latToCir (const std::string& s) {
	using namespace cirstr_private;
	std::wstring res;

	for (const auto& c : s) {
		if (isLetter (c)) {
			lToC (c, &res);
			continue;
		}
		if (c == '_' || c == ' ' || c == '\n' || c == '\t') {
			res.push_back (c);
			continue;
		}
		c_c_c = c;
		ws_ws_ws = &res;
		if (ctowc ('.', L'.')
			|| ctowc ('0', L'0') || ctowc ('1', L'1') || ctowc ('2', L'2') || ctowc ('3', L'3') || ctowc ('4', L'4')
			|| ctowc ('5', L'5') || ctowc ('6', L'6') || ctowc ('7', L'7') || ctowc ('8', L'8') || ctowc ('9', L'9')) continue;
	}
	return res;
}
