#ifndef MY_TREE_H
#define MY_TREE_H
#include <string>

template<typename T>
struct MyTree {
	MyTree (const T& data) : node (new T (data)) {}
	MyTree () = default;
	~MyTree () = default;

	MyTree<T>* AddChild (const T& data) {
		childs.push_back (std::make_unique<MyTree<T> > (data));
		childs.back ()->parent = this;
		return childs.back ().get ();
	}
	void Clear () {
		node.reset (nullptr);
		childs.clear ();
	}
	MyTree<T>* SetData (const T& data) { node.reset (new T (data)); return this; }
	T& GetData () { return *node; }
	std::vector<std::unique_ptr<MyTree<T>>>& GetChilds () { return childs; }

private:
	std::unique_ptr<T> node{nullptr};
	std::vector<std::unique_ptr<MyTree<T>>> childs;
	MyTree* parent{nullptr};
};
#endif
