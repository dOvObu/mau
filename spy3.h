#ifndef SPY3_H
#define SPY3_H
#include "tokens.h"
#include "my_tree.h"

struct SPY3 : Runner {

public:
	SPY3 ()
	{
		stringTree.SetData (L"root");
		nodeStack.push_back (&stringTree);
	}

	~SPY3 () = default;

private:
	MY_TREE<std::wstring> stringTree;
	std::vector<MY_TREE<std::wstring>*> nodeStack;


	void AddChildNode (std::wstring&& str)
	{
		nodeStack.back ()->AddChild (str);
	}

	void PushBackChildNode (std::wstring&& str)
	{
		nodeStack.push_back (nodeStack.back ()->AddChild (str));
	}

	void PopBackChildNode ()
	{
		nodeStack.pop_back ();
	}

public:
	MY_TREE<std::wstring>& GetTree ()
	{
		return stringTree;
	}

	void Clear ()
	{
		stringTree.Clear ();
		stringTree.SetData (L"root");
		nodeStack.clear ();
		nodeStack.push_back (&stringTree);
	}

	void run (UInt_t* t) override
	{
		AddChildNode (L"const " + std::to_wstring (t->getUInt ()) + L" : unsigned int");
	}

	void run (Int_t* t) override
	{
		AddChildNode (L"const " + std::to_wstring (t->getInt ()) + L" : int");
	}

	void run (Float_t* t) override
	{
		AddChildNode (L"const " + std::to_wstring (t->getFloat ()) + L" : float");
	}

	void run (String_t* t) override
	{
		AddChildNode (L"const '" + t->getId () + L"' : string");
	}

	void run (Expr_t* t) override
	{
		PushBackChildNode (L"Expression:");
		if (t->l != nullptr) {
			for (auto& it : *(t->l.get ())) {
				it->run (this);
			}
		}
		PopBackChildNode ();
	}

	void run (Call_t* t) override
	{
		PushBackChildNode (L"Call " + t->id->getId () + L" function");
		PushBackChildNode (L"arguments [" + std::to_wstring (t->args.size ()) + L"]");

		for (auto& it : t->args) {
			it->run (this);
		}
		PopBackChildNode ();
		PopBackChildNode ();
	}

