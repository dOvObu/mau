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

struct Expr_t 			   : Token { RUNNER_METHOD Tok type () {return Tok::Expr;} std::shared_ptr<std::vector<std::shared_ptr<Token>>> l; };
struct Dot_t			   : Token { RUNNER_METHOD Tok type () {return Tok::Dot;} };
struct Semicolon_t		   : Token { RUNNER_METHOD Tok type () {return Tok::Semicolon;} };
struct Colon_t			   : Token { RUNNER_METHOD Tok type () {return Tok::Colon;} };
struct DoubleColon_t	   : Token { RUNNER_METHOD Tok type () {return Tok::DoubleColon;} };
struct Assign_t			   : Token { RUNNER_METHOD Tok type () {return Tok::Assign;} };
struct Lambda_t			   : Token { RUNNER_METHOD Tok type () {return Tok::Lambda;} };
struct In_t				   : Token { RUNNER_METHOD Tok type () {return Tok::In;} };
struct OpenLambdaType_t    : Token { RUNNER_METHOD Tok type () {return Tok::OpenLambdaType;} };
struct CloseLambdaType_t   : Token { RUNNER_METHOD Tok type () {return Tok::CloseLambdaType;} };
struct ArrayDef_t          : Token { RUNNER_METHOD Tok type () {return Tok::ArrayDef;} std::vector<Expr_t> cells; };
struct I16_type_t          : Token { RUNNER_METHOD Tok type () {return Tok::I16_type; } };
struct I32_type_t          : Token { RUNNER_METHOD Tok type () {return Tok::I32_type; } };
struct I64_type_t          : Token { RUNNER_METHOD Tok type () {return Tok::I64_type; } };
struct U16_type_t          : Token { RUNNER_METHOD Tok type () {return Tok::U16_type; } };
struct U32_type_t          : Token { RUNNER_METHOD Tok type () {return Tok::U32_type; } };
struct U64_type_t          : Token { RUNNER_METHOD Tok type () {return Tok::U64_type; } };
struct F32_type_t          : Token { RUNNER_METHOD Tok type () {return Tok::F32_type; } };
struct F64_type_t          : Token { RUNNER_METHOD Tok type () {return Tok::F64_type; } };
struct String_type_t       : Token { RUNNER_METHOD Tok type () {return Tok::String_type; } };
struct Vector_type_t       : Token { RUNNER_METHOD Tok type () {return Tok::String_type; } };
struct TemplateKey_t       : Token { RUNNER_METHOD Tok type () {return Tok::TemplateKey; } };
struct Array_type_t        : Token { RUNNER_METHOD Tok type () {return Tok::Array_type; } };
struct Map_type_t          : Token { RUNNER_METHOD Tok type () {return Tok::Map_type; } };
struct Atomic_type_t       : Token { RUNNER_METHOD Tok type () {return Tok::Atomic_type; } };
struct SharedPtr_type_t    : Token { RUNNER_METHOD Tok type () {return Tok::SharedPtr_type; } };
struct UniquePtr_type_t    : Token { RUNNER_METHOD Tok type () {return Tok::UniquePtr_type; } };
struct Typename_t          : Token { RUNNER_METHOD Tok type () {return Tok::Typename; } };
struct OpenParenthesis_t   : Token { RUNNER_METHOD Tok type () {return Tok::OpenParenthesis;} };
struct CloseParenthesis_t  : Token { RUNNER_METHOD Tok type () {return Tok::CloseParenthesis;} };
struct Arrow_t             : Token { RUNNER_METHOD Tok type () {return Tok::Arrow;} };
struct Sword_t             : Token { RUNNER_METHOD Tok type () {return Tok::Sword;} };
struct StartType_t         : Token { RUNNER_METHOD Tok type () {return Tok::StartType;} };
struct EndType_t           : Token { RUNNER_METHOD Tok type () {return Tok::EndType; } };
struct InCall_is_t         : Token { RUNNER_METHOD Tok type () {return Tok::InCall_is; } std::shared_ptr<Token> id, expr;};
struct Space_t             : Token { RUNNER_METHOD Tok type () {return Tok::Space;} };
struct OpenBody_t          : Token { RUNNER_METHOD Tok type () {return Tok::OpenBody;} std::shared_ptr<std::vector<std::shared_ptr<Token>>> stmts; };
struct OpenBodyOfLambda_t  : Token { RUNNER_METHOD Tok type () {return Tok::OpenBodyOfLambda;} };
struct CloseBody_t         : Token { RUNNER_METHOD Tok type () {return Tok::CloseBody;} };
struct binop_t             : Token { RUNNER_METHOD Tok type () {return Tok::binop;} Tok opType; std::shared_ptr<Token> left, right; };

