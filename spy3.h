#ifndef SPY3_H
#define SPY3_H
#include "tokens.h"

template<typename T>
struct Tree {
	Tree (const T& data) : node (new T (data)) {}
	Tree () = default;
	~Tree () = default;

	Tree<T>* AddChild (const T& data) {
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
		nodeStack.push_back (nodeStack.back ()->AddChild (str));
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
	void run (UInt_t* t) override { AddChildNode (L"const " + std::to_wstring (t->getUInt ()) + L" : unsigned int"); }
	void run (Int_t* t) override { AddChildNode (L"const " + std::to_wstring (t->getInt ()) + L" : int"); }
	void run (Float_t* t) override { AddChildNode (L"const " + std::to_wstring (t->getFloat ()) + L" : float"); }
	void run (String_t* t) override { AddChildNode (L"const '" + t->getId () + L"' : string"); }
	void run (Expr_t* t) override {
		PushBackChildNode (L"Expression:");
		for (auto& it : *(t->l.get ())) {
			it->run (this);
		}
		PopBackChildNode ();
	}
	void run (Call_t* t) override {
		PushBackChildNode (L"Call " + t->id->getId () + L" function");
		PushBackChildNode (L"arguments [" + std::to_wstring (t->args.size ()) + L"]");
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
	void run (Id_t* t) override { AddChildNode (L"Id: " + t->getId ()); }
	void run (ArrayDef_t* t) override {
		PushBackChildNode (L"Array[" + std::to_wstring (t->cells.size ()) + L']');
		for (auto& it : t->cells) {
			it.run (this);
		}
		PopBackChildNode ();
	}
	void run (OpenParenthesis_t* t) override { AddChildNode (L"("); }
	void run (CloseParenthesis_t* t) override { AddChildNode (L")"); }
	void run (Space_t* t) override { AddChildNode (L"<white space( )>"); }
	void run (Dot_t* t) override { AddChildNode (L"<dot(.)>"); }
	void run (Lambda_t* t) override { AddChildNode (L"<lambda(\\)>"); }
	void run (Semicolon_t* t) override { AddChildNode (L"<semicolon(;)>"); }
	void run (Colon_t* t) override { AddChildNode (L"<colon(:)>"); }
	void run (DoubleColon_t* t) override { AddChildNode (L"<double colon(::)>"); }
	void run (OpenBody_t* t) override { AddChildNode (L"<open body>"); }
	void run (OpenBodyOfLambda_t* t) override { AddChildNode (L"<open body of lambda>"); }
	void run (CloseBody_t* t) override { AddChildNode (L"<close body>"); }
	void run (LambdaDef_t* t) override {
		PushBackChildNode (L"Lambda def");
		PushBackChildNode (L"Arguments [" + std::to_wstring (t->args.size ()) + L"]");
		bool f = true;
		{
			size_t i = 0;
			for (auto& it : t->args) {
				PushBackChildNode (L"Arg (" + std::to_wstring (i++) + L")");
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
		PushBackChildNode (L"arguments [" + std::to_wstring (t->args.size ()) + L"]");
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
			PushBackChildNode (L"Arg (" + std::to_wstring (i++) + L")");
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

#endif
