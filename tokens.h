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
#define RUN_VMETHOD(___inType__) virtual void run (struct ___inType__ * t) = 0
	RUN_VMETHOD (UInt_t);
	RUN_VMETHOD (Int_t);
	RUN_VMETHOD (Float_t);
	RUN_VMETHOD (String_t);
	RUN_VMETHOD (Id_t);
	RUN_VMETHOD (ArrayDef_t);
	RUN_VMETHOD (Expr_t);
	RUN_VMETHOD (Call_t);
	RUN_VMETHOD (Space_t);
	RUN_VMETHOD (binop_t);
	RUN_VMETHOD (OpenParenthesis_t);
	RUN_VMETHOD (CloseParenthesis_t);
	RUN_VMETHOD (OpenBody_t);
	RUN_VMETHOD (OpenBodyOfLambda_t);
	RUN_VMETHOD (CloseBody_t);
	RUN_VMETHOD (If_t);
	RUN_VMETHOD (Else_t);
	RUN_VMETHOD (Elif_t);
	RUN_VMETHOD (While_t);
	RUN_VMETHOD (Semicolon_t);
	RUN_VMETHOD (Colon_t);
	RUN_VMETHOD (DoubleColon_t);
	RUN_VMETHOD (Lambda_t);
	RUN_VMETHOD (LambdaDef_t);
	RUN_VMETHOD (Dot_t);
	RUN_VMETHOD (Assign_t);
	RUN_VMETHOD (InCall_is_t);
	RUN_VMETHOD (StartType_t);
	RUN_VMETHOD (EndType_t);
	RUN_VMETHOD (I16_type_t);
	RUN_VMETHOD (I32_type_t);
	RUN_VMETHOD (I64_type_t);
	RUN_VMETHOD (U16_type_t);
	RUN_VMETHOD (U32_type_t);
	RUN_VMETHOD (U64_type_t);
	RUN_VMETHOD (F32_type_t);
	RUN_VMETHOD (F64_type_t);
	RUN_VMETHOD (String_type_t);
	RUN_VMETHOD (Array_type_t);
	RUN_VMETHOD (Map_type_t);
	RUN_VMETHOD (Atomic_type_t);
	RUN_VMETHOD (Vector_type_t);
	RUN_VMETHOD (SharedPtr_type_t);
	RUN_VMETHOD (UniquePtr_type_t);
	RUN_VMETHOD (TemplateKey_t);
	RUN_VMETHOD (Typename_t);
	RUN_VMETHOD (Sword_t);
	RUN_VMETHOD (Arrow_t);
	RUN_VMETHOD (TemplateCall_t);
	RUN_VMETHOD (OpenLambdaType_t);
	RUN_VMETHOD (CloseLambdaType_t);
	RUN_VMETHOD (LambdaType_t);
	RUN_VMETHOD (In_t);

	RUN_VMETHOD (Equal_t);
	RUN_VMETHOD (NotEqual_t);
	RUN_VMETHOD (nye_t);
	RUN_VMETHOD (OpenTemplateType_t);
	RUN_VMETHOD (CloseTemplateType_t);
	RUN_VMETHOD (IfKey_t);
	RUN_VMETHOD (ElifKey_t);
	RUN_VMETHOD (ElseKey_t);
	RUN_VMETHOD (Assert_t);
	RUN_VMETHOD (Let_t);
	RUN_VMETHOD (Throw_t);
	RUN_VMETHOD (Try_t);
	RUN_VMETHOD (Catch_t);
	RUN_VMETHOD (ForKey_t);
	RUN_VMETHOD (For_t);
	RUN_VMETHOD (WhileKey_t);
	RUN_VMETHOD (Ban_t);
	RUN_VMETHOD (Break_t);
	RUN_VMETHOD (Continue_t);
	RUN_VMETHOD (Const_t);
	RUN_VMETHOD (Import_t);
	RUN_VMETHOD (As_t);
	RUN_VMETHOD (Empty_t);
	RUN_VMETHOD (Delete_t);
	RUN_VMETHOD (Comma_t);
	RUN_VMETHOD (TypeComma_t);
	RUN_VMETHOD (EndString_t);
	RUN_VMETHOD (OpenBrackets_t);
	RUN_VMETHOD (CloseBrackets_t);
	RUN_VMETHOD (OpenCurlyBrackets_t);
	RUN_VMETHOD (CloseCurlyBrackets_t);
	RUN_VMETHOD (Reference_t);
	RUN_VMETHOD (Less_t);
	RUN_VMETHOD (More_t);
	RUN_VMETHOD (LessOrEqual_t);
	RUN_VMETHOD (MoreOrEqual_t);
	RUN_VMETHOD (DotInType_t);
	RUN_VMETHOD (Therefore_t);
	RUN_VMETHOD (And_t);
	RUN_VMETHOD (Or_t);
	RUN_VMETHOD (Return_t);
	RUN_VMETHOD (Argument_t);
	RUN_VMETHOD (Number_t);
	RUN_VMETHOD (Not_t);
	RUN_VMETHOD (Stmt_t);
	RUN_VMETHOD (ArrayCall_t);
	RUN_VMETHOD (Minus_t);
	RUN_VMETHOD (UnMinus_t);
	RUN_VMETHOD (Plus_t);
	RUN_VMETHOD (Multiply_t);
	RUN_VMETHOD (Power_t);
	RUN_VMETHOD (Devide_t);
	RUN_VMETHOD (Mod_t);
	RUN_VMETHOD (Decrement_t);
	RUN_VMETHOD (Increment_t);
	RUN_VMETHOD (FieldCall_t);
	RUN_VMETHOD (TypeFieldCall_t);
	RUN_VMETHOD (FieldDef_t);
