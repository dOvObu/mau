#ifndef MY_TREE_H
#define MY_TREE_H
#include <string>

template<typename T>
struct MY_TREE {

	MY_TREE (const T& data)
		: node (new T (data))
	{}

	MY_TREE () = default;
	
	~MY_TREE () = default;

	MY_TREE<T>* AddChild (const T& data)
	{
		childs.push_back (std::make_unique<MY_TREE<T> > (data));
		childs.back ()->parent = this;
		return childs.back ().get ();
	}

	void Clear ()
	{
		node.reset (nullptr);
		childs.clear ();
	}

	MY_TREE<T>* SetData (const T& data)
	{
		node.reset (new T (data));
		
		return this;
	}

	T& GetData ()
	{
		return *node;
	}

	std::vector<std::unique_ptr<MY_TREE<T>>>& GetChilds ()
	{
		return childs;
	}


private:

	std::unique_ptr<T> node{nullptr};

	std::vector<std::unique_ptr<MY_TREE<T>>> childs;

	MY_TREE* parent{nullptr};
};
#endif
