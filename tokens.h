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

// All Possible Tokens
enum class Tok {
	Dot,				// .
	Semicolon,	// ;
	Colon,			// :
	DoubleColon,	// ::
	Assign,			// =
	Id,					// лол
	Argument,		// лол

	Lambda,			// ля
	LambdaDef,
	Return,			// отдать
	If,					// при(){}
	Else,				// иначе(){}
	Elif,				// инапри(){}
	IfKey,				// при
	ElseKey,			// иначе
	ElifKey,			// инапри
	Assert,			// утв
	Let,			// пусть
	Throw,			// кинь
	Try,				// пробуй
	Catch,			// лови
	For,				// для(){}
	ForKey,				// для
	While,			// пока(){}
	WhileKey,		// пока
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
	String_type, // строка
	Number,			// 42.0
	Int,				// -42
	I16_type,
	I32_type,		// целое
	I64_type,
	UInt,				// 42
	U16_type,
	U32_type,	// натуральное
	U64_type,
	Float,			// 3.1415926535898
	F32_type,
	F64_type,	// вещественное
	OpenParenthesis,	// (
	CloseParenthesis,	// )
	OpenBrackets,			// [
	CloseBrackets,		// ]
	OpenCurlyBrackets,// {
	CloseCurlyBrackets,//}
	Reference,				// №
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
	Sword,			// -+ тип
	TypeComma,		// тип!(Т: тип TypeComma T2: тип) или typeLambda(тип TypeComma тип)
	StartType,		// : type
	EndType,		// : type endType ','/';'/'='
	DotInType,		// : type.type
	InCall_is,		// call(idx: 24) => call(InCall_is<idx, 24>)
	In,				// для x in range (1, 10) { ... } // для х из ряд (1, 10), ... ;
	Space,
	OpenBody,
	OpenBodyOfLambda,
	OpenLambdaType,
	CloseLambdaType,
	LambdaType,
	OpenTemplateType,
	CloseTemplateType,
	TemplateCall,
	CloseBody,
	Call,
	Body,
	IfStmt,
	ClassDef,
	AssignOp,
	ArrayDef,
	ArrayCall,
	Array_type,
	FieldCall,
	TypeFieldCall,
	FieldDef,
	Map_type,
	Vector_type,
	Atomic_type,
	SharedPtr_type,
	UniquePtr_type,
	TemplateKey,
	Typename,
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
	virtual void run (struct OpenBodyOfLambda_t* t) = 0;
	virtual void run (struct CloseBody_t* t) = 0;
	virtual void run (struct If_t* t) = 0;
	virtual void run (struct Else_t* t) = 0;
	virtual void run (struct Elif_t* t) = 0;
	virtual void run (struct While_t* t) = 0;
	virtual void run (struct Semicolon_t* t) = 0;
	virtual void run (struct Colon_t* t) = 0;
	virtual void run (struct DoubleColon_t* t) = 0;
	virtual void run (struct Lambda_t* t) = 0;
	virtual void run (struct LambdaDef_t* t) = 0;
	virtual void run (struct Dot_t* t) = 0;
	virtual void run (struct Assign_t* t) = 0;
	virtual void run (struct InCall_is_t* t) = 0;
	virtual void run (struct StartType_t* t) = 0;
	virtual void run (struct EndType_t* t) = 0;
	virtual void run (struct I16_type_t* t) = 0;
	virtual void run (struct I32_type_t* t) = 0;
	virtual void run (struct I64_type_t* t) = 0;
	virtual void run (struct U16_type_t* t) = 0;
	virtual void run (struct U32_type_t* t) = 0;
	virtual void run (struct U64_type_t* t) = 0;
	virtual void run (struct F32_type_t* t) = 0;
	virtual void run (struct F64_type_t* t) = 0;
	virtual void run (struct String_type_t* t) = 0;
	virtual void run (struct Array_type_t* t) = 0;
	virtual void run (struct Map_type_t* t) = 0;
	virtual void run (struct Atomic_type_t* t) = 0;
	virtual void run (struct Vector_type_t* t) = 0;
	virtual void run (struct SharedPtr_type_t* t) = 0;
	virtual void run (struct UniquePtr_type_t* t) = 0;
	virtual void run (struct TemplateKey_t* t) = 0;
	virtual void run (struct Typename_t* t) = 0;
	virtual void run (struct Sword_t* t) = 0;
	virtual void run (struct Arrow_t* t) = 0;
	virtual void run (struct TemplateCall_t* t) = 0;
	virtual void run (struct OpenLambdaType_t* t) = 0;
	virtual void run (struct CloseLambdaType_t* t) = 0;
	virtual void run (struct LambdaType_t* t) = 0;
	virtual void run (struct In_t* t) = 0;
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
	virtual size_t idx() {return column;}
	virtual size_t getLine () {return line;}
	void setPos (const size_t& line, const size_t& column)
	{
		this->column = column;
		this->line = line;
	}
	//virtual llvm::Value* codegen() {return nullptr;}
	virtual void run (Runner* v) {}
protected:
	size_t column;
	size_t line;
};