#undef RUN_VMETHOD
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

struct Expr_t 			       : Token { RUNNER_METHOD Tok type () {return Tok::Expr;} std::shared_ptr<std::vector<std::shared_ptr<Token>>> l; };
struct Dot_t			       : Token { RUNNER_METHOD Tok type () {return Tok::Dot;} };
struct Semicolon_t		    : Token { RUNNER_METHOD Tok type () {return Tok::Semicolon;} };
struct Colon_t			       : Token { RUNNER_METHOD Tok type () {return Tok::Colon;} };
struct DoubleColon_t	       : Token { RUNNER_METHOD Tok type () {return Tok::DoubleColon;} };
struct Assign_t			    : Token { RUNNER_METHOD Tok type () {return Tok::Assign;} };
struct Lambda_t			    : Token { RUNNER_METHOD Tok type () {return Tok::Lambda;} };
struct In_t				       : Token { RUNNER_METHOD Tok type () {return Tok::In;} };
struct OpenLambdaType_t     : Token { RUNNER_METHOD Tok type () {return Tok::OpenLambdaType;} };
struct CloseLambdaType_t    : Token { RUNNER_METHOD Tok type () {return Tok::CloseLambdaType;} };
struct ArrayDef_t           : Token { RUNNER_METHOD Tok type () {return Tok::ArrayDef;} std::vector<Expr_t> cells; };
struct I16_type_t           : Token { RUNNER_METHOD Tok type () {return Tok::I16_type; } };
struct I32_type_t           : Token { RUNNER_METHOD Tok type () {return Tok::I32_type; } };
struct I64_type_t           : Token { RUNNER_METHOD Tok type () {return Tok::I64_type; } };
struct U16_type_t           : Token { RUNNER_METHOD Tok type () {return Tok::U16_type; } };
struct U32_type_t           : Token { RUNNER_METHOD Tok type () {return Tok::U32_type; } };
struct U64_type_t           : Token { RUNNER_METHOD Tok type () {return Tok::U64_type; } };
struct F32_type_t           : Token { RUNNER_METHOD Tok type () {return Tok::F32_type; } };
struct F64_type_t           : Token { RUNNER_METHOD Tok type () {return Tok::F64_type; } };
struct String_type_t        : Token { RUNNER_METHOD Tok type () {return Tok::String_type; } };
struct Vector_type_t        : Token { RUNNER_METHOD Tok type () {return Tok::String_type; } };
struct TemplateKey_t        : Token { RUNNER_METHOD Tok type () {return Tok::TemplateKey; } };
struct Array_type_t         : Token { RUNNER_METHOD Tok type () {return Tok::Array_type; } };
struct Map_type_t           : Token { RUNNER_METHOD Tok type () {return Tok::Map_type; } };
struct Atomic_type_t        : Token { RUNNER_METHOD Tok type () {return Tok::Atomic_type; } };
struct SharedPtr_type_t     : Token { RUNNER_METHOD Tok type () {return Tok::SharedPtr_type; } };
struct UniquePtr_type_t     : Token { RUNNER_METHOD Tok type () {return Tok::UniquePtr_type; } };
struct Typename_t           : Token { RUNNER_METHOD Tok type () {return Tok::Typename; } };
struct OpenParenthesis_t    : Token { RUNNER_METHOD Tok type () {return Tok::OpenParenthesis;} };
struct CloseParenthesis_t   : Token { RUNNER_METHOD Tok type () {return Tok::CloseParenthesis;} };
struct Arrow_t              : Token { RUNNER_METHOD Tok type () {return Tok::Arrow;} };
struct Sword_t              : Token { RUNNER_METHOD Tok type () {return Tok::Sword;} };
struct StartType_t          : Token { RUNNER_METHOD Tok type () {return Tok::StartType;} };
struct EndType_t            : Token { RUNNER_METHOD Tok type () {return Tok::EndType; } };
struct InCall_is_t          : Token { RUNNER_METHOD Tok type () {return Tok::InCall_is; } std::shared_ptr<Token> id, expr;};
struct Space_t              : Token { RUNNER_METHOD Tok type () {return Tok::Space;} };
struct OpenBody_t           : Token { RUNNER_METHOD Tok type () {return Tok::OpenBody;} std::shared_ptr<std::vector<std::shared_ptr<Token>>> stmts; };
struct OpenBodyOfLambda_t   : Token { RUNNER_METHOD Tok type () {return Tok::OpenBodyOfLambda;} };
struct CloseBody_t          : Token { RUNNER_METHOD Tok type () {return Tok::CloseBody;} };
struct binop_t              : Token { RUNNER_METHOD Tok type () {return Tok::binop;} Tok opType; std::shared_ptr<Token> left, right; };

