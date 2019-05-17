#ifndef TOKENS_H
#define TOKENS_H
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <map>

#include "cirstr.h"

//#include <llvm/ADT/APFloat.h>
//#include <llvm/IR/Constants.h>
//#include <llvm/IR/Function.h>
//#include <llvm/IR/IRBuilder.h>
//#include <llvm/IR/LLVMContext.h>
//#include <llvm/IR/Module.h>
//#include <llvm/IR/Type.h>
//#include <llvm/IR/Verifier.h>

const int gobho_int_size = 32;


//static llvm::LLVMContext TheContext;
//static llvm::IRBuilder<> Builder(TheContext);
//static std::unique_ptr<llvm::Module> TheModule;
//static std::map<std::wstring, llvm::Value *> NamedValues;

//llvm::Value *LogErrorV (const char *Str) {
//	std::wcerr << Str << L'\n';
//	return nullptr;
//}

// Possible tokens
enum class Tok {
	Dot,				// .
	Semicolon,	// ;
	Colon,			// :
	Assign,			// =
	Id,					// лол
	Argument,		// лол

	Lambda,			// ля
	Return,			// отдать
	If,					// при
	Else,				// иначе
	Elif,				// инапри
	Assert,			// утв
	Class,			// пусть
	Throw,			// кинь
	Try,				// пробуй
	Catch,			// лови
	For,				// для
	While,			// пока
	Ban,				// __запрет__
	Break,			// бряк
	Continue,		// дальше
	Const,			// конст
	Import,			// импорт
	As,					// как
	Empty,			// пусто
	Delete,			// удали

	Comma,			// ,
	String,			// "_
	EndString,	// _"
	Number,			// 42.0
	Int,				// -42
	Int_type,		// целое
	UInt,				// 42
	UInt_type,	// натуральное
	Float,			// 3.1415926535898
	Float_type,	// вещественное
	OpenParenthesis,	// (
	CloseParenthesis,	// )
	OpenBrackets,			// [
	CloseBrackets,		// ]
	OpenCurlyBrackets,// {
	CloseCurlyBrackets,//}
	Prototype,				// №
	Plus,				// +
	Increment,	// ++
	Multiply,		// *
	Minus,			// -
	UnMinus,
	Decrement,	// --
	Devide,			// /
	Power,			// **
	Mod,				// %
	Equal,			// ==
	NotEqual,		// !=
	nye,				// !
	Less,				// <
	More,				// >
	LessOrEqual,// <=
	MoreOrEqual,// >=

	Therefore,	// =>
	And,				// и
	Or,					// или
	Not,				// не

	Arrow,			// ->
	Space,
	OpenBody,
	CloseBody,
	Call,
	Body,
	IfStmt,
	LambdaDef,
	ClassDef,
	AssignOp,
	ArrayDef,
	ArrayCall,
	FieldCall,
	FieldDef,
	Stmt,
	Expr,
	startRep,
	endRep,
	mightBe,
	binop,
	unop,
	operation,
	loperation
};

struct Runner {
	virtual void run (struct UInt_t* t) = 0;
	virtual void run (struct Int_t* t) = 0;
	virtual void run (struct Float_t* t) = 0;
	virtual void run (struct String_t* t) = 0;
	virtual void run (struct Id_t* t) = 0;
	virtual void run (struct ArrayDef_t* t) = 0;
	virtual void run (struct Expr_t* t) = 0;
	virtual void run (struct Call_t* t) = 0;
	virtual void run (struct Space_t* t) = 0;
	virtual void run (struct binop_t* t) = 0;
	virtual void run (struct OpenParenthesis_t* t) = 0;
	virtual void run (struct CloseParenthesis_t* t) = 0;
	virtual void run (struct OpenBody_t* t) = 0;
	virtual void run (struct CloseBody_t* t) = 0;
	virtual void run (struct If_t* t) = 0;
	virtual void run (struct Else_t* t) = 0;
	virtual void run (struct Elif_t* t) = 0;
	virtual void run (struct Semicolon_t* t) = 0;
	virtual ~Runner () = default;
};