struct Equal_t              : Token { Tok type () {return Tok::Equal;} };
struct NotEqual_t           : Token { Tok type () {return Tok::NotEqual;} };
struct nye_t                : Token { Tok type () {return Tok::nye;} };
struct OpenTemplateType_t   : Token { Tok type () {return Tok::OpenTemplateType;} };
struct CloseTemplateType_t  : Token { Tok type () {return Tok::CloseTemplateType;} };
struct IfKey_t              : Token { Tok type () {return Tok::IfKey;} };
struct ElifKey_t            : Token { Tok type () {return Tok::ElifKey;} };
struct ElseKey_t            : Token { Tok type () {return Tok::ElseKey;} };
struct Assert_t             : Token { Tok type () {return Tok::Assert;} };
struct Let_t                : Token { Tok type () {return Tok::Let;} };
struct Throw_t              : Token { Tok type () {return Tok::Throw;} };
struct Try_t                : Token { Tok type () {return Tok::Try;} };
struct Catch_t              : Token { Tok type () {return Tok::Catch;} };
struct ForKey_t             : Token { Tok type () {return Tok::ForKey; } };
struct For_t                : Token { Tok type () {return Tok::For;} };
struct WhileKey_t           : Token { Tok type () {return Tok::WhileKey; } };
struct Ban_t                : Token { Tok type () {return Tok::Ban;} };
struct Break_t              : Token { Tok type () {return Tok::Break;} };
struct Continue_t           : Token { Tok type () {return Tok::Continue;} };
struct Const_t              : Token { Tok type () {return Tok::Const;} };
struct Import_t             : Token { Tok type () {return Tok::Import;} };
struct As_t                 : Token { Tok type () {return Tok::As;} };
struct Empty_t              : Token { Tok type () {return Tok::Empty;} };
struct Delete_t             : Token { Tok type () {return Tok::Delete;} };
struct Comma_t              : Token { Tok type () {return Tok::Comma;} };
struct TypeComma_t          : Token { Tok type () {return Tok::TypeComma;} };
struct EndString_t          : Token { Tok type () {return Tok::EndString;} };
struct OpenBrackets_t       : Token { Tok type () {return Tok::OpenBrackets; } };
struct CloseBrackets_t      : Token { Tok type () {return Tok::CloseBrackets; } };
struct OpenCurlyBrackets_t  : Token { Tok type () {return Tok::OpenCurlyBrackets; } };
struct CloseCurlyBrackets_t : Token { Tok type () {return Tok::CloseCurlyBrackets; } };
struct Reference_t          : Token { Tok type () {return Tok::Reference; } };
struct Less_t               : Token { Tok type () {return Tok::Less; } };
struct More_t               : Token { Tok type () {return Tok::More; } };
struct LessOrEqual_t        : Token { Tok type () {return Tok::LessOrEqual; } };
struct MoreOrEqual_t        : Token { Tok type () {return Tok::MoreOrEqual; } };
struct DotInType_t          : Token { Tok type () {return Tok::DotInType; } };
struct Therefore_t          : Token { Tok type () {return Tok::Therefore; } };
struct And_t                : Token { Tok type () {return Tok::And; } };
struct Or_t                 : Token { Tok type () {return Tok::Or; } };
struct Return_t	            : Token { Tok type () {return Tok::Return;} std::shared_ptr<std::vector<std::shared_ptr<Token> > > l{nullptr}; };