struct Equal_t              : Token { RUNNER_METHOD Tok type () {return Tok::Equal;} };
struct NotEqual_t           : Token { RUNNER_METHOD Tok type () {return Tok::NotEqual;} };
struct nye_t                : Token { RUNNER_METHOD Tok type () {return Tok::nye;} };
struct OpenTemplateType_t   : Token { RUNNER_METHOD Tok type () {return Tok::OpenTemplateType;} };
struct CloseTemplateType_t  : Token { RUNNER_METHOD Tok type () {return Tok::CloseTemplateType;} };
struct IfKey_t              : Token { RUNNER_METHOD Tok type () {return Tok::IfKey;} };
struct ElifKey_t            : Token { RUNNER_METHOD Tok type () {return Tok::ElifKey;} };
struct ElseKey_t            : Token { RUNNER_METHOD Tok type () {return Tok::ElseKey;} };
struct Assert_t             : Token { RUNNER_METHOD Tok type () {return Tok::Assert;} };
struct Let_t                : Token { RUNNER_METHOD Tok type () {return Tok::Let;} };
struct Throw_t              : Token { RUNNER_METHOD Tok type () {return Tok::Throw;} };
struct Try_t                : Token { RUNNER_METHOD Tok type () {return Tok::Try;} };
struct Catch_t              : Token { RUNNER_METHOD Tok type () {return Tok::Catch;} };
struct ForKey_t             : Token { RUNNER_METHOD Tok type () {return Tok::ForKey; } };
struct For_t                : Token { RUNNER_METHOD Tok type () {return Tok::For;} };
struct WhileKey_t           : Token { RUNNER_METHOD Tok type () {return Tok::WhileKey; } };
struct Ban_t                : Token { RUNNER_METHOD Tok type () {return Tok::Ban;} };
struct Break_t              : Token { RUNNER_METHOD Tok type () {return Tok::Break;} };
struct Continue_t           : Token { RUNNER_METHOD Tok type () {return Tok::Continue;} };
struct Const_t              : Token { RUNNER_METHOD Tok type () {return Tok::Const;} };
struct Import_t             : Token { RUNNER_METHOD Tok type () {return Tok::Import;} };
struct As_t                 : Token { RUNNER_METHOD Tok type () {return Tok::As;} };
struct Empty_t              : Token { RUNNER_METHOD Tok type () {return Tok::Empty;} };
struct Delete_t             : Token { RUNNER_METHOD Tok type () {return Tok::Delete;} };
struct Comma_t              : Token { RUNNER_METHOD Tok type () {return Tok::Comma;} };
struct TypeComma_t          : Token { RUNNER_METHOD Tok type () {return Tok::TypeComma;} };
struct EndString_t          : Token { RUNNER_METHOD Tok type () {return Tok::EndString;} };
struct OpenBrackets_t       : Token { RUNNER_METHOD Tok type () {return Tok::OpenBrackets; } };
struct CloseBrackets_t      : Token { RUNNER_METHOD Tok type () {return Tok::CloseBrackets; } };
struct OpenCurlyBrackets_t  : Token { RUNNER_METHOD Tok type () {return Tok::OpenCurlyBrackets; } };
struct CloseCurlyBrackets_t : Token { RUNNER_METHOD Tok type () {return Tok::CloseCurlyBrackets; } };
struct Reference_t          : Token { RUNNER_METHOD Tok type () {return Tok::Reference; } };
struct Less_t               : Token { RUNNER_METHOD Tok type () {return Tok::Less; } };
struct More_t               : Token { RUNNER_METHOD Tok type () {return Tok::More; } };

