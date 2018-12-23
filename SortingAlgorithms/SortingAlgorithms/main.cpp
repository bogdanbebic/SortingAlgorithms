#include <iostream>
#include <vector>
#include "graphics.h"
#include "graphic_sort.h"
#include "benchmark.h"
#include "sort.h"

void print_array(std::vector<int>& v) {
	for (auto elem : v) {
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}


std::vector<int> test_vec = {20, 9, 3, 11, 23, 25, 24, 26, 7, 17, 14, 10, 18, 21, 2, 4, 27, 30, 6, 12, 16, 19, 8, 22, 5, 1, 28, 29, 15, 13};

const int size_of_test_benchmark = 100;


int main(int argc, char* argv[]) {
	gui::hide_console();
	gui::window.setFramerateLimit(60);
	gui::font.loadFromFile("arial.ttf");
	bool visualization = false, benchmarking = false;
	gui::SelectedSort selected_sort = gui::None, previous_sort = gui::None;
	gui::SelectedType selected_type = gui::NoType;

	// Vector with flags for types of vector that will be benchmarked
	bool checkup_vector[gui::NumOfTypes] = {false};

	gui::start_btn.loadFromFile("start_btn.png");
	gui::stop_btn.loadFromFile("stop_btn.png");
	gui::exit_btn.loadFromFile("exit_btn.png");
	gui::check_on.loadFromFile("check_box_on.png");
	gui::check_off.loadFromFile("check_box_off.png");
	gui::radio_on.loadFromFile("radio_btn_on.png");
	gui::radio_off.loadFromFile("radio_btn_off.png");

	sf::RectangleShape separator_line(sf::Vector2f(3, 768));
	separator_line.setPosition(sf::Vector2f(511, 0));
	separator_line.setFillColor(sf::Color::White);

	std::vector<sf::Text> sort_txt_rect;
	std::vector<sf::Text> sort_txt_type;
	gui::init_sort_texts(sort_txt_rect);
	gui::init_type_texts(sort_txt_type);

	std::vector<sf::Sprite> radio_btn;
	std::vector<sf::Sprite> check_box;

	gui::init_radio_btn(radio_btn);
	gui::init_check_box(check_box);

	/*sf::Text header("Selection Menu", font);
	header.setStyle(sf::Text::Bold);
	header.setCharacterSize(40);
	header.setFillColor(sf::Color::White);
	header.setPosition(350, 5);*/

	sf::Text sort_header("Simulation", gui::font);
	sort_header.setStyle(sf::Text::Bold);
	sort_header.setCharacterSize(40);
	sort_header.setFillColor(sf::Color::White);
	sort_header.setPosition(100, 10);

	sf::Text type_header("Benchmarking", gui::font);
	type_header.setStyle(sf::Text::Bold);
	type_header.setCharacterSize(40);
	type_header.setFillColor(sf::Color::White);
	type_header.setPosition(600, 10);

	sf::Sprite btn_sim(gui::start_btn);
	btn_sim.setPosition(sf::Vector2f(100, 550));

	sf::Sprite btn_bench(gui::start_btn);
	btn_bench.setPosition(sf::Vector2f(600, 550));

	gui::exit_sprite.setTexture(gui::exit_btn);
	gui::exit_sprite.setPosition(sf::Vector2f(850, 50));

	try {
		while (gui::window.isOpen()) {
			sf::Event event;
			while (gui::window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					gui::window.close();
				}
				if (event.type == sf::Event::MouseButtonPressed) {
					selected_sort = gui::check_sort(event, sort_txt_rect, radio_btn);
					if (selected_sort != gui::None) {
						sort_txt_rect[selected_sort].setFillColor(sf::Color::Cyan);
						radio_btn[selected_sort].setTexture(gui::radio_on);
						if (previous_sort != gui::None && previous_sort != selected_sort) {
							sort_txt_rect[previous_sort].setFillColor(sf::Color::White);
							radio_btn[previous_sort].setTexture(gui::radio_off);
						}
						previous_sort = selected_sort;
					}
					else {
						selected_sort = previous_sort;
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

			if (visualization && selected_sort != gui::None) {
				std::vector<int> vec2 = test_vec;
				try {
					simulate_sort(vec2, selected_sort);
				}
				catch(ExitSim&) {}
				sort_txt_rect[previous_sort].setFillColor(sf::Color::White);
				radio_btn[previous_sort].setTexture(gui::radio_off);
				previous_sort = gui::None;
				visualization = false;
			}

			if (benchmarking) {
				benchmark_int::runtime = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
				benchmark_int::init_test_vectors(size_of_test_benchmark);
				for (auto i = 0; i < gui::NumOfTypes; i++) {
					if (checkup_vector[i]) {
						for (auto j = 0; j < gui::NumOfSorts; j++) {
							benchmark_int::runtime[j] += benchmark::measure_time(benchmark_int::sort_func[j], benchmark_int::test_vectors[i], sorting::less).count();
						}
					}
				}
				for (auto runtime : benchmark_int::runtime) {
					std::cout << runtime << std::endl;
				}

				// absolutely unnecessary, but so is my life :'), jk, I'm good
				gui::window.clear();
				sf::Text loading("LoAdIn'", gui::font);
				loading.setStyle(sf::Text::Bold);
				loading.setCharacterSize(40);
				loading.setFillColor(sf::Color::White);
				loading.setPosition(435, 320);
				gui::window.draw(loading);
				gui::window.display();
				sleep(sf::milliseconds(3309));
				try {
					gui::benchmark_sort(benchmark_int::runtime, sort_txt_rect);
				}
				catch(ExitBenchmark&) {}
				gui::exit_sprite.setPosition(sf::Vector2f(850, 50));
				benchmarking = false;
			}

			

			gui::window.clear();
			//gui::window.draw(header);
			gui::window.draw(separator_line);
			gui::window.draw(sort_header);
			gui::window.draw(type_header);
			gui::update_vec(sort_txt_rect);
			gui::update_vec(sort_txt_type);
			gui::window.draw(btn_sim);
			gui::window.draw(btn_bench);
			gui::update_radio(radio_btn);
			gui::update_radio(check_box);
			gui::window.display();
		}
	}
	catch (ProgramExit &) {
		// empty body
	}
	return 0;
}