struct LambdaType_t : Token { RUNNER_METHOD Tok type () { return Tok::LambdaType; } // ...
	std::vector<std::shared_ptr<Token> > args; // types of args
	std::shared_ptr<Token> ret; // type of ret values
};
struct TemplateCall_t : Token { RUNNER_METHOD Tok type () { return Tok::TemplateCall; } // ...
	std::shared_ptr<Id_t> id;
	std::vector<std::shared_ptr<Token>> args;
};
struct LambdaDef_t : Token { RUNNER_METHOD Tok type () {return Tok::LambdaDef;} // ...
	std::shared_ptr<Token> body;
	std::vector<std::pair<std::shared_ptr<Token>, std::shared_ptr<Token> > > args;
	std::shared_ptr<Token> ret_type;
};
struct If_t : Token { RUNNER_METHOD Tok type () {return Tok::If;} // ...
	std::shared_ptr<struct Expr_t> condition{nullptr};
	std::shared_ptr<Token> body{nullptr}, alternative{nullptr};
};
struct Elif_t : Token { RUNNER_METHOD Tok type () {return Tok::Elif;} // ...
	std::shared_ptr<struct Expr_t> condition{nullptr};
	std::shared_ptr<Token> body{nullptr}, alternative{nullptr};
};
struct Else_t : Token { RUNNER_METHOD Tok type () {return Tok::Else;} // ...
	std::shared_ptr<Token> body{nullptr}, alternative{nullptr};
	#ifdef __unix__
	std::shared_ptr<struct Expr_t> condition{nullptr};
	#endif
};
struct While_t : Token { RUNNER_METHOD Tok type () {return Tok::While;} // ...
	std::shared_ptr<struct Expr_t> condition{nullptr};
	std::shared_ptr<Token> body{nullptr};
	#ifdef __unix__
	std::shared_ptr<Token> alternative{nullptr};
	#endif
};

struct Id_t : Token { RUNNER_METHOD Tok type () {return Tok::Id;} // ...
	void setId (const std::wstring& str) {
		this->str = cirToLat (str);
	}
	std::wstring getId () { return latToCir (str); }
	void setStr (const std::string& str) { this->str = str; }
	std::string getStr () { return str; }
private:
	std::string str;
};

struct String_t : Token { RUNNER_METHOD Tok type () {return Tok::String;} // ...
	void setId (const std::wstring& str){this->str = str;}
	std::wstring getId () {return str;}
private:
	std::wstring str;
};

struct Int_t : Token { RUNNER_METHOD Tok type () {return Tok::Int;} // ...
	void setInt (const int val) {this->val = val;}
	int getInt () {return val;}
private:
	int val;
};

struct UInt_t : Token { RUNNER_METHOD Tok type () {return Tok::UInt;} // ...
	void setUInt (const unsigned val) {this->val = val;}
	unsigned getUInt () {return val;}
private:
	unsigned val;
};

struct Float_t : Token { RUNNER_METHOD Tok type () {return Tok::Float;} // ...
	void setFloat (const float val) {this->val = val;}
	float getFloat () {return val;}
private:
	float val;
};


struct Argument_t : Token {
	Tok type () { return Tok::Argument; } std::wstring id;
	void setId (const std::wstring& str) { this->str = str; }
	std::wstring getId () { return str; }
private:
	std::wstring str;
};

struct Number_t : Token {
	Tok type () { return Tok::Number; }
	void setId (const std::wstring& str) { this->str = cirToLat (str); }
	std::wstring getId () { return latToCir (str); }
	std::string getStr () { return str; }
private:
	std::string str;
};

struct Not_t                : Token { Tok type () {return Tok::Not;} std::shared_ptr<Token> right; };
struct Stmt_t               : Token { Tok type () {return Tok::Stmt;} std::shared_ptr<std::vector<std::shared_ptr<Token>>> l; };

