#ifndef SPY2_H
#define SPY2_H
#include "tokens.h"

struct Spy2 : Runner {
	Spy2 () {}
	void run (UInt_t* t) override {  }
	void run (Int_t* t) override { std::cout << "[i" << t->getInt () << "]"; }
	void run (Float_t* t) override { std::cout << "[f" << t->getFloat () << "]"; }
	void run (String_t* t) override { std::wcout << L"[s'" << t->getId () << L"']"; }
	void run (Expr_t* t) override {
		for (auto& it : *(t->l.get ())) { it->run (this); }
	}
	void run (Call_t* t) override {
		bool tr = true;
		std::wcout << "[Call " << t->id->getId () << '(';
		for (auto& it : t->args) { if (tr) { tr = false; } else { std::cout << ", "; } it->run (this); }
		std::cout << ")]";
	}
	void run (binop_t* t) {
		t->left->run (this);
		switch (t->opType) {
		case Tok::Plus: std::cout << '+'; break;
		case Tok::Minus: std::cout << '-'; break;
		case Tok::Devide: std::cout << '/'; break;
		case Tok::Multiply: std::cout << '*'; break;
		case Tok::Equal: std::cout << "=="; break;
		default: break;
		}
		t->right->run (this);
	}
	void run (Id_t* t) override { std::wcout << "[Id: " << t->getId () << "]"; }
	void run (ArrayDef_t* t) override {
		bool tr = false;
		std::cout << "[m";
		for (auto& it : t->cells) {
			if (tr) { std::cout << ", "; }
			else { tr = true; } it.run (this);
		}
		std::cout << "]";
	}
	void run (OpenParenthesis_t* t) override { std::cout << " (:"; }
	void run (CloseParenthesis_t* t) override { std::cout << ":) "; }
	void run (Space_t* t) override { std::cout << "_"; }
	void run (Dot_t* t) override { std::cout << "."; }
	void run (Lambda_t* t) override { std::cout << "\\"; }
	void run (Semicolon_t* t) override { std::cout << "|"; }
	void run (Colon_t* t) override { std::cout << "is"; }
	void run (DoubleColon_t* t) override { std::cout << "::"; }
	void run (OpenBody_t* t) override { std::cout << " {:"; }
	void run (OpenBodyOfLambda_t* t) override { std::cout << " {:"; }
	void run (CloseBody_t* t) override { std::cout << ":} "; }
	void run (LambdaDef_t* t) override {
		std::cout << "[lambda" << t->args.size () << "(";
		bool f = true;
		for (auto& it : t->args) {
			if (!f) std::cout << ",";
			else f = false;
			it.second->run (this);
			std::cout << ":";
			if (it.first.get () != nullptr) it.first->run (this);
		}
		std::cout << ")";
		if (t->ret_type.get () != nullptr) {
			std::cout << "->";
			t->ret_type->run (this);
		}
		std::cout << ":";
		t->body->run (this);
		std::cout << "]";
	}
	void run (StartType_t* t) override { std::cout << "type:"; }
	void run (I16_type_t* t) override { std::cout << "[i16_t]"; }
	void run (I32_type_t* t) override { std::cout << "[i32_t]"; }
	void run (I64_type_t* t) override { std::cout << "[i64_t]"; }
	void run (U16_type_t* t) override { std::cout << "[u16_t]"; }
	void run (U32_type_t* t) override { std::cout << "[u32_t]"; }
	void run (U64_type_t* t) override { std::cout << "[u64_t]"; }
	void run (F32_type_t* t) override { std::cout << "[f32_t]"; }
	void run (F64_type_t* t) override { std::cout << "[f64_t]"; }
	void run (String_type_t* t) override { std::cout << "[string_t]"; }
	void run (Vector_type_t* t) override { std::cout << "[vector_t]"; }
	void run (Array_type_t* t) override { std::cout << "[array_t]"; }
	void run (SharedPtr_type_t* t) override { std::cout << "[shared_ptr_t]"; }
	void run (UniquePtr_type_t* t) override { std::cout << "[unique_ptr_t]"; }
	void run (Map_type_t* t) override { std::cout << "[map_t]"; }
	void run (Atomic_type_t* t) override { std::cout << "[atomic_ref_t]"; }
	void run (Typename_t* t) override { std::cout << "[typename_t]"; }
	void run (TemplateKey_t* t) override { std::cout << "[template_key]"; }
	void run (EndType_t* t) override { std::cout << ":endType"; }
	void run (If_t* t) override {
		std::cout << " IF ";
	}
	void run (InCall_is_t* t) override {
		std::wcout << t->id->getId () << L":";
		t->expr->run (this);
	}
	void run (Else_t* t) override { std::cout << " ELSE "; }
	void run (Elif_t* t) override { std::cout << " ELIF "; }
	void run (While_t* t) override { std::cout << " WHILE "; }
	void run (Assign_t* t) override { std::cout << "="; }
	void run (Sword_t* t) override { std::cout << "-+"; }
	void run (Arrow_t* t) override { std::cout << "->"; }


	void run (struct TemplateCall_t* t) override {
		bool tr = true;
		std::wcout << '[' << t->id->getId () << "!<";
		for (auto& it : t->args) { if (tr) { tr = false; } else { std::cout << ", "; } it->run (this); }
		std::cout << ">]";
	}
	void run (struct OpenLambdaType_t* t) override { std::cout << "\\("; }
	void run (struct CloseLambdaType_t* t) override { std::cout << ")->"; }
	void run (struct LambdaType_t* t) override { std::cout << "\\()->"; }
	void run (struct In_t* t) override { std::cout << "in"; }

	~Spy2 () = default;
};

inline void printTokens_ (std::vector<std::shared_ptr<Token> >& tokens) {
	//Spy2 spy;
	//for (auto& it : tokens) it->run (&spy);
}

inline void printTokens (const char str[], std::vector<std::shared_ptr<Token> >& tokens, const char str2[]) {
	printf (str);
	printTokens_ (tokens);
	printf (str2);
}
#endif
