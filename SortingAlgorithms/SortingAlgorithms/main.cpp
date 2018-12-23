#include <iostream>
#include <vector>
#include "graphics.h"
#include "sort.h"

void print_array(std::vector<int>& v) {
	for (auto elem : v) {
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}


std::vector<int> test_vec = {20, 9, 3, 11, 23, 25, 24, 26, 7, 17, 14, 10, 18, 21, 2, 4, 27, 30, 6, 12, 16, 19, 8, 22, 5, 1, 28, 29, 15, 13};

int main(int argc, char* argv[]) {
	//gui::hide_console();
	gui::window.setFramerateLimit(60);
	sf::Font font;
	font.loadFromFile("arial.ttf");
	bool visualization = false, benchmarking = false;
	gui::SelectedSort selected_sort = gui::None;
	gui::SelectedType selected_type = gui::NoType;
	std::vector<sf::Text> sort_txt_rect;
	std::vector<sf::Text> sort_txt_type;
	//gui::init_sort_texts(sort_txt_rect);
	//gui::init_type_texts(sort_txt_type);

	sf::Text header("Selection Menu", font);
	header.setStyle(sf::Text::Bold);
	header.setCharacterSize(40);
	header.setFillColor(sf::Color::White);
	header.setPosition(350, 5);

	sf::Text sort_header("Select a sort:", font);
	sort_header.setStyle(sf::Text::Bold);
	sort_header.setFillColor(sf::Color::White);
	sort_header.setPosition(100, 100);

	sf::Text type_header("Select array type:", font);
	type_header.setStyle(sf::Text::Bold);
	type_header.setFillColor(sf::Color::White);
	type_header.setPosition(600, 100);

	while (gui::window.isOpen()) {
		sf::Event event;  
		while (gui::window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				gui::window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				// TODO: check functions
				// selected_sort = check_sort(sort_txt_rect);
				// selected_type = check_type(type_txt_rect);
				// same for benchmarking and visualization and start buttons
			}
		}

		//if (visualization && selected_sort != gui::None && selected_type != gui::NoType) {
			// TODO: simulation of a sort 
		//}
		// if (benchmarking && selected_type != gui::NoType) {
			// TODO: Benchmarking of all sorts 
		//}

		simulate_sort(test_vec, gui::Heap);

		gui::window.clear();
		gui::window.draw(header);
		gui::window.draw(sort_header);
		gui::window.draw(type_header);
		gui::window.display();
	}
}