struct Call_t               : Token { RUNNER_METHOD Tok type () {return Tok::Call;} // ... 
	std::shared_ptr<Id_t> id;
	std::vector<std::shared_ptr<Token>> args;
};
struct ArrayCall_t          : Token {
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

struct FieldCall_t : Token { Tok type () { return Tok::FieldCall; } std::shared_ptr<Token> owner, id; };
struct TypeFieldCall_t : Token { Tok type () { return Tok::TypeFieldCall; } std::shared_ptr<Token> owner, id; };

struct FieldDef_t					: Token {
	Tok type() {return Tok::FieldDef;}
	std::map<std::shared_ptr<Id_t>, Expr_t> cells;
};

#undef RUNNER_METHOD


template <typename T>
std::shared_ptr<T> as(std::shared_ptr<Token> t) {return std::static_pointer_cast<T> (t);}

static std::vector<int> int_stk;
static std::map<std::string, int> int_vars;
static std::vector<float> float_stk;
static std::map<std::string, float> float_vars;

//=======================================================//
//--------------- VISITORS STARTS HERE -----------------//
//=====================================================//

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

template<typename T>
struct Tree {
	Tree (const T& data): node(new T(data)) {}
	Tree () = default;
	~Tree () = default;

	Tree<T>* AddChild(const T& data) {
		childs.push_back (std::make_unique<Tree<T> > (data));
		childs.back ()->parent = this;
		return childs.back ().get ();
	}
	void Clear () {
		node.reset (nullptr);
		childs.clear ();
	}
	Tree<T>* SetData (const T& data) { node.reset (new T (data)); return this; }
	T& GetData () { return *node; }
	std::vector<std::unique_ptr<Tree<T>>>& GetChilds () { return childs; }

private:
	std::unique_ptr<T> node{nullptr};
	std::vector<std::unique_ptr<Tree<T>>> childs;
	Tree* parent{nullptr};
};



struct Spy3 : Runner {
	Spy3 () {
		stringTree.SetData (L"root");
		nodeStack.push_back (&stringTree);
	}
private:
	Tree<std::wstring> stringTree;
	std::vector<Tree<std::wstring>*> nodeStack;
	void AddChildNode (std::wstring&& str) {
		nodeStack.back ()->AddChild (str);
	}
	void PushBackChildNode (std::wstring&& str) {
		nodeStack.push_back (nodeStack.back()->AddChild (str));
	}
	void PopBackChildNode () {
		nodeStack.pop_back ();
	}
public:
	Tree<std::wstring>& GetTree () { return stringTree; }

