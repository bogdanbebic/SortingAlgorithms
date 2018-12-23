#include "graphics.h"
#include "sort.h"

std::vector<sf::RectangleShape> gui::rect_v;
sf::RenderWindow gui::window(sf::VideoMode(1024, 768), "Sorting Algorithms Visualization and Benchmarking");


bool gui::is_inside_shape(const sf::Event& e, const sf::RectangleShape& rect) {
	if (e.mouseButton.x >= rect.getPosition().x && e.mouseButton.x <= rect.getPosition().x + rect.getSize().x) {
		if (e.mouseButton.y >= rect.getPosition().y && e.mouseButton.y <= rect.getPosition().y + rect.getSize().y) {
			return true;
		}
	}
	return false;
}

void gui::simulate_sort(std::vector<int>& v, gui::SelectedSort selected_sort)
{
	int max_height = 500, width = 1024 / static_cast<int>(v.size());
	int max = v[0];
	for (int i : v)
		if (i > max) max = i;
	rect_v.clear();
	for (size_t i = 0; i < v.size(); i++) {
		sf::RectangleShape rect(sf::Vector2f(static_cast<float>(width), static_cast<float>(v[i]) * max_height / max));
		rect_v.push_back(rect);
		rect_v[i].setFillColor(sf::Color::White);
		rect_v[i].setPosition(static_cast<float>(i * width), static_cast<float>(268 + max_height - rect_v[i].getSize().y));
	}
	switch (selected_sort)
	{
	case Insertion:
		sorting::insertion_sort<int>(v, sorting::less);
		break;
	case Heap:
		sorting::heap_sort<int>(v, sorting::less);
		break;
	case Shell:
		sorting::shell_sort<int>(v, sorting::less);
		break;
	case Shaker:
		sorting::shaker_sort<int>(v, sorting::less);
		break;
	case Quick:
		sorting::quick_sort(v, sorting::less);
	default:
		break;
	}
}

void gui::update_simulation() {
	
	window.clear(sf::Color::Black);
	for (const auto& i : rect_v)
		window.draw(i);
	window.display();
	sleep(sf::milliseconds(100));
}

void gui::changePos(sf::RectangleShape& dst, sf::RectangleShape& src) {
	dst.setSize(src.getSize());
	dst.setPosition(sf::Vector2f(dst.getPosition().x, src.getPosition().y));
}
