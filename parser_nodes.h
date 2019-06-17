#ifndef PARSER_NODES_H
#define PARSER_NODES_H

#include <memory>
#include <vector>
#include <map>
#include "tokens.h"

namespace nodes
{
		struct Node
		{
				Tok type = Tok::Empty;
				virtual int getInt(){return 0;}
				virtual void setInt(int val){}
				virtual float getFloat(){return 0.f;}
				virtual void setFloat(float val){}
				virtual std::wstring getName(){return L"";}
				virtual void setName(std::wstring name){}
				virtual std::vector<std::shared_ptr<Node> >* getList(){return nullptr;}
				virtual ~Node(){}
		};

		struct Body : Node
		{
				std::vector<std::shared_ptr<Node> > statm;
				Body(){this->type = Tok::Body;}
				virtual std::vector<std::shared_ptr<Node> >* getList(){return &statm;}
		};

		struct Id : Node
		{
				std::wstring name;
				Id(){this->type = Tok::Id;}
		};

		struct Assign : Node
		{
				Id id;
				std::shared_ptr<Node> meaning;
				Assign(){this->type = Tok::Assign;}
		};

		struct Lambda : Node
		{
				std::vector<std::shared_ptr<Node> > args;
				std::vector<std::shared_ptr<Node> > statements;
				std::vector<unsigned> returns;
				Lambda(){this->type = Tok::Lambda;}
		};

		struct Call : Node
		{
				Id id;
				std::vector<std::shared_ptr<Node> > args;
				Call(){this->type = Tok::Call;}
		};

		struct Binar : Node
		{
				std::shared_ptr<Node> left;
				std::shared_ptr<Node> right;
		};

		struct Pluss : Binar {};

		struct Int : Node
		{
				int val;
				virtual int getInt(){return val;}
				virtual void setInt(int val){this->val = val;}
		};
}

void parse_to_tree (std::vector<std::shared_ptr<Token> >& tokens, nodes::Node& root);

#endif // PARSER_NODES_H