	void Clear () {
		stringTree.Clear ();
		stringTree.SetData (L"root");
		nodeStack.clear ();
		nodeStack.push_back (&stringTree);
	}
	void run (UInt_t* t) override {AddChildNode (L"const "+std::to_wstring(t->getUInt())+L" : unsigned int");}
	void run (Int_t* t) override {AddChildNode (L"const " + std::to_wstring(t->getInt ())+L" : int"); }
	void run (Float_t* t) override {AddChildNode (L"const " + std::to_wstring(t->getFloat ())+L" : float"); }
	void run (String_t* t) override {AddChildNode (L"const '" + t->getId () + L"' : string"); }
	void run (Expr_t* t) override {
		PushBackChildNode (L"Expression:");
		for (auto& it : *(t->l.get ())) {
			it->run (this);
		}
		PopBackChildNode ();
	}
	void run (Call_t* t) override {
		PushBackChildNode (L"Call " + t->id->getId () + L" function");
		PushBackChildNode (L"arguments [" + std::to_wstring(t->args.size())+L"]");
		for (auto& it : t->args) {
			it->run (this);
		}
		PopBackChildNode ();
		PopBackChildNode ();
	}
	void run (binop_t* t) {
		switch (t->opType) {
		case Tok::Plus: PushBackChildNode (L"+"); break;
		case Tok::Minus: PushBackChildNode (L"-"); break;
		case Tok::Devide: PushBackChildNode (L"/"); break;
		case Tok::Multiply: PushBackChildNode (L"*"); break;
		case Tok::Equal: PushBackChildNode (L"=="); break;
		default: break;
		}
		PushBackChildNode (L"left");
		t->left->run (this);
		PopBackChildNode ();

		PushBackChildNode (L"right");
		t->right->run (this);
		PopBackChildNode ();

		PopBackChildNode ();
	}
	void run (Id_t* t) override {AddChildNode (L"Id: " + t->getId ());}
	void run (ArrayDef_t* t) override {
		PushBackChildNode (L"Array[" + std::to_wstring (t->cells.size ()) + L']');
		for (auto& it : t->cells) {
			it.run (this);
		}
		PopBackChildNode ();
	}
	void run (OpenParenthesis_t* t) override {AddChildNode (L"(");}
	void run (CloseParenthesis_t* t) override {AddChildNode (L")");}
	void run (Space_t* t) override {AddChildNode (L"<white space( )>");}
	void run (Dot_t* t) override {AddChildNode (L"<dot(.)>");}
	void run (Lambda_t* t) override {AddChildNode (L"<lambda(\\)>");}
	void run (Semicolon_t* t) override {AddChildNode (L"<semicolon(;)>");}
	void run (Colon_t* t) override {AddChildNode (L"<colon(:)>");}
	void run (DoubleColon_t* t) override {AddChildNode (L"<double colon(::)>");}
	void run (OpenBody_t* t) override {AddChildNode (L"<open body>");}
	void run (OpenBodyOfLambda_t* t) override {AddChildNode (L"<open body of lambda>");}
	void run (CloseBody_t* t) override {AddChildNode (L"<close body>");}
	void run (LambdaDef_t* t) override {
		PushBackChildNode (L"Lambda def");
		PushBackChildNode (L"Arguments [" + std::to_wstring(t->args.size()) + L"]");
		bool f = true;
		{
			size_t i = 0;
			for (auto& it : t->args) {
				PushBackChildNode (L"Arg (" + std::to_wstring(i++) + L")");
				it.second->run (this);
				if (it.first.get () != nullptr) it.first->run (this);
				else AddChildNode (L"Any type");
				PopBackChildNode ();
			}
		}
		PopBackChildNode ();
		PushBackChildNode (L"Return type");
		if (t->ret_type.get () != nullptr) {
			t->ret_type->run (this);
		}
		PopBackChildNode ();
		PushBackChildNode (L"Body");
		t->body->run (this);
		PopBackChildNode ();
		PopBackChildNode ();
	}
	void run (StartType_t* t) override { AddChildNode (L"<Start type>"); }
	void run (I16_type_t* t) override { AddChildNode (L"<i16>"); }
	void run (I32_type_t* t) override { AddChildNode (L"<i32>"); }
	void run (I64_type_t* t) override { AddChildNode (L"<i64>"); }
	void run (U16_type_t* t) override { AddChildNode (L"<u16>"); }
	void run (U32_type_t* t) override { AddChildNode (L"<u32>"); }
	void run (U64_type_t* t) override { AddChildNode (L"<u64>"); }
	void run (F32_type_t* t) override { AddChildNode (L"<f32>"); }
	void run (F64_type_t* t) override { AddChildNode (L"<f64>"); }
	void run (String_type_t* t) override { AddChildNode (L"<string>"); }
	void run (Vector_type_t* t) override { AddChildNode (L"<vector>"); }
	void run (Array_type_t* t) override { AddChildNode (L"<array>"); }
	void run (SharedPtr_type_t* t) override { AddChildNode (L"<shared ptr>"); }
	void run (UniquePtr_type_t* t) override { AddChildNode (L"<unique ptr>"); }
	void run (Map_type_t* t) override { AddChildNode (L"<map>"); }
	void run (Atomic_type_t* t) override { AddChildNode (L"<atomic ref>"); }
	void run (Typename_t* t) override { AddChildNode (L"<typename>"); }
	void run (TemplateKey_t* t) override { AddChildNode (L"<template>"); }
	void run (EndType_t* t) override { AddChildNode (L"<End type>"); }
	void run (If_t* t) override { AddChildNode (L"<If>"); }
	void run (InCall_is_t* t) override {
		PushBackChildNode (L"Arg '" + t->id->getId () + L"' is");
		t->expr->run (this);
		PopBackChildNode ();
	}
	void run (Else_t* t) override { AddChildNode (L"<Else>"); }
	void run (Elif_t* t) override { AddChildNode (L"<Elif>"); }
	void run (While_t* t) override { AddChildNode (L"<While>"); }
	void run (Assign_t* t) override { AddChildNode (L"<assign>"); }
	void run (Sword_t* t) override { AddChildNode (L"<Sword(-+)>"); }
	void run (Arrow_t* t) override { AddChildNode (L"<Sword(->)>"); }