struct Token																		//	interface
{
	virtual Tok type () = 0;
	virtual ~Token () {}
	virtual std::wstring getId () {return L"";}
	virtual void setId (const std::wstring& str) {}
	virtual void setInt (const int val) {}
	virtual int getInt () {return 0;}
	virtual void setFloat (const float val) {}
	virtual float getFloat () {return 0.f;}
	virtual unsigned idx() {return column;}
	virtual unsigned getLine () {return line;}
	void setPos (const unsigned& line, const unsigned& column)
	{
		this->column = column;
		this->line = line;
	}
	//virtual llvm::Value* codegen() {return nullptr;}
	virtual void run (Runner* v) {}
protected:
	unsigned column;
	unsigned line;
};

static void pass (Token*t) {}


struct Expr_t : Token { Tok type () { return Tok::Expr; } std::shared_ptr<std::vector<std::shared_ptr<Token>>> l; void run (Runner* v) override { v->run (this); } };
struct Dot_t				: Token { Tok type () {return Tok::Dot;} };
struct Semicolon_t	: Token { Tok type () {return Tok::Semicolon;} void run (Runner* v) {v->run(this);} };
struct Colon_t			: Token { Tok type () {return Tok::Colon;} };
struct Equal_t			: Token { Tok type () {return Tok::Equal;} };
struct NotEqual_t		: Token { Tok type () {return Tok::NotEqual;} };
struct nye_t				: Token { Tok type () {return Tok::nye;} };
struct Assign_t			: Token { Tok type () {return Tok::Assign;} };
struct Lambda_t			: Token { Tok type () {return Tok::Lambda;} };
struct Return_t			: Token { Tok type () {return Tok::Return;} };
struct If_t					: Token { Tok type () {return Tok::If;} void run (Runner* v) {v->run(this);} };
struct Else_t				: Token { Tok type () {return Tok::Else;} void run (Runner* v) {v->run(this);} };
struct Elif_t				: Token { Tok type () {return Tok::Elif;} void run (Runner* v) {v->run(this);} };
struct Assert_t			: Token { Tok type () {return Tok::Assert;} };
struct Class_t			: Token { Tok type () {return Tok::Class;} };
struct Throw_t			: Token { Tok type () {return Tok::Throw;} };
struct Try_t				: Token { Tok type () {return Tok::Try;} };
struct Catch_t			: Token { Tok type () {return Tok::Catch;} };
struct For_t				: Token { Tok type () {return Tok::For;} };
struct While_t			: Token { Tok type () {return Tok::While;} };
struct Ban_t				: Token { Tok type () {return Tok::Ban;} };
struct Break_t			: Token { Tok type () {return Tok::Break;} };
struct Continue_t		: Token { Tok type () {return Tok::Continue;} };
struct Const_t			: Token { Tok type () {return Tok::Const;} };
struct Import_t			: Token { Tok type () {return Tok::Import;} };
struct As_t					: Token { Tok type () {return Tok::As;} };
struct Empty_t			: Token { Tok type () {return Tok::Empty;} };
struct Delete_t			: Token { Tok type () {return Tok::Delete;} };
struct Comma_t			: Token { Tok type () {return Tok::Comma;} };
struct EndString_t	: Token { Tok type () {return Tok::EndString;} };
struct Argument_t		: Token {
				Tok type () {return Tok::Argument;} std::wstring id;
				void setId (const std::wstring& str) {this->str = str;}
				std::wstring getId () {return str;}
private:
				std::wstring str;
};

