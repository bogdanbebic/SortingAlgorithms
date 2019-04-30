#include <iostream>
#include <vector>
#include "graphics.h"
#include "graphic_sort.h"
#include "benchmark.h"
#include "sort.h"
#include <random>

void print_array(std::vector<int>& v) {
	for (auto elem : v) {
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}

std::vector<int> test_vec;

const int size_of_test_benchmark = 1000;


int main(int argc, char* argv[]) {
	gui::init_graphics();
	bool visualization = false, benchmarking = false;
	gui::SelectedSort previous_sort = gui::None;
	gui::SelectedType selected_type = gui::NoType;

	test_vec.reserve(30);
	for (auto i = 1; i <= 30; i++) {
		test_vec.push_back(i);
	}

	// Vector with flags for types of vector that will be benchmarked
	bool checkup_vector[gui::NumOfTypes] = {false};


	sf::RectangleShape separator_line(sf::Vector2f(4, 768));
	separator_line.setPosition(sf::Vector2f(505, 70));
	separator_line.setFillColor(sf::Color::White);
	sf::RectangleShape separator_line_horizontal(sf::Vector2f(1024, 4));
	separator_line_horizontal.setPosition(sf::Vector2f(0, 70));
	separator_line_horizontal.setFillColor(sf::Color::White);

	std::vector<sf::Text> sort_txt_rect;
	std::vector<sf::Text> sort_txt_type;
	gui::init_sort_texts(sort_txt_rect, true);
	gui::init_type_texts(sort_txt_type);

	std::vector<sf::Sprite> radio_btn;
	std::vector<sf::Sprite> check_box;
	gui::init_radio_btn(radio_btn);
	gui::init_check_box(check_box);

	sf::Text menu_header("Sorting Algorithms", gui::font);
	menu_header.setStyle(sf::Text::Bold);
	menu_header.setCharacterSize(50);
	menu_header.setFillColor(sf::Color::Cyan);
	menu_header.setPosition(300, 5);

	sf::Text sort_header("Simulation", gui::font);
	sort_header.setStyle(sf::Text::Bold);
	sort_header.setCharacterSize(40);
	sort_header.setFillColor(sf::Color::Cyan);
	sort_header.setPosition(100, 75);

	sf::Text type_header("Benchmarking", gui::font);
	type_header.setStyle(sf::Text::Bold);
	type_header.setCharacterSize(40);
	type_header.setFillColor(sf::Color::Cyan);
	type_header.setPosition(600, 75);

	sf::Text created_by("Created by: Uros Krstic, Bogdan Bebic", gui::font);
	created_by.setCharacterSize(20);
	created_by.setFillColor(sf::Color::Cyan);
	created_by.setPosition(6, 740);

	sf::Sprite btn_sim(gui::start_btn);
	btn_sim.setPosition(sf::Vector2f(100, 550));
	sf::Sprite btn_bench(gui::start_btn);
	btn_bench.setPosition(sf::Vector2f(600, 550));

	try {
		while (gui::window.isOpen()) {
			sf::Event event;
			while (gui::window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					gui::window.close();
				}
				if (event.type == sf::Event::MouseButtonPressed) {
					gui::selected_sort = gui::check_sort(event, sort_txt_rect, radio_btn);
					if (gui::selected_sort != gui::None) {
						sort_txt_rect[gui::selected_sort].setFillColor(sf::Color::Cyan);
						radio_btn[gui::selected_sort].setTexture(gui::radio_on);
						if (previous_sort != gui::None && previous_sort != gui::selected_sort) {
							sort_txt_rect[previous_sort].setFillColor(sf::Color::White);
							radio_btn[previous_sort].setTexture(gui::radio_off);
						}
						previous_sort = gui::selected_sort;
					}
					else {
						gui::selected_sort = previous_sort;
					}

					selected_type = gui::check_type(event, sort_txt_type, check_box);
					if (selected_type != gui::NoType) {
						if (checkup_vector[selected_type]) {
							sort_txt_type[selected_type].setFillColor(sf::Color::White);
							check_box[selected_type].setTexture(gui::check_off);
							checkup_vector[selected_type] = false;
						}
						else {
							sort_txt_type[selected_type].setFillColor(sf::Color::Cyan);
							check_box[selected_type].setTexture(gui::check_on);
							checkup_vector[selected_type] = true;
						}
						
					}
					visualization = gui::check_start_btn(event, btn_sim);
					benchmarking = gui::check_start_btn(event, btn_bench);

				}
			}

			if (visualization && gui::selected_sort != gui::None) {
				std::shuffle(test_vec.begin(), test_vec.end(), std::default_random_engine());
				try {
					simulate_sort(test_vec, gui::selected_sort);
				}
				catch(ExitSim&) {}
				sort_txt_rect[previous_sort].setFillColor(sf::Color::White);
				radio_btn[previous_sort].setTexture(gui::radio_off);
				previous_sort = gui::None;
				visualization = false;
			}

			if (benchmarking) {
				gui::window.clear();
				gui::display_loading_screen();
				benchmark_int::runtime = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
				benchmark_int::init_test_vectors(size_of_test_benchmark);
				for (auto i = 0; i < gui::NumOfTypes; i++) {
					if (checkup_vector[i]) {
						for (auto j = 0; j < gui::NumOfSorts; j++) {
							benchmark_int::runtime[j] += benchmark::measure_time(benchmark_int::sort_func[j], benchmark_int::test_vectors[i], sorting::less).count() * 1000;
						}
					}
				}
				for (auto runtime : benchmark_int::runtime) {
					std::cout << runtime << std::endl;
				}

				try {
					gui::benchmark_sort(benchmark_int::runtime);
				}
				catch(ExitBenchmark&) {}
				gui::exit_sprite.setPosition(sf::Vector2f(850, 50));
				benchmarking = false;
			}
			gui::window.clear();
			gui::window.draw(separator_line);
			gui::window.draw(separator_line_horizontal);
			gui::window.draw(menu_header);
			gui::window.draw(sort_header);
			gui::window.draw(type_header);
			gui::window.draw(created_by);
			gui::update_vec(sort_txt_rect);
			gui::update_vec(sort_txt_type);
			gui::window.draw(btn_sim);
			gui::window.draw(btn_bench);
			gui::update_radio(radio_btn);
			gui::update_radio(check_box);
			gui::window.display();
		}
	}
	catch (ProgramExit &) {}
	return 0;
}