	void run (struct TemplateCall_t* t) override {
		PushBackChildNode (L"Call Template");
		AddChildNode (L"id: " + t->id->getId ());
		PushBackChildNode (L"arguments [" + std::to_wstring (t->args.size()) + L"]");
		for (auto& it : t->args) {
			it->run (this);
		}
		PopBackChildNode ();
		PopBackChildNode ();
	}
	void run (struct OpenLambdaType_t* t) override { AddChildNode (L"<Start Args Lambda Type>"); }
	void run (struct CloseLambdaType_t* t) override { AddChildNode (L"<End Args Lambda Type>"); }
	void run (struct LambdaType_t* t) override {
		PushBackChildNode (L"Lambda type");
		PushBackChildNode (L"arguments [" + std::to_wstring (t->args.size ()) + L"]");
		size_t i = 0;
		for (auto& it : t->args) {
			PushBackChildNode (L"Arg (" + std::to_wstring (i++) + L")" );
			it->run (this);
			PopBackChildNode ();
		}
		PopBackChildNode ();
		PushBackChildNode (L"Return type");
		t->ret->run (this);
		PopBackChildNode ();
		PopBackChildNode ();
		std::cout << "\\()->";
	}
	void run (struct In_t* t) override { AddChildNode (L"<in>"); }
	~Spy3 () = default;
};

//=======================================================//
//-------------- DEBUG WINDOW STARTS HERE --------------//
//=====================================================//


#ifndef DBG_WINDOW
#define DBG_WINDOW
#include <SFML/Graphics.hpp>

class DbgNode {
public:
	DbgNode (Tree<std::wstring>* node, sf::Font& font, float X = 0.f, float Y = 0.f, bool Open = true)
		: x (X), y (Y), open (Open)
	{
		text.setString (node->GetData ());
		text.setFont (font);
		text.setCharacterSize (12);
		heightIfClose = text.getGlobalBounds ().height;
		float offsetStep = 10, offsetY = offsetStep;

		for (auto& it : node->GetChilds ()) {
			childs.push_back (std::unique_ptr<DbgNode> (new DbgNode(it.get (), font, x + heightIfClose, y + offsetY)));
			offsetY += offsetStep;
		}
	}

