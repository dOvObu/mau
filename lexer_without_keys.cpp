#include "lexer_without_keys.h"

using shp_t = std::shared_ptr<Token>;


void lexer_1 (const char path[], std::vector <shp_t>& tokens) {
	std::vector <std::wstring> lines;
	
	const unsigned buff_size = 200;
	char buff[buff_size];
	std::ifstream fin (path);
	size_t line_idx = 0;
	bool readyToCloseBody = false, approvedClosingBody = false;

	auto add = [&tokens](Token* t, const size_t line_idx, const size_t idx) {
		tokens.push_back (shp_t (t, pass));
		tokens.back ()->setPos (line_idx, idx);
	};
	auto changeBack = [&tokens](Token* t, const size_t line_idx, const size_t idx) {
		tokens.back () = shp_t (t, pass);
		tokens.back ()->setPos (line_idx, idx - 1);
	};
	auto tryToSetId = [&tokens](const Tok& prew_t, const size_t idx, std::wstring& wb) {
		if (prew_t == Tok::Id) {
			tokens.back ()->setId (wb.substr (tokens.back()->idx (), idx - tokens.back()->idx ()));
		}
	};
	auto tryToSetNum = [&tokens](const Tok& prew_t, const size_t idx, std::wstring& wb) {
		if (prew_t == Tok::Number) {
			tokens.back ()->setId (wb.substr (tokens.back()->idx (), idx - tokens.back()->idx ()));
		}
	};
	auto tryToSetParentecis = [&add, &tryToSetId, &tryToSetNum](const wchar_t ch, Tok prew_t, const size_t line_idx, const size_t idx, std::wstring& wb)->bool {
		if (ch == L'(') {
			tryToSetId (prew_t, idx, wb);
			tryToSetNum (prew_t, idx, wb);
			add (new OpenParenthesis_t (), line_idx, idx);
			add (new Space_t(), line_idx, idx);
			return true;
		}
		if (ch == L')') {
			tryToSetId (prew_t, idx, wb);
			tryToSetNum (prew_t, idx, wb);
			add (new CloseParenthesis_t (), line_idx, idx);
			return true;
		}
		if (ch == L'[') {
			tryToSetId (prew_t, idx, wb);
			tryToSetNum (prew_t, idx, wb);
			add (new OpenBrackets_t (), line_idx, idx);
			return true;
		}
		if (ch == L']') {
			tryToSetId (prew_t, idx, wb);
			tryToSetNum (prew_t, idx, wb);
			add (new CloseBrackets_t (), line_idx, idx);
			return true;
		}
		if (ch == L'{') {
			tryToSetId (prew_t, idx, wb);
			tryToSetNum (prew_t, idx, wb);
			add (new OpenCurlyBrackets_t (), line_idx, idx);
			return true;
		}
		if (ch == L'}') {
			tryToSetId (prew_t, idx, wb);
			tryToSetNum (prew_t, idx, wb);
			add (new CloseCurlyBrackets_t (), line_idx, idx);
			return true;
		}
		return false;
	};

	while (!fin.eof()) {
		fin.getline (buff, buff_size);
		
		std::wstring wb = stows (buff);
		//for (auto& it : buff) wb.push_back (it);

		if (!wb.empty()) {

			lines.push_back (wb);
			
			for (size_t idx = 0; idx < wb.length (); ++idx) {

				if (!approvedClosingBody) readyToCloseBody = false;
				approvedClosingBody = false;
				const auto ch = wb[idx];
				Tok prew_t = (tokens.empty ())? Tok::Space : tokens.back ()->type ();

				if (ch == L'"') {
					if (prew_t != Tok::String)
						add(new String_t (), line_idx, idx);
					else {
						tokens.back ()->setId (wb.substr(tokens.back()->idx () + 1, idx - tokens.back()->idx () - 1));
						add (new EndString_t(), line_idx, idx);
					}
					continue;
				}

				if (prew_t != Tok::String) {
					if (prew_t == Tok::Decrement && ch == L'-') { // комментарии
						tokens.pop_back ();
						idx = wb.length ();
						continue;
					}
					if (prew_t != Tok::Id) {
						if (isLetter (ch)) { add (new Id_t(), line_idx, idx); continue; } // начало id
						if (prew_t != Tok::Number && isDigit (ch)) { add (new Number_t(), line_idx, idx); continue; } // начало num
					}
					if (ch == L'.') {
						tryToSetId (prew_t, idx, wb);
						if (prew_t != Tok::Number) add (new Dot_t(), line_idx, idx);
						continue;
					}
					if (ch == L':') {
						tryToSetId (prew_t, idx, wb);
						tryToSetNum (prew_t, idx, wb);
						add (new Colon_t (), line_idx, idx);
						continue;
					}
					if (ch == L',') {
						tryToSetId (prew_t, idx, wb);
						tryToSetNum (prew_t, idx, wb);
						add (new Comma_t (), line_idx, idx);
						continue;
					}
					if (ch == L';') {
						tryToSetId (prew_t, idx, wb);
						tryToSetNum (prew_t, idx, wb);
						if (!readyToCloseBody) approvedClosingBody = readyToCloseBody = true;
						add (new Semicolon_t (), line_idx, idx);
						continue;
					}

					if (tryToSetParentecis (ch, prew_t, line_idx, idx, wb)) continue;

					if (ch == L'-') {
						tryToSetId (prew_t, idx, wb);
						tryToSetNum (prew_t, idx, wb);
						if (prew_t == Tok::Minus) changeBack (new Decrement_t (), line_idx, idx);
						else add (new Minus_t (), line_idx, idx);
						continue;
					}
					if (ch == L'+') {
						tryToSetId (prew_t, idx, wb);
						tryToSetNum (prew_t, idx, wb);
						if (prew_t == Tok::Plus) changeBack (new Increment_t (), line_idx, idx);
						else if (prew_t == Tok::Minus) changeBack (new Sword_t (), line_idx, idx);
						else add (new Plus_t (), line_idx, idx);
						continue;
					}
					if (ch == L'*') {
						tryToSetId (prew_t, idx, wb);
						tryToSetNum (prew_t, idx, wb);
						if (prew_t == Tok::Multiply) changeBack (new Power_t (), line_idx, idx);
						else add (new Multiply_t (), line_idx, idx);
						continue;
					}
					if (ch == L'/') {
						tryToSetId (prew_t, idx, wb);
						tryToSetNum (prew_t, idx, wb);
						//if (prew_t == Tok::Devide) changeBack (new Power_t (), line_idx, idx); else
						add (new Devide_t (), line_idx, idx);
						continue;
					}
					if (ch == L'\\') {
						tryToSetId (prew_t, idx, wb);
						tryToSetNum (prew_t, idx, wb);
						//if (prew_t == Tok::Devide) changeBack (new Power_t (), line_idx, idx); else
						add (new Lambda_t (), line_idx, idx);
						std::cout << "test" << std::endl;
						continue;
					}
					if (ch == L'<') {
						tryToSetId (prew_t, idx, wb);
						tryToSetNum (prew_t, idx, wb);
						add (new Less_t (), line_idx, idx);
						continue;
					}
					if (ch == L'!') {
						tryToSetId (prew_t, idx, wb);
						tryToSetNum (prew_t, idx, wb);
						add (new nye_t (), line_idx, idx);
						continue;
					}
					if (ch == L'%') {
						tryToSetId (prew_t, idx, wb);
						tryToSetNum (prew_t, idx, wb);
						add (new Reference_t (), line_idx, idx);
						continue;
					}
					if (ch == L'>') {
						tryToSetId (prew_t, idx, wb);
						tryToSetNum (prew_t, idx, wb);
						if (prew_t == Tok::Minus) changeBack (new Arrow_t (),line_idx, idx - 1);
						if (prew_t == Tok::Equal) changeBack (new Therefore_t(), line_idx, idx - 1);
						else add(new More_t(), line_idx, idx);
						continue;
					}
					if (ch == L'=') {
						tryToSetId (prew_t, idx, wb);
						tryToSetNum (prew_t, idx, wb);
						if (prew_t == Tok::Less) changeBack (new LessOrEqual_t (), line_idx, idx - 1);
						else if (prew_t == Tok::More) changeBack (new MoreOrEqual_t (), line_idx, idx - 1);
						else if (prew_t == Tok::Assign) changeBack (new Equal_t (), line_idx, idx);
						else if (prew_t == Tok::nye) changeBack (new NotEqual_t (), line_idx, idx);
						else add (new Assign_t (), line_idx, idx - 1);
						continue;
					}
					if (ch == L' ' || ch == L'\t') {
						if ( prew_t != Tok::Space) {
							tryToSetId (prew_t, idx, wb);
							tryToSetNum (prew_t, idx, wb);
							add(new Space_t(), line_idx, idx);
						}
						if (readyToCloseBody) approvedClosingBody = true;
					}
				}
			}

			auto&& prew_t = tokens.empty () ? Tok::Space : tokens.back ()->type ();
			tryToSetId (prew_t, wb.length (), wb);
			tryToSetNum (prew_t, wb.length (), wb);
			if (prew_t != Tok::Space) add (new Space_t (), line_idx, wb.length ());
			if (readyToCloseBody) approvedClosingBody = true;
		}
		
		++line_idx;
	}
	fin.close ();
}//----------------------------------------------------------------//