static void pass (Token*t) {}

#define RUNNER_METHOD void run (Runner* v) override {v->run (this);}

struct Expr_t 			: Token { RUNNER_METHOD Tok type () {return Tok::Expr;} std::shared_ptr<std::vector<std::shared_ptr<Token>>> l; };
struct Dot_t			: Token { RUNNER_METHOD Tok type () {return Tok::Dot;} };
struct Semicolon_t		: Token { RUNNER_METHOD Tok type () {return Tok::Semicolon;} };
struct Colon_t			: Token { RUNNER_METHOD Tok type () {return Tok::Colon;} };
struct DoubleColon_t	: Token { RUNNER_METHOD Tok type () {return Tok::DoubleColon;} };
struct Equal_t			: Token { Tok type () {return Tok::Equal;} };
struct NotEqual_t		: Token { Tok type () {return Tok::NotEqual;} };
struct nye_t			: Token { Tok type () {return Tok::nye;} };
struct Assign_t			: Token { RUNNER_METHOD Tok type () {return Tok::Assign;} };
struct Lambda_t			: Token { RUNNER_METHOD Tok type () {return Tok::Lambda;} };
struct Return_t			: Token { Tok type () {return Tok::Return;} std::shared_ptr<std::vector<std::shared_ptr<Token> > > l{nullptr}; };
struct In_t				: Token { RUNNER_METHOD Tok type () {return Tok::In;} };
struct OpenLambdaType_t : Token { RUNNER_METHOD Tok type () {return Tok::OpenLambdaType;} };
struct CloseLambdaType_t: Token { RUNNER_METHOD Tok type () {return Tok::CloseLambdaType;} };
struct LambdaType_t		: Token { RUNNER_METHOD Tok type () { return Tok::LambdaType; }
	std::vector<std::shared_ptr<Token> > args; // types of args
	std::shared_ptr<Token> ret; // type of ret values
};
struct OpenTemplateType_t	: Token { Tok type () { return Tok::OpenTemplateType; } };
struct CloseTemplateType_t	: Token { Tok type () { return Tok::CloseTemplateType; } };
struct TemplateCall_t	: Token { RUNNER_METHOD Tok type () { return Tok::TemplateCall; }
	std::shared_ptr<Id_t> id;
	std::vector<std::shared_ptr<Token>> args;
};
struct LambdaDef_t		: Token { RUNNER_METHOD Tok type () {return Tok::LambdaDef;}
	std::shared_ptr<Token> body;
	std::vector<std::pair<std::shared_ptr<Token>, std::shared_ptr<Token> > > args;
	std::shared_ptr<Token> ret_type;
};
struct IfKey_t : Token {
	Tok type () { return Tok::IfKey; }
};
struct ElifKey_t : Token {
	Tok type () { return Tok::ElifKey; }
};
struct ElseKey_t : Token {
	Tok type () { return Tok::ElseKey; }
};
struct If_t				: Token { RUNNER_METHOD Tok type () {return Tok::If;}
	std::shared_ptr<struct Expr_t> condition{nullptr};
	std::shared_ptr<Token> body{nullptr}, alternative{nullptr};
};
struct Elif_t			: Token { RUNNER_METHOD Tok type () {return Tok::Elif;}
	std::shared_ptr<struct Expr_t> condition{nullptr};
	std::shared_ptr<Token> body{nullptr}, alternative{nullptr};
};
struct Else_t			: Token { RUNNER_METHOD Tok type () {return Tok::Else;}
	#ifdef __unix__
	std::shared_ptr<struct Expr_t> condition{nullptr};
	#endif
	std::shared_ptr<Token> body{nullptr}, alternative{nullptr};
};
struct Assert_t			: Token { Tok type () {return Tok::Assert;} };
struct Let_t			: Token { Tok type () {return Tok::Let;} };
struct Throw_t			: Token { Tok type () {return Tok::Throw;} };
struct Try_t			: Token { Tok type () {return Tok::Try;} };
struct Catch_t			: Token { Tok type () {return Tok::Catch;} };
struct ForKey_t : Token { Tok type () { return Tok::ForKey; } };
struct For_t			: Token { Tok type () {return Tok::For;} };
struct WhileKey_t : Token { Tok type () { return Tok::WhileKey; } };
struct While_t			: Token { RUNNER_METHOD Tok type () {return Tok::While;}
	std::shared_ptr<struct Expr_t> condition{nullptr};
	std::shared_ptr<Token> body{nullptr};
	#ifdef __unix__
	std::shared_ptr<Token> alternative{nullptr};
	#endif
};
struct Ban_t			: Token { Tok type () {return Tok::Ban;} };
struct Break_t			: Token { Tok type () {return Tok::Break;} };
struct Continue_t		: Token { Tok type () {return Tok::Continue;} };
struct Const_t			: Token { Tok type () {return Tok::Const;} };
struct Import_t			: Token { Tok type () {return Tok::Import;} };
struct As_t				: Token { Tok type () {return Tok::As;} };
struct Empty_t			: Token { Tok type () {return Tok::Empty;} };
struct Delete_t			: Token { Tok type () {return Tok::Delete;} };
struct Comma_t			: Token { Tok type () {return Tok::Comma;} };
struct TypeComma_t		: Token { Tok type () {return Tok::TypeComma;} };
struct EndString_t		: Token { Tok type () {return Tok::EndString;} };
struct Argument_t		: Token {
				Tok type () {return Tok::Argument;} std::wstring id;
				void setId (const std::wstring& str) {this->str = str;}
				std::wstring getId () {return str;}
private:
				std::wstring str;
};

