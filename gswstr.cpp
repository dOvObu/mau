#include "gswstr.h"
static std::set<wchar_t> abc;
static std::vector<wchar_t> t_abc[2];
static std::vector<wchar_t> s_abc[2];
static std::wstring* ws{nullptr};


std::wstring::size_type find_lin(std::vector<wchar_t>& s, wchar_t c) {
	const auto size = s.size (); 
	for (size_t idx = 0; idx < size; ++idx) {
		if (s[idx] == c) return idx;
	}
	return std::wstring::npos;
}

void cToL (wchar_t c, std::string* s)
{
	std::wstring::size_type idx = 0;
	if ((idx = find_lin (s_abc[0], c)) != std::wstring::npos) {
		s->push_back (s_abc[1][idx]);
		return;
	}
	if ((idx = find_lin (t_abc[0], c)) != std::wstring::npos) {
		int key = -1;
		long shift = 0;
		if (idx > t_abc[1].size () - 3) { key = -2; shift = t_abc[1].size ()-3; }
		s->push_back (*(t_abc[1].end () + key));
		s->push_back (t_abc[1][idx - shift]);
		return;
	}
	for (int idx = 1; idx < 2; ++idx) {
		const auto ch = *(t_abc[1].end () - idx);
		if (c == ch) {
			s->push_back (ch);
			s->push_back (ch);
			return;
		}
	}
	s->push_back (c);
}

void lToC (char c, std::wstring* s)
{
	static int sup = 0;
	//std::cout << "sup: " << sup << std::endl;
	if (sup == 0) {
		for (int idx = -1; idx > -3; --idx)
			if (c == *(t_abc[1].end () + idx)) {
				sup = idx;
				return; // зарядился на вывод кириллицы
			}
		// иначе, добавляем латиницу как есть
		s->push_back (c);
		return;
	}
	else {
		if (c == *(t_abc[1].end () + sup))
			s->push_back (*(t_abc[1].end () + sup));
		else
			s->push_back (t_abc[0][find_lin (t_abc[1], c) + (sup == -2 ? t_abc[1].size() - 3 : 0)]);
		sup = 0; // разрядился
		return;
	}
}

void loadABC (const char path[])
{
	const unsigned buff_size = 200;
	char buff[buff_size];
	std::ifstream fin (path);
	int idx = 0;
	while (!fin.eof ())
	{
		fin.getline (buff, buff_size);
		std::wstring&& wb = stows (buff);
		bool same = true;
		for (auto& it : wb) {
			if (it == L'_') { same = false; continue; }
			if (!same) t_abc[idx].push_back (it);
			else if (it != L' ') { s_abc[idx].push_back (it); }
			if (it != L' ') { abc.insert (it); }
		}
		if (!same) ++idx;

		std::wcout << wb << std::endl;
	}
}

bool isDigit (wchar_t ch) {
	return (ch == L'0') || (ch == L'1') || (ch == L'2') || (ch == L'3') || (ch == L'4') || (ch == L'5') || (ch == L'6') || (ch == L'7') || (ch == L'8') || (ch == L'9');
}
bool isDigit (char ch) {
	return (ch == '0') || (ch == '1') || (ch == '2') || (ch == '3') || (ch == '4') || (ch == '5') || (ch == '6') || (ch == '7') || (ch == '8') || (ch == '9');
}


bool isLetter (wchar_t ch) {
	return abc.count (ch);
}