	bool Draw (sf::RenderWindow& window, float parentX = 0.f, float parentY = 0.f) {
		text.setPosition (parentX + x, parentY + y);
		window.draw (text);
		if (open)
			for (auto& it : childs) {
				it->Draw (window, parentX + x, parentY + y);
			}
		return open;
	}

private:
	float x, y; // положение относително родителя
	float heightIfClose = 0.f, heightIfOpen = 0.f;
	bool open;
	sf::Text text;
	std::vector<std::unique_ptr<DbgNode>> childs;
};

class DbgWindow {
	enum MoveMapState {
		Wait,
		SetAncore,
		CountAndShowDiff,
		SetDifference,
	};
	static void MoveMapFsmUpdate (
		sf::RenderWindow& window,
		sf::View& view,
		float zoom,
		MoveMapState& moveMapState,
		sf::Vector2i& startAncor,
		sf::Vector2i& diffAncor,
		sf::Vector2i& diffAncorWas,
		bool mouseIsPressed,
		bool mouseWasPressed )
	{
		switch (moveMapState)
		{
		case Wait:
			if (mouseIsPressed && !mouseWasPressed)
				moveMapState = SetAncore;
			break;
		case SetAncore:
			startAncor = sf::Mouse::getPosition (window);
			moveMapState = CountAndShowDiff;
			diffAncorWas = {0, 0};
			break;
		case CountAndShowDiff:
			if (mouseWasPressed && !mouseIsPressed)
				moveMapState = SetDifference;
			view.move (-diffAncorWas.x*zoom, -diffAncorWas.y*zoom);
			diffAncor = startAncor - sf::Mouse::getPosition (window);
			view.move (diffAncor.x*zoom, diffAncor.y*zoom);
			diffAncorWas = diffAncor;
			break;
		case SetDifference:
			moveMapState = Wait;
			diffAncorWas = {0, 0};
			break;
		default:
			break;
		}
	}
public:
	static void Show (Tree<std::wstring>& tree, const char fontPath[], int width = 860, int height = 640)
	{
		sf::RenderWindow window (sf::VideoMode(width, height), "Hello");
		sf::View view;
		view.setCenter (width / 2, height / 2);
		view.setSize (width, height);
		sf::Font font;
		font.loadFromFile (fontPath);
		MoveMapState moveMapState{MoveMapState::Wait};
		DbgNode node (&tree, font);
		float zoom = 1.f;

		sf::Vector2i mouseStart{0, 0}, mouseDiff{0, 0}, mouseDiffWas{0, 0};
		bool mouseWasPressed = false;
		while (window.isOpen ())
		{
			sf::Event ev;
			while (window.pollEvent (ev))
			{
				if (ev.type == sf::Event::Closed || sf::Keyboard::isKeyPressed (sf::Keyboard::Return))
				{
					window.close ();
				}
				if (ev.type == sf::Event::MouseWheelMoved)
				{
					float zoom_coef = 1.f;
					if (ev.mouseWheel.delta > 0)
					{
						zoom_coef -= 0.05f;
						zoom *= 0.95f;
					}
					else
					{
						zoom_coef += 0.05f;
						zoom *= 1.05f;
					}

					view.zoom (zoom_coef);
				}
			}
			bool mouseIsPressed = sf::Mouse::isButtonPressed (sf::Mouse::Right);

			MoveMapFsmUpdate (
				window,
				view,
				zoom,
				moveMapState,
				mouseStart,
				mouseDiff,
				mouseDiffWas,
				mouseIsPressed,
				mouseWasPressed
			);

			mouseWasPressed = mouseIsPressed;

			window.setView (view);
			window.clear ();
			node.Draw (window);
			window.display ();
		}
	}
};
#endif

inline void printTokens_ (std::vector<std::shared_ptr<Token> >& tokens) {
	Spy3 spy;
	for (auto& it : tokens) it->run (&spy);
	DbgWindow::Show (spy.GetTree (), "data/Underdog-Regular.ttf");
}

inline void printTokens (const char str[], std::vector<std::shared_ptr<Token> >& tokens, const char str2[]) {
	printf (str);
	printTokens_ (tokens);
	printf (str2);
}

//=======================================================//
//----------- INLINE FUNCTIONS STARTS HERE -------------//
//=====================================================//

inline bool isOpener (Tok type) { return type == Tok::OpenParenthesis || type == Tok::OpenBrackets || type == Tok::OpenCurlyBrackets; }
inline bool isCloser (Tok type) { return type == Tok::CloseParenthesis || type == Tok::CloseBrackets || type == Tok::CloseCurlyBrackets; }
inline bool isOpenerUnsave (Tok type) { return type == Tok::OpenBody || isOpener (type); }
inline bool isCloserUnsave (Tok type) { return type == Tok::CloseBody || isCloser (type); }

#endif // TOKENS_H