	void run (binop_t* t)
	{
		switch (t->opType) {
			case Tok::Plus:     PushBackChildNode (L"+");   break;
			case Tok::Minus:    PushBackChildNode (L"-");   break;
			case Tok::Devide:   PushBackChildNode (L"/");   break;
			case Tok::Multiply: PushBackChildNode (L"*");   break;
			case Tok::Equal:    PushBackChildNode (L"==");  break;
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

	void run (Id_t* t) override
	{
		AddChildNode (L"Id: " + t->getId ());
	}

	void run (ArrayDef_t* t) override
	{
		PushBackChildNode (L"Array[" + std::to_wstring (t->cells.size ()) + L']');

		for (auto& it : t->cells) {
			it.run (this);
		}
		PopBackChildNode ();
	}

	void run (LambdaDef_t* t) override
	{
		PushBackChildNode (L"Lambda def");
		PushBackChildNode (L"Arguments [" + std::to_wstring (t->args.size ()) + L"]");
		bool f = true;
		
		size_t i = 0;
		for (auto& it : t->args) {
			PushBackChildNode (L"Arg (" + std::to_wstring (i++) + L")");
			it.second->run (this);
			if (it.first.get () != nullptr) it.first->run (this);
			else AddChildNode (L"Any type");
			PopBackChildNode ();
		}
		
		PopBackChildNode ();
		PushBackChildNode (L"Return type");

		if (t->ret_type.get () != nullptr) {
			t->ret_type->run (this);
		}
		PopBackChildNode ();
		PushBackChildNode (L"Body");
		if (t->body != nullptr) {
			t->body->run (this);
		}
		PopBackChildNode ();
		PopBackChildNode ();
	}

	void run (InCall_is_t* t) override {
		PushBackChildNode (L"Arg '" + t->id->getId () + L"' is");
		t->expr->run (this);
		PopBackChildNode ();
	}

	void run (struct TemplateCall_t* t) override
	{
		PushBackChildNode (L"Call Template");
		AddChildNode (L"id: " + t->id->getId ());
		PushBackChildNode (L"arguments [" + std::to_wstring (t->args.size ()) + L"]");

		for (auto& it : t->args) {
			it->run (this);
		}
		PopBackChildNode ();
		PopBackChildNode ();
	}

	void run (struct LambdaType_t* t) override
	{
		PushBackChildNode (L"Lambda type");
		PushBackChildNode (L"arguments [" + std::to_wstring (t->args.size ()) + L"]");

		size_t i = 0;
		for (auto& it : t->args) {
			PushBackChildNode (L"Arg (" + std::to_wstring (i++) + L")");
			it->run (this);
			PopBackChildNode ();
		}
		PopBackChildNode ();
		PushBackChildNode (L"Return type");

		if (t->ret.get() != nullptr) {
			t->ret->run (this);
		} else {
			PushBackChildNode (L"void");
			PopBackChildNode ();
		}

		PopBackChildNode ();
		PopBackChildNode ();
	}

	void run (Return_t* t) override
	{
		PushBackChildNode (L"Return");
		if (t->l != nullptr) {
			for (auto& it : *(t->l)) {
				it->run (this);
			}
		} else {
			AddChildNode (L"void");
		}
		PopBackChildNode ();
	}

	void run (If_t* t) override
	{
		PushBackChildNode (L"if");
			PushBackChildNode (L"condition:");
			if (t->condition != nullptr) {
				t->condition->run (this);
			}
			PopBackChildNode ();

			PushBackChildNode (L"body:");
			if (t->body != nullptr) {
				t->body->run (this);
			}
			PopBackChildNode ();

			if (t->alternative != nullptr) {
				PushBackChildNode (L"alternative:");
				t->alternative->run (this);
				PopBackChildNode ();
			}
		PopBackChildNode ();
	}

	void run (Elif_t* t) override
	{
		PushBackChildNode (L"elif");
		PushBackChildNode (L"condition:");
		if (t->condition != nullptr) {
			t->condition->run (this);
		}
		PopBackChildNode ();

		PushBackChildNode (L"body:");
		if (t->body != nullptr) {
			t->body->run (this);
		}
		PopBackChildNode ();

		if (t->alternative != nullptr) {
			PushBackChildNode (L"alternative:");
			t->alternative->run (this);
			PopBackChildNode ();
		}
		PopBackChildNode ();
	}

	void run (Else_t* t) override
	{
		PushBackChildNode (L"else");

		PushBackChildNode (L"body:");
		if (t->body != nullptr) {
			t->body->run (this);
		}
		PopBackChildNode ();

		PushBackChildNode (L"alternative:");
		if (t->alternative != nullptr) {
			t->alternative->run (this);
		}
		PopBackChildNode ();
		PopBackChildNode ();
	}

	void run (While_t* t) override
	{
		PushBackChildNode (L"while");
		PushBackChildNode (L"condition:");
		if (t->condition != nullptr) {
			t->condition->run (this);
		}
		PopBackChildNode ();

		PushBackChildNode (L"body:");
		if (t->body != nullptr) {
			t->body->run (this);
		}
		PopBackChildNode ();
		PopBackChildNode ();
	}

#define OVERRIDE_NODE(type_, wString_) void run(type_* t) override { AddChildNode (wString_); }
	OVERRIDE_NODE (OpenParenthesis_t,  L"(")
	OVERRIDE_NODE (CloseParenthesis_t, L")")
	OVERRIDE_NODE (Space_t,            L"<white space( )>")
	OVERRIDE_NODE (Dot_t,              L"<dot(.)>")
	OVERRIDE_NODE (Lambda_t,           L"<lambda(\\)>")
	OVERRIDE_NODE (Semicolon_t,        L"<semicolon(;)>")
	OVERRIDE_NODE (Colon_t,            L"<colon(:)>")
	OVERRIDE_NODE (DoubleColon_t,      L"<double colon(::)>")
	OVERRIDE_NODE (OpenBody_t,         L"<open body>")
	OVERRIDE_NODE (OpenBodyOfLambda_t, L"<open body of lambda>")
	OVERRIDE_NODE (CloseBody_t,        L"<close body>")
	OVERRIDE_NODE (StartType_t,        L"<Start type>")
	OVERRIDE_NODE (I16_type_t,         L"<i16>")
	OVERRIDE_NODE (I32_type_t,         L"<i32>")
	OVERRIDE_NODE (I64_type_t,         L"<i64>")
	OVERRIDE_NODE (U16_type_t,         L"<u16>")
	OVERRIDE_NODE (U32_type_t,         L"<u32>")
	OVERRIDE_NODE (U64_type_t,         L"<u64>")
	OVERRIDE_NODE (F32_type_t,         L"<f32>")
	OVERRIDE_NODE (F64_type_t,         L"<f64>")
	OVERRIDE_NODE (String_type_t,      L"<string>")
	OVERRIDE_NODE (Vector_type_t,      L"<vector>")
	OVERRIDE_NODE (Array_type_t,       L"<array>")
	OVERRIDE_NODE (SharedPtr_type_t,   L"<shared ptr>")
	OVERRIDE_NODE (UniquePtr_type_t,   L"<unique ptr>")
	OVERRIDE_NODE (Map_type_t,         L"<map>")
	OVERRIDE_NODE (Atomic_type_t,      L"<atomic ref>")
	OVERRIDE_NODE (Typename_t,         L"<typename>")
	OVERRIDE_NODE (TemplateKey_t,      L"<template>")
	OVERRIDE_NODE (EndType_t,          L"<End type>")
	OVERRIDE_NODE (Assign_t,           L"<assign>")
	OVERRIDE_NODE (Sword_t,            L"<Sword(-+)>")
	OVERRIDE_NODE (Arrow_t,            L"<Sword(->)>")
	OVERRIDE_NODE (In_t,               L"<in>")
	OVERRIDE_NODE (OpenLambdaType_t,   L"<Start Args Lambda Type>")
	OVERRIDE_NODE (CloseLambdaType_t,  L"<End Args Lambda Type>")
	OVERRIDE_NODE (Equal_t,            L"<==>")
	OVERRIDE_NODE (NotEqual_t,         L"<!=>")
	OVERRIDE_NODE (nye_t,              L"< ! >")
	OVERRIDE_NODE (OpenTemplateType_t, L"<Open Template Type>")
	OVERRIDE_NODE (CloseTemplateType_t,L"<Close Template Type>")
	OVERRIDE_NODE (IfKey_t,            L"<if keyword>")
	OVERRIDE_NODE (ElifKey_t,          L"<elif keyword>")
	OVERRIDE_NODE (ElseKey_t,          L"<else keyword>")
	OVERRIDE_NODE (Assert_t,           L"<Assert>")
	OVERRIDE_NODE (Let_t,              L"<Let>")
	OVERRIDE_NODE (Throw_t,            L"<Throw>")
	OVERRIDE_NODE (Try_t,              L"<Try>")
	OVERRIDE_NODE (Catch_t,            L"<Catch>")
	OVERRIDE_NODE (ForKey_t,           L"<for keyword>")
	OVERRIDE_NODE (For_t,              L"<for>")
	OVERRIDE_NODE (WhileKey_t,         L"<while keyword>")
	OVERRIDE_NODE (Ban_t,              L"<ban>")
	OVERRIDE_NODE (Break_t,            L"<break>")
	OVERRIDE_NODE (Continue_t,         L"<continue>")
	OVERRIDE_NODE (Const_t,            L"<const>")
	OVERRIDE_NODE (Import_t,           L"<import>")
	OVERRIDE_NODE (As_t,               L"<as>")
	OVERRIDE_NODE (Empty_t,            L"<empty>")
	OVERRIDE_NODE (Delete_t,           L"<delete>")
	OVERRIDE_NODE (Comma_t,            L"<comma(,)>")
	OVERRIDE_NODE (TypeComma_t,        L"<Type Comma>")
	OVERRIDE_NODE (EndString_t,        L"<End String>")
	OVERRIDE_NODE (OpenBrackets_t,     L"<[>")
	OVERRIDE_NODE (CloseBrackets_t,    L"<]>")
	OVERRIDE_NODE (OpenCurlyBrackets_t, L"<{>")
	OVERRIDE_NODE (CloseCurlyBrackets_t,L"<}>")
	OVERRIDE_NODE (Reference_t,        L"<reference>")
	OVERRIDE_NODE (Less_t,             L"<less>")
	OVERRIDE_NODE (More_t,             L"<more>")
	OVERRIDE_NODE (LessOrEqual_t,      L"<less or equal>")
	OVERRIDE_NODE (MoreOrEqual_t,      L"<more or equal>")
	OVERRIDE_NODE (DotInType_t,        L"<dot in type>")
	OVERRIDE_NODE (Therefore_t,        L"<therefore>")
	OVERRIDE_NODE (And_t,              L"<and>")
	OVERRIDE_NODE (Or_t,               L"<or>")
	OVERRIDE_NODE (Argument_t,         L"<argument>")
	OVERRIDE_NODE (Number_t,           L"<number>")
	OVERRIDE_NODE (Not_t,              L"<not>")
	OVERRIDE_NODE (Stmt_t,             L"<statement>")
	OVERRIDE_NODE (ArrayCall_t,        L"<array call>")
	OVERRIDE_NODE (Minus_t,            L"<minus>")
	OVERRIDE_NODE (UnMinus_t,          L"<unary minus>")
	OVERRIDE_NODE (Plus_t,             L"<plus>")
	OVERRIDE_NODE (Multiply_t,         L"<multiply>")
	OVERRIDE_NODE (Power_t,            L"<power>")
	OVERRIDE_NODE (Devide_t,           L"<devide>")
	OVERRIDE_NODE (Mod_t,              L"<mod>")
	OVERRIDE_NODE (Decrement_t,        L"<decrement>")
	OVERRIDE_NODE (Increment_t,        L"<increment>")
	OVERRIDE_NODE (FieldCall_t,        L"<field call>")
	OVERRIDE_NODE (TypeFieldCall_t,    L"<type field call>")
	OVERRIDE_NODE (FieldDef_t,         L"<field def>")
#undef OVERRIDE_NODE
};
#endif