struct LessOrEqual_t        : Token { RUNNER_METHOD Tok type () {return Tok::LessOrEqual; } };
struct MoreOrEqual_t        : Token { RUNNER_METHOD Tok type () {return Tok::MoreOrEqual; } };
struct DotInType_t          : Token { RUNNER_METHOD Tok type () {return Tok::DotInType; } };
struct Therefore_t          : Token { RUNNER_METHOD Tok type () {return Tok::Therefore; } };
struct And_t                : Token { RUNNER_METHOD Tok type () {return Tok::And; } };
struct Or_t                 : Token { RUNNER_METHOD Tok type () {return Tok::Or; } };
struct Return_t	          : Token { RUNNER_METHOD Tok type () {return Tok::Return;}
	std::shared_ptr<std::vector<std::shared_ptr<Token> > > l{nullptr};
};

struct LambdaType_t : Token { RUNNER_METHOD Tok type () { return Tok::LambdaType; } // ...
	std::vector<std::shared_ptr<Token> > args; // types of args
	std::shared_ptr<Token> ret; // type of ret values
};
struct TemplateCall_t : Token { RUNNER_METHOD Tok type () { return Tok::TemplateCall; } // ...
	std::shared_ptr<Id_t> id;
	std::vector<std::shared_ptr<Token>> args;
};
struct LambdaDef_t : Token { RUNNER_METHOD Tok type () {return Tok::LambdaDef;} // ...
	std::shared_ptr<Token> body = nullptr;
	std::vector<std::pair<std::shared_ptr<Token>, std::shared_ptr<Token> > > args;
	std::shared_ptr<Token> ret_type = nullptr;
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


struct Argument_t : Token { RUNNER_METHOD
	Tok type () { return Tok::Argument; } std::wstring id;
	void setId (const std::wstring& str) { this->str = str; }
	std::wstring getId () { return str; }
private:
	std::wstring str;
};

struct Number_t : Token { RUNNER_METHOD
	Tok type () { return Tok::Number; }
	void setId (const std::wstring& str) { this->str = cirToLat (str); }
	std::wstring getId () { return latToCir (str); }
	std::string getStr () { return str; }
private:
	std::string str;
};

struct Not_t                : Token { RUNNER_METHOD Tok type () {return Tok::Not;} std::shared_ptr<Token> right; };
struct Stmt_t               : Token { RUNNER_METHOD Tok type () {return Tok::Stmt;} std::shared_ptr<std::vector<std::shared_ptr<Token>>> l; };

struct Call_t               : Token { RUNNER_METHOD Tok type () {return Tok::Call;} // ... 
	std::shared_ptr<Id_t> id;
	std::vector<std::shared_ptr<Token>> args;
};
struct ArrayCall_t          : Token { RUNNER_METHOD
	Tok type () {return Tok::ArrayCall;}
	std::shared_ptr<Id_t> id;
	std::vector<std::shared_ptr<Token>> args;
};
struct Minus_t              : Token { RUNNER_METHOD Tok type () {return Tok::Minus;}};
struct UnMinus_t            : Token { RUNNER_METHOD Tok type () {return Tok::UnMinus;} std::shared_ptr<Token> right; };
struct Plus_t               : Token { RUNNER_METHOD Tok type () {return Tok::Plus;}};
struct Multiply_t           : Token { RUNNER_METHOD Tok type () {return Tok::Multiply;} };
struct Power_t              : Token { RUNNER_METHOD Tok type () {return Tok::Power;}};
struct Devide_t             : Token { RUNNER_METHOD Tok type () {return Tok::Devide;} };
struct Mod_t                : Token { RUNNER_METHOD Tok type () {return Tok::Mod;}};
struct Decrement_t          : Token { RUNNER_METHOD Tok type () {return Tok::Decrement;} std::shared_ptr<Token> right; };
struct Increment_t          : Token { RUNNER_METHOD Tok type () {return Tok::Increment;} std::shared_ptr<Token> right; };
struct FieldCall_t          : Token { RUNNER_METHOD Tok type () { return Tok::FieldCall; } std::shared_ptr<Token> owner, id; };
struct TypeFieldCall_t      : Token { RUNNER_METHOD Tok type () { return Tok::TypeFieldCall; } std::shared_ptr<Token> owner, id; };
struct FieldDef_t           : Token { RUNNER_METHOD
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
//----------- INLINE FUNCTIONS STARTS HERE -------------//
//=====================================================//

inline bool isOpener (Tok type) { return type == Tok::OpenParenthesis || type == Tok::OpenBrackets || type == Tok::OpenCurlyBrackets; }
inline bool isCloser (Tok type) { return type == Tok::CloseParenthesis || type == Tok::CloseBrackets || type == Tok::CloseCurlyBrackets; }
inline bool isOpenerUnsave (Tok type) { return type == Tok::OpenBody || isOpener (type); }
inline bool isCloserUnsave (Tok type) { return type == Tok::CloseBody || isCloser (type); }

#endif // TOKENS_H