struct Id_t					: Token { RUNNER_METHOD Tok type () {return Tok::Id;}
				void setId (const std::wstring& str) {
					std::wstring _str (str);
					this->str = cirToLat (_str);
				}
				std::wstring getId () { return latToCir (str); }
				void setStr (const std::string& str) { this->str = str; }
				std::string getStr () { return str; }
private:
				std::string str;
};


struct String_t						: Token { RUNNER_METHOD Tok type () {return Tok::String;}
				void setId (const std::wstring& str){this->str = str;}
				std::wstring getId () {return str;}
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

struct Int_t							: Token { RUNNER_METHOD Tok type () {return Tok::Int;}
				void setInt (const int val) {this->val = val;}
				int getInt () {return val;}
private:
				int val;
};

struct UInt_t							: Token { RUNNER_METHOD Tok type () {return Tok::UInt;}
				void setUInt (const unsigned val) {this->val = val;}
				float getUInt () {return val;}
private:
				unsigned val;
};

struct Float_t							: Token { RUNNER_METHOD Tok type () {return Tok::Float;}
				void setFloat (const float val) {this->val = val;}
				float getFloat () {return val;}
private:
				float val;
};

struct ArrayDef_t							: Token { RUNNER_METHOD Tok type () {return Tok::ArrayDef;} std::vector<Expr_t> cells; };

struct I16_type_t : Token { RUNNER_METHOD Tok type () { return Tok::I16_type; } };
struct I32_type_t : Token { RUNNER_METHOD Tok type () { return Tok::I32_type; } };
struct I64_type_t : Token { RUNNER_METHOD Tok type () { return Tok::I64_type; } };
struct U16_type_t : Token { RUNNER_METHOD Tok type () { return Tok::U16_type; } };
struct U32_type_t : Token { RUNNER_METHOD Tok type () { return Tok::U32_type; } };
struct U64_type_t : Token { RUNNER_METHOD Tok type () { return Tok::U64_type; } };
struct F32_type_t : Token { RUNNER_METHOD Tok type () { return Tok::F32_type; } };
struct F64_type_t : Token { RUNNER_METHOD Tok type () { return Tok::F64_type; } };
struct String_type_t : Token { RUNNER_METHOD Tok type () { return Tok::String_type; } };
struct Vector_type_t : Token { RUNNER_METHOD Tok type () { return Tok::String_type; } };
struct TemplateKey_t : Token { RUNNER_METHOD Tok type () { return Tok::TemplateKey; } };
struct Array_type_t : Token { RUNNER_METHOD Tok type () { return Tok::Array_type; } };
struct Map_type_t : Token { Tok type () { return Tok::Map_type; } void run (Runner* v) { v->run (this); } };
struct Atomic_type_t : Token { Tok type () { return Tok::Atomic_type; } void run (Runner* v) { v->run (this); } };
struct SharedPtr_type_t : Token { Tok type () { return Tok::SharedPtr_type; } void run (Runner* v) { v->run (this); } };
struct UniquePtr_type_t : Token { Tok type () { return Tok::UniquePtr_type; } void run (Runner* v) { v->run (this); } };
struct Typename_t : Token { Tok type () { return Tok::Typename; } void run (Runner* v) { v->run (this); } };
struct OpenParenthesis_t		: Token { Tok type () {return Tok::OpenParenthesis;} void run (Runner* v) {v->run (this);} };
struct CloseParenthesis_t		: Token { Tok type () {return Tok::CloseParenthesis;} void run (Runner* v) {v->run (this);} };
struct OpenBrackets_t			: Token { Tok type () {return Tok::OpenBrackets;} };
struct CloseBrackets_t			: Token { Tok type () {return Tok::CloseBrackets;} };
struct OpenCurlyBrackets_t		: Token { Tok type () {return Tok::OpenCurlyBrackets;} };
struct CloseCurlyBrackets_t		: Token { Tok type () {return Tok::CloseCurlyBrackets;} };
struct Reference_t				: Token { Tok type () {return Tok::Reference;} };
struct Less_t					: Token { Tok type () {return Tok::Less;}};
struct More_t					: Token { Tok type () {return Tok::More;}};
struct LessOrEqual_t			: Token { Tok type () {return Tok::LessOrEqual;}};
struct MoreOrEqual_t			: Token { Tok type () {return Tok::MoreOrEqual;}};
struct Arrow_t					: Token { Tok type () {return Tok::Arrow;} void run (Runner* v){v->run(this);} };
struct Sword_t					: Token { Tok type () {return Tok::Sword;} void run (Runner* v){v->run(this);} };
struct StartType_t				: Token { Tok type () {return Tok::StartType;} void run (Runner* v){v->run(this);} };
struct EndType_t				: Token { Tok type () {return Tok::EndType;} void run (Runner* v) {v->run (this);} };
struct DotInType_t				: Token { Tok type () {return Tok::DotInType;} };
// foo(arg: 12) => foo(InCall_is<arg, 12>)
struct InCall_is_t : Token {
	Tok type () { return Tok::InCall_is; }
	std::shared_ptr<Token> id, expr;
	void run (Runner* v) { v->run (this); }
};
struct Therefore_t				: Token { Tok type () {return Tok::Therefore;}};
struct And_t							: Token { Tok type () {return Tok::And;}};
struct Or_t								: Token { Tok type () {return Tok::Or;}};
struct Not_t							: Token { Tok type () {return Tok::Not;} std::shared_ptr<Token> right; };
struct Space_t						: Token { Tok type () {return Tok::Space;} void run (Runner* v) {v->run (this);} };
struct Stmt_t							: Token { Tok type () {return Tok::Stmt;} std::shared_ptr<std::vector<std::shared_ptr<Token>>> l; };
struct OpenBody_t				: Token { Tok type () {return Tok::OpenBody;} std::shared_ptr<std::vector<std::shared_ptr<Token>>> stmts; void run(Runner* v) {v->run (this);} };
struct OpenBodyOfLambda_t		: Token { Tok type () {return Tok::OpenBodyOfLambda;} void run(Runner* v) {v->run (this);} };
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
struct Minus_t					: Token { Tok type () {return Tok::Minus;}};
struct UnMinus_t				: Token { Tok type () {return Tok::UnMinus;} std::shared_ptr<Token> right; };
struct Plus_t					: Token { Tok type () {return Tok::Plus;}};
struct Multiply_t				: Token { Tok type () {return Tok::Multiply;} };
struct Power_t					: Token { Tok type () {return Tok::Power;}};
struct Devide_t					: Token { Tok type () {return Tok::Devide;} };
struct Mod_t					: Token { Tok type () {return Tok::Mod;}};
struct Decrement_t				: Token { Tok type () {return Tok::Decrement;} std::shared_ptr<Token> right; };
struct Increment_t				: Token { Tok type () {return Tok::Increment;} std::shared_ptr<Token> right; };
struct binop_t					: Token { Tok type () {return Tok::binop;} Tok opType; std::shared_ptr<Token> left, right; void run (Runner* v) { v->run (this); }};

struct FieldCall_t : Token { Tok type () { return Tok::FieldCall; } std::shared_ptr<Token> owner, id; };
struct TypeFieldCall_t : Token { Tok type () { return Tok::TypeFieldCall; } std::shared_ptr<Token> owner, id; };

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
	void run (OpenBodyOfLambda_t* t) override {std::cout << " {l:";}
	void run (CloseBody_t* t) override {std::cout << ":} ";}
	void run (LambdaDef_t* t) override {std::cout << "[lambda]";}
	void run (StartType_t* t) override {std::cout << "type:";}
	~Spy () = default;
};



