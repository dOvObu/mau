#ifndef MY_MOUSE_H
#define MY_MOUSE_H
#include <SFML/Graphics.hpp>

class MyMouse {
public:
	static sf::Vector2f GetPosition () {
		sf::Vector2f position{0.f,0.f};
		sf::Vector2f viewPosition (view->getCenter ());
		sf::Vector2f viewSize (view->getSize ());
		viewSize *= 0.5f;
		if (window != nullptr)
			position = sf::Vector2f (sf::Mouse::getPosition (*window));
		return sf::Vector2f {
			viewPosition.x + zoom * (position.x) - viewSize.x,
			zoom * (position.y) - viewSize.y + viewPosition.y,
		};
	}
	static float& GetZoom () { return zoom; }
	static void SetZoom (float zoom) { MyMouse::zoom = zoom; }
	static void SetWindowAndView (sf::RenderWindow& window, sf::View& view) {
		MyMouse::window = &window;
		MyMouse::view = &view;
	}
private:
	static float zoom;
	static sf::RenderWindow* window;
	static sf::View* view;
};


#endif