struct Id_t					: Token {
				Tok type () {return Tok::Id;}
				void setId (const std::wstring& str) {
					std::wstring _str (str);
					this->str = cirToLat (_str);
				}
				std::wstring getId () { return latToCir (str); }
				void setStr (const std::string& str) { this->str = str; }
				std::string getStr () { return str; }
				//llvm::Value* codegen () { return nullptr; }
				void run (Runner* v) { v->run (this); }
private:
				std::string str;
};


struct String_t						: Token {
				Tok type () {return Tok::String;}
				void setId (const std::wstring& str){this->str = str;}
				std::wstring getId () {return str;}
				void run (Runner* v) { v->run (this); }
private:
				std::wstring str;
};


struct Number_t						: Token {
				Tok type () {return Tok::Number;}
				void setId (const std::wstring& str) { std::wstring _str(str); this->str = cirToLat (_str); }
				std::wstring getId () { return latToCir (str); }
				std::string getStr () { return str; }
private:
				std::string str;
};

struct Int_t							: Token {
				Tok type () {return Tok::Int;}
				void setInt (const int val) {this->val = val;}
				int getInt () {return val;}
				void run (Runner* v) { v->run (this); }
				//llvm::Value* codegen () { return llvm::ConstantInt::get (TheContext, llvm::APInt (gobho_int_size, this->val, true)); }
private:
				int val;
};

struct UInt_t							: Token {
				Tok type () {return Tok::UInt;}
				void setUInt (const unsigned val) {this->val = val;}
				float getUInt () {return val;}
				void run (Runner* v) { v->run (this); }
				//llvm::Value* codegen () { return llvm::ConstantInt::get (TheContext, llvm::APInt (gobho_int_size, this->val)); }
private:
				unsigned val;
};

struct Float_t							: Token {
				Tok type () {return Tok::Float;}
				void setFloat (const float val) {this->val = val;}
				float getFloat () {return val;}
				void run (Runner* v) { v->run (this); }
				//llvm::Value* codegen () { return llvm::ConstantFP::get (TheContext, llvm::APFloat (this->val)); }
private:
				float val;
};

struct ArrayDef_t							: Token {
	Tok type () {return Tok::ArrayDef;}
	std::vector<Expr_t> cells;
	void run (Runner* v) { v->run (this); }
};

struct Int_type_t					: Token { Tok type () {return Tok::Int_type;} };
struct UInt_type_t				: Token { Tok type () {return Tok::UInt_type;} };
struct Float_type_t				: Token { Tok type () {return Tok::Float_type;} };

