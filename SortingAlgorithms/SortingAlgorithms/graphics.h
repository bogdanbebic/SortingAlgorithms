#pragma once
#ifndef _GRAPHICS_H_
#define  _GRAPHICS_H_
#include "SFML/Graphics.hpp"
#include <Windows.h>
#include <string>

class ProgramExit : public std::exception 
{};

class ExitSim : public std::exception
{};

class ExitBenchmark : public std::exception
{};

namespace gui {
	extern std::vector<sf::RectangleShape> rect_v;
	extern sf::RenderWindow window;
	extern sf::Font font;
	extern sf::Texture start_btn;
	extern sf::Texture stop_btn;
	extern sf::Texture exit_btn;
	extern sf::Texture check_on;
	extern sf::Texture check_off;
	extern sf::Texture radio_on;
	extern sf::Texture radio_off;
	extern sf::Sprite exit_sprite;

	enum SelectedSort { None = -1, Selection, Bubble, Shaker, Insertion, Shell, Quick, Heap, Merge, NumOfSorts };
	enum SelectedType { NoType = -1, Random, NearlySorted, Sorted, ReverseSorted, FewDistinct, NumOfTypes };
	const std::string sort_name[NumOfSorts] = { "Selection", "Bubble", "Shaker", "Insertion", "Shell", "Quick", "Heap", "Merge" };
	const std::string type_name[NumOfTypes] = { "Random", "Nearly Sorted", "Sorted", "Reverse Sorted", "Few Distinct" };

	inline void hide_console() {
		::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	}

	inline void show_console() {
		::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	}

	bool is_inside_shape(const sf::Event& e, const sf::RectangleShape& rect);

	void init_sort_texts(std::vector<sf::Text>& texts);
	void init_type_texts(std::vector<sf::Text>& texts);
	void init_radio_btn(std::vector<sf::Sprite>& radio_btn);
	void init_check_box(std::vector<sf::Sprite>& check);

	SelectedSort check_sort(const sf::Event& e,std::vector<sf::Text>& texts, std::vector<sf::Sprite>& radio);
	SelectedType check_type(const sf::Event& e, std::vector<sf::Text>& texts, std::vector<sf::Sprite>& check);
	bool check_start_btn(const sf::Event& e, sf::Sprite& spr);

	void update_vec(std::vector<sf::Text>& texts);
	void update_radio(std::vector<sf::Sprite>& radio_btn);

	void simulate_sort(std::vector<int>& v, gui::SelectedSort selected_sort);
	void update_simulation();
	void changePos(sf::RectangleShape& dst, sf::RectangleShape& src);

	void benchmark_sort(std::vector<double>& runtime, std::vector<sf::Text>& text_rects);
}
#endif
