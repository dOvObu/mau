#ifndef DBG_NODE_H
#define DBG_NODE_H

#include "tokens.h"
#include "spy3.h"
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
		heightIfClose = aabb.height;
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
			window.draw (text);
			sf::Vector2f p1{text.getPosition () + sf::Vector2f{-2.f, heightIfClose + 5.f}};
			text.move (-parentX, -parentY);

			parentY += heightIfClose + 3.f;
			for (auto& it : childs) {
				sf::Vertex v[2] = {p1, sf::Vector2f{parentX + 28.f, parentY + heightIfClose + 5.f}};
				v[0].color = sf::Color::Blue;
				v[1].color = sf::Color::Cyan;
				window.draw (v, 2, sf::Lines);
				it->Draw (window, parentY, parentX + 30.f);
			}
			parentY += 3.f;
		}
	}

private:
	float heightIfClose = 0.f, width = 0.f;
	bool open;
	const int fontSize = 16;
	sf::Text text;
	std::vector<std::unique_ptr<DbgNode>> childs;
};

#endif