struct Spy2 : Runner {
	Spy2 () {}
	void run (UInt_t* t) override {  }
	void run (Int_t* t) override { std::cout << "[i" << t->getInt () << "]"; }
	void run (Float_t* t) override { std::cout << "[f" << t->getFloat () << "]"; }
	void run (String_t* t) override { std::wcout << L"[s'" << t->getId () << L"']"; }
	void run (Expr_t* t) override {
		for (auto& it : *(t->l.get())) {it->run (this);}
	}
	void run (Call_t* t) override {
		bool tr = true;
		std::wcout << "[Call " << t->id->getId () << '(';
		for (auto& it : t->args) { if (tr) { tr = false; } else { std::cout << ", "; } it->run (this); }
		std::cout << ")]";
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
	void run (Dot_t* t) override {std::cout <<".";}
	void run (Lambda_t* t) override {std::cout <<"\\";}
	void run (Semicolon_t* t) override {std::cout << "|";}
	void run (Colon_t* t) override { std::cout << "is"; }
	void run (DoubleColon_t* t) override { std::cout << "::"; }
	void run (OpenBody_t* t) override {std::cout << " {:";}
	void run (OpenBodyOfLambda_t* t) override {std::cout << " {:";}
	void run (CloseBody_t* t) override {std::cout << ":} ";}
	void run (LambdaDef_t* t) override {
		std::cout << "[lambda"<< t->args.size () <<"(";
		bool f = true;
		for (auto& it : t->args) {
			if (!f) std::cout << ",";
			else f = false;
			it.second->run (this);
			std::cout << ":";
			if (it.first.get () != nullptr) it.first->run (this);
		}
		std::cout << ")";
		if (t -> ret_type.get () != nullptr) {
			std::cout << "->";
			t -> ret_type -> run (this);
		}
		std::cout << ":";
		t->body->run ( this );
		std::cout << "]";
	}
	void run (StartType_t* t) override {std::cout << "type:";}
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
	void run (EndType_t* t) override {std::cout << ":endType";}
	void run (If_t* t) override {
		std::cout << " IF ";
	}
	void run (InCall_is_t* t) override {
		std::wcout << t->id->getId () << L":";
		t->expr->run (this);
	}
	void run (Else_t* t) override {std::cout << " ELSE ";}
	void run (Elif_t* t) override {std::cout << " ELIF ";}
	void run (While_t* t) override {std::cout << " WHILE ";}
	void run (Assign_t* t) override {std::cout << "=";}
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
	Spy2 spy;
	for (auto& it : tokens) it->run (&spy);
}

inline void printTokens (const char str[], std::vector<std::shared_ptr<Token> >& tokens, const char str2[]) {
	printf (str);
	printTokens_ (tokens);
	printf (str2);
}

#endif // TOKENS_H