struct OpenParenthesis_t	: Token { Tok type () {return Tok::OpenParenthesis;} void run (Runner* v) {v->run (this);} };
struct CloseParenthesis_t	: Token { Tok type () {return Tok::CloseParenthesis;} void run (Runner* v) {v->run (this);} };
struct OpenBrackets_t			: Token { Tok type () {return Tok::OpenBrackets;} };
struct CloseBrackets_t		: Token { Tok type () {return Tok::CloseBrackets;} };
struct OpenCurlyBrackets_t: Token { Tok type () {return Tok::OpenCurlyBrackets;} };
struct CloseCurlyBrackets_t:Token { Tok type () {return Tok::CloseCurlyBrackets;} };
struct Prototype_t				: Token { Tok type () {return Tok::Prototype;} };
struct Less_t							: Token { Tok type () {return Tok::Less;}};
struct More_t							: Token { Tok type () {return Tok::More;}};
struct LessOrEqual_t			: Token { Tok type () {return Tok::LessOrEqual;}};
struct MoreOrEqual_t			: Token { Tok type () {return Tok::MoreOrEqual;}};
struct Arrow_t						: Token { Tok type () {return Tok::Arrow;} };
struct Therefore_t				: Token { Tok type () {return Tok::Therefore;}};
struct And_t							: Token { Tok type () {return Tok::And;}};
struct Or_t								: Token { Tok type () {return Tok::Or;}};
struct Not_t							: Token { Tok type () {return Tok::Not;} std::shared_ptr<Token> right; };
struct Space_t						: Token { Tok type () {return Tok::Space;} void run (Runner* v) {v->run (this);} };
struct Stmt_t							: Token { Tok type () {return Tok::Stmt;} std::shared_ptr<std::vector<std::shared_ptr<Token>>> l; };
struct OpenBody_t				: Token { Tok type () {return Tok::OpenBody;} std::shared_ptr<std::vector<std::shared_ptr<Token>>> stmts; void run(Runner* v) {v->run (this);} };
struct CloseBody_t				: Token { Tok type () {return Tok::CloseBody;} void run(Runner* v) {v->run (this);}};
struct Call_t					: Token {
	Tok type () {return Tok::Call;}
	std::shared_ptr<Id_t> id;
	std::vector<std::shared_ptr<Token>> args;
	void run (Runner* v) { v->run (this); }
};
struct ArrayCall_t				: Token {
	Tok type () {return Tok::ArrayCall;}
	std::shared_ptr<Id_t> id;
	std::vector<std::shared_ptr<Token>> args;
};
struct Minus_t						: Token { Tok type () {return Tok::Minus;}};
struct UnMinus_t					: Token { Tok type () {return Tok::UnMinus;} std::shared_ptr<Token> right; };
struct Plus_t							: Token { Tok type () {return Tok::Plus;}};
struct Multiply_t					: Token { Tok type () {return Tok::Multiply;} };
struct Power_t						: Token { Tok type () {return Tok::Power;}};
struct Devide_t					: Token { Tok type () {return Tok::Devide;} };
struct Mod_t							: Token { Tok type () {return Tok::Mod;}};
struct Decrement_t				: Token { Tok type () {return Tok::Decrement;} std::shared_ptr<Token> right; };
struct Increment_t				: Token { Tok type () {return Tok::Increment;} std::shared_ptr<Token> right; };
struct binop_t						: Token { Tok type () {return Tok::binop;} Tok opType; std::shared_ptr<Token> left, right;
																		void run (Runner* v) { v->run (this); }
																		//llvm::Value* codegen() {
																			//llvm::Value* L = left->codegen();
																			//llvm::Value* R = right->codegen();
																			//if (opType == Tok::Multiply) return Builder.CreateFMul (L, R, "multmp");
																			//if (opType == Tok::Devide) return Builder.CreateFDiv (L, R, "divtmp");
																			//if (opType == Tok::Plus) return Builder.CreateFAdd (L, R, "addtmp");
																			//if (opType == Tok::Minus) return Builder.CreateFSub(L, R, "subtmp");
																			//if (opType == Tok::Mod) return Builder.CreateFDiv(L, Builder.CreateFRem(L, R,"remtmp"), "divtmp");
																			//if (opType == Tok::Less) return Builder.CreateUIToFP(Builder.CreateFCmpULT(L, R, "lmptmp"), llvm::Type::getDoubleTy(TheContext),"booltmp");
																			//if (opType == Tok::LessOrEqual) return Builder.CreateNot(Builder.CreateFCmpULT(L, R, "lmptmp"));
																			//return nullptr;
																		//}
																	};

struct FieldCall_t : Token { Tok type () { return Tok::FieldCall; } std::shared_ptr<Token> owner, id; };

struct FieldDef_t					: Token {
	Tok type() {return Tok::FieldDef;}
	std::map<std::shared_ptr<Id_t>, Expr_t> cells;
};

template <typename T>
std::shared_ptr<T> as(std::shared_ptr<Token> t) {return std::static_pointer_cast<T> (t);}

static std::vector<int> int_stk;
static std::map<std::string, int> int_vars;
static std::vector<float> float_stk;
static std::map<std::string, float> float_vars;

