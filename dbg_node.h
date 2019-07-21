#ifndef DBG_NODE_H
#define DBG_NODE_H

#include "tokens.h"
#include "spy3.h"
#include "my_mouse.h"
#include <SFML/Graphics.hpp>

class DbgNode {
public:
	DbgNode (MyTree<std::wstring>* node, sf::Font& font, bool Open = true)
		: open (Open)
	{
		std::wstring str = node->GetData ();
		text.setString (str);
		text.setFont (font);
		text.setCharacterSize (fontSize);
		text.setPosition (0, 0);
		const auto&& aabb = text.getGlobalBounds ();
		height = aabb.height;
		width = aabb.width;

		for (auto& it : node->GetChilds ()) {
			childs.push_back (std::unique_ptr<DbgNode> (
				new DbgNode (it.get (), font)
			));
		}
	}

	void Draw (sf::RenderWindow& window, float& parentY, float parentX = 0.f) {

		if (open) {
			text.move (parentX, parentY);
			HandleOpen ();
			window.draw (text);
			sf::Vector2f p1{text.getPosition () + sf::Vector2f{-2.f, height + 5.f}};
			text.move (-parentX, -parentY);

			parentY += height + 5.f;
			for (auto& it : childs) {
				sf::Vertex v[2] = {p1, sf::Vector2f{parentX + 28.f, parentY + height + 5.f}};
				v[0].color = pointed || subpointed ? sf::Color(100,0,0,255) : sf::Color::Blue;
				v[1].color = pointed || subpointed ? sf::Color::Magenta : sf::Color::Cyan;

				window.draw (v, 2, sf::Lines);
				it->Draw (window, parentY, parentX + 30.f);
			}
			parentY += 3.f;
		}
	}

private:

	void HandleOpen () {
		const auto leftUp = text.getPosition ();
		const auto rightDown = leftUp + sf::Vector2f {width, height};
		const auto dot = MyMouse::GetPosition ();
		bool wasPointed = pointed;
		pointed = rightDown.x > dot.x && dot.x > leftUp.x && rightDown.y > dot.y && dot.y > leftUp.y;
		if (wasPointed != pointed && !subpointed) {
			UpdatePointed (pointed);
		}
	}

	void UpdatePointed (bool subpointed) {
		for (auto& it : childs) {
			it->pointed = pointed;
			it->subpointed = subpointed;
			it->UpdatePointed (subpointed);
		}
	}

	float height = 0.f, width = 0.f;
	bool open, pointed = false, subpointed = false;
	const int fontSize = 16;
	sf::Text text;
	std::vector<std::unique_ptr<DbgNode>> childs;
};

#endif
