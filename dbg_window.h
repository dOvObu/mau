#ifndef DBG_WINDOW_H
#define DBG_WINDOW_H
#include "tokens.h"
#include "spy3.h"
#include <SFML/Graphics.hpp>


class DbgNode {
public:
	DbgNode (Tree<std::wstring>* node, sf::Font& font, bool Open = true)
		: open (Open)
	{
		std::wstring str = node->GetData ();
		text.setString (str);
		text.setFont (font);
		text.setCharacterSize (fontSize);
		text.setPosition (0, 0);
		heightIfClose = text.getGlobalBounds ().height;
		heightIfOpen = (heightIfClose + 3.f) * (node->GetChilds().size());

		for (auto& it : node->GetChilds ()) {
			childs.push_back (std::unique_ptr<DbgNode> (
				new DbgNode (it.get (), font)
			));
		}
	}

	bool Draw (sf::RenderWindow& window, float& parentY, float parentX = 0.f) {
		text.move (parentX, parentY);
		window.draw (text);
		sf::Vector2f p1{text.getPosition () + sf::Vector2f{-2.f, heightIfClose + 5.f}};
		text.move (-parentX, -parentY);
		
		if (open) {
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

		return open;
	}

private:
	float heightIfClose = 0.f, heightIfOpen = 0.f;
	bool open;
	const int fontSize = 16;
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
		bool mouseWasPressed)
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
		sf::RenderWindow window (sf::VideoMode (width, height), "Hello");
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
			float y = 0;
			node.Draw (window, y);
			window.display ();
		}
	}
};
inline void showTokens (std::vector<std::shared_ptr<Token> >& tokens) {
	Spy3 spy3;
	for (auto& it : tokens) it->run (&spy3);
	DbgWindow::Show (spy3.GetTree (), "data/Underdog-Regular.ttf");
}

#endif
