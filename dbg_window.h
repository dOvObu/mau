﻿#ifndef DBG_WINDOW_H
#define DBG_WINDOW_H
#include "tokens.h"
#include "spy3.h"
#include "dbg_node.h"
#include <SFML/Graphics.hpp>


class DbgWindow
{
	enum MoveMapState {
		Wait,
		SetAncore,
		CountAndShowDiff,
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
			view.move (-diffAncorWas.x*zoom, -diffAncorWas.y*zoom);
			diffAncor = startAncor - sf::Mouse::getPosition (window);
			view.move (diffAncor.x*zoom, diffAncor.y*zoom);

			if (mouseWasPressed && !mouseIsPressed) {
				moveMapState = Wait;
				diffAncorWas = {0, 0};
			} else {
				diffAncorWas = diffAncor;
			}
			break;
		default:
			break;
		}
	}
public:
	static void Show (MyTree<std::wstring>& tree, const char fontPath[], int width = 860, int height = 640)
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
