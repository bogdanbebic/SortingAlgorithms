#pragma once
#ifndef _GRAPHICS_H_
#define  _GRAPHICS_H_
#include "SFML/Graphics.hpp"
#include <Windows.h>

namespace gui {
	extern std::vector<sf::RectangleShape> rect_v;
	extern sf::RenderWindow window;
	enum SelectedSort { None = -1, Selection, Insertion, Bubble, Shaker, Shell, Heap, Quick, Merge, NumOfSorts };
	enum SelectedType { NoType = -1, Random, NearlySorted, Sorted, ReverseSorted, NumOfTypes };

	inline void hide_console() {
		::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	}

	inline void show_console() {
		::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	}

	bool is_inside_shape(const sf::Event& e, const sf::RectangleShape& rect);

	void init_sort_texts(std::vector<sf::Text>& texts);
	void init_type_texts(std::vector<sf::Text>& texts);

	void simulate_sort(std::vector<int>& v, gui::SelectedSort selected_sort);
	void update_simulation();
	void changePos(sf::RectangleShape& dst, sf::RectangleShape& src);
}
#endif