struct Spy : Runner {
	Spy () {}
	void run (UInt_t* t) override {}
	void run (Int_t* t) override { std::cout << "[i" << t->getInt () << "]"; }
	void run (Float_t* t) override { std::cout << "[f" << t->getFloat () << "]"; }
	void run (String_t* t) override {}
	void run (Expr_t* t) override { for (auto& it : *(t->l.get())) {it->run (this);} }
	void run (Call_t* t) override {
		bool tr = true;
		std::wcout << "[fCall " << t->id->getId () << '(';
		for (auto& it : t->args) { if (tr) { tr = false; } else { std::cout << ", "; } it->run (this); }
		std::cout << ")]" << std::endl;
	}

	void run (binop_t* t) {
		//std::cout << "AaAAaaA!!11\n";
		t->left->run(this);
		switch (t->opType) {
			case Tok::Plus: std::cout << '+'; break;
			case Tok::Minus: std::cout << '-'; break;
			case Tok::Devide: std::cout << '/'; break;
			case Tok::Multiply: std::cout << '*'; break;
			case Tok::Equal: std::cout << "=="; break;
			default: break;
		}
		t->right->run(this);
	}
	void run (Id_t* t) override { std::wcout << "\nId: " << t->getId () << "\n"; }
	void run (ArrayDef_t* t) override {
		bool tr = false;
		std::cout << "\n[(";
		for (auto& it : t->cells) {
			if (tr) { std::cout << ", "; }else { tr = true; } it.run (this);
		}
		std::cout << ")]";
	}
	void run (OpenParenthesis_t* t) override {std::cout <<" (:";}
	void run (CloseParenthesis_t* t) override {std::cout <<":) ";}
	void run (Space_t* t) override {std::cout <<"|";}
	void run (OpenBody_t* t) override {std::cout << " {:";}
	void run (CloseBody_t* t) override {std::cout << ":} ";}
	~Spy () = default;
};

struct Spy2 : Runner {
	Spy2 () {}
	void run (UInt_t* t) override {  }
	void run (Int_t* t) override { std::cout << "[i" << t->getInt () << "]"; }
	void run (Float_t* t) override { std::cout << "[f" << t->getFloat () << "]"; }
	void run (String_t* t) override { std::wcout << L"[s'" << t->getId () << L"']"; }
	void run (Expr_t* t) override { for (auto& it : *(t->l.get())) {it->run (this);} }
	void run (Call_t* t) override {

		bool tr = true;
		std::wcout << "[Call " << t->id->getId () << '(';
		for (auto& it : t->args) { if (tr) { tr = false; } else { std::cout << ", "; } it->run (this); }
		std::cout << ")]" << std::endl;

	}
	void run (binop_t* t) {
		t->left->run(this);
		switch (t->opType) {
			case Tok::Plus: std::cout << '+'; break;
			case Tok::Minus: std::cout << '-'; break;
			case Tok::Devide: std::cout << '/'; break;
			case Tok::Multiply: std::cout << '*'; break;
			case Tok::Equal: std::cout << "=="; break;
			default: break;
		}
		t->right->run(this);
	}
	void run (Id_t* t) override { std::wcout << "[Id: " << t->getId () << "]"; }
	void run (ArrayDef_t* t) override {
		bool tr = false;
		std::cout << "[m";
		for (auto& it : t->cells) {
			if (tr) { std::cout << ", "; }else { tr = true; } it.run (this);
		}
		std::cout << "]";
	}
	void run (OpenParenthesis_t* t) override {std::cout <<" (:";}
	void run (CloseParenthesis_t* t) override {std::cout <<":) ";}
	void run (Space_t* t) override {std::cout <<"_";}
	void run (Semicolon_t* t) override {std::cout << "|";}
	void run (OpenBody_t* t) override {std::cout << " {:";}
	void run (CloseBody_t* t) override {std::cout << ":} ";}
	void run (If_t* t) override {std::cout << " IF ";}
	void run (Else_t* t) override {std::cout << " ELSE ";}
	void run (Elif_t* t) override {std::cout << " ELIF ";}
	~Spy2 () = default;
};

#endif // TOKENS_H
