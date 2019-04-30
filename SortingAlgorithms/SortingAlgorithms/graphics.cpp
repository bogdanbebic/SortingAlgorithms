#include "graphics.h"
#include "graphic_sort.h"
#include "sort.h"
#include <string>

std::vector<sf::RectangleShape> gui::rect_v;
sf::RenderWindow gui::window(sf::VideoMode(1024, 768), "Sorting Algorithms Simulation and Benchmarking", sf::Style::Close | sf::Style::Titlebar);
sf::Font gui::font;
gui::SelectedSort gui::selected_sort = gui::None;
sf::Texture gui::start_btn;
sf::Texture gui::stop_btn;
sf::Texture gui::exit_btn;
sf::Texture gui::check_on;
sf::Texture gui::check_off;
sf::Texture gui::radio_on;
sf::Texture gui::radio_off;
sf::Image gui::img;
sf::Sprite gui::exit_sprite;



bool gui::is_inside_shape(const sf::Event& e, const sf::RectangleShape& rect) {
	if (e.mouseButton.x >= rect.getPosition().x && e.mouseButton.x <= rect.getPosition().x + rect.getSize().x) {
		if (e.mouseButton.y >= rect.getPosition().y && e.mouseButton.y <= rect.getPosition().y + rect.getSize().y) {
			return true;
		}
	}
	return false;
}

void gui::init_graphics()
{
	hide_console();
	window.setFramerateLimit(60);
	font.loadFromFile("arial.ttf");
	img.loadFromFile("sa_icon.png");

	window.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());

	start_btn.loadFromFile("start_btn.png");
	stop_btn.loadFromFile("stop_btn.png");
	exit_btn.loadFromFile("exit_btn.png");
	check_on.loadFromFile("check_box_on.png");
	check_off.loadFromFile("check_box_off.png");
	radio_on.loadFromFile("radio_btn_on.png");
	radio_off.loadFromFile("radio_btn_off.png");

	exit_sprite.setTexture(gui::exit_btn);
	exit_sprite.setPosition(sf::Vector2f(850, 50));
}

void gui::init_sort_texts(std::vector<sf::Text>& texts, bool is_in_menu)
{
	float start_height = is_in_menu ? 140.0F : 80.0F;
	for(auto i = 0U; i < NumOfSorts; i++) {
		texts.emplace_back(sf::Text(sort_name[i], font));
		texts[i].setStyle(sf::Text::Bold);
		texts[i].setFillColor(sf::Color::White);
		texts[i].setPosition(140, start_height + i * 50);
	}
}

void gui::init_type_texts(std::vector<sf::Text>& texts)
{
	float start_height = 140;
	for (auto i = 0U; i < NumOfTypes; i++) {
		texts.emplace_back(sf::Text(type_name[i], font));
		texts[i].setStyle(sf::Text::Bold);
		texts[i].setFillColor(sf::Color::White);
		texts[i].setPosition(640, start_height + i * 50);
	}
}

void gui::init_radio_btn(std::vector<sf::Sprite>& radio_btn) {
	float start_height = 148;
	for (auto i = 0U; i < NumOfSorts; i++) {
		radio_btn.emplace_back(sf::Sprite(radio_off));
		radio_btn[i].setPosition(100, start_height + i * 50);
	}
}

void gui::init_check_box(std::vector<sf::Sprite>& check)
{
	float start_height = 146;
	for (auto i = 0U; i < NumOfTypes; i++) {
		check.emplace_back(sf::Sprite(check_off));
		check[i].setPosition(600, start_height + i * 50);
	}
}

gui::SelectedSort gui::check_sort(const sf::Event& e, std::vector<sf::Text>& texts, std::vector<sf::Sprite>& radio) {
	for (int i = 0; i < NumOfSorts; i++) {
		if (e.mouseButton.x > texts[i].getPosition().x && e.mouseButton.y > texts[i].getPosition().y) {
			if (e.mouseButton.x < texts[i].getPosition().x + 16 * sort_name[i].length() &&
				e.mouseButton.y < texts[i].getPosition().y + 30) {
				return static_cast<SelectedSort>(i);
			}
		}
		if (e.mouseButton.x > radio[i].getPosition().x && e.mouseButton.y > radio[i].getPosition().y) {
			if (e.mouseButton.x < radio[i].getPosition().x + 30 &&
				e.mouseButton.y < radio[i].getPosition().y + 30) {
				return static_cast<SelectedSort>(i);
			}
		}
	}
	return None;
}

gui::SelectedType gui::check_type(const sf::Event& e, std::vector<sf::Text>& texts, std::vector<sf::Sprite>& check){
	for (int i = 0; i < NumOfTypes; i++) {
		if (e.mouseButton.x > texts[i].getPosition().x && e.mouseButton.y > texts[i].getPosition().y) {
			if (e.mouseButton.x < texts[i].getPosition().x + 16 * type_name[i].length() &&
				e.mouseButton.y < texts[i].getPosition().y + 30) {
				return static_cast<SelectedType>(i);
			}
		}
		if (e.mouseButton.x > check[i].getPosition().x && e.mouseButton.y > check[i].getPosition().y) {
			if (e.mouseButton.x < check[i].getPosition().x + 30 &&
				e.mouseButton.y < check[i].getPosition().y + 30) {
				return static_cast<SelectedType>(i);
			}
		}
	}
	return NoType;
}

bool gui::check_start_btn(const sf::Event & e, sf::Sprite & spr)
{
	if (e.mouseButton.x > spr.getPosition().x && e.mouseButton.y > spr.getPosition().y) {
		if (e.mouseButton.x < spr.getPosition().x + 187 && e.mouseButton.y < spr.getPosition().y + 88)
			return true;
	}
	return false;
}


void gui::update_vec(std::vector<sf::Text>& texts)
{
	for (const auto& text : texts)
		window.draw(text);
}

void gui::update_radio(std::vector<sf::Sprite>& radio_btn) {
	for (const auto& btn : radio_btn)
		window.draw(btn);
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
	switch (gui::selected_sort)
	{
	case Insertion:
		gui_sorting::insertion_sort<int>(v, sorting::less);
		break;
	case Heap:
		gui_sorting::heap_sort<int>(v, sorting::less);
		break;
	case Shell:
		gui_sorting::shell_sort<int>(v, sorting::less);
		break;
	case Shaker:
		gui_sorting::shaker_sort<int>(v, sorting::less);
		break;
	case Quick:
		gui_sorting::quick_sort(v, sorting::less);
		break;
	case Bubble:
		gui_sorting::bubble_sort(v, sorting::less);
		break;
	case Selection:
		gui_sorting::selection_sort(v, sorting::less);
		break;
	case Merge:
		gui_sorting::merge_sort(v, sorting::less);
		break;
	default:
		break;
	}
}

void gui::update_simulation() {
	sf::Event event;
	while (gui::window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			gui::window.close();
			throw ProgramExit();
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.x > exit_sprite.getPosition().x && event.mouseButton.y > exit_sprite.getPosition().y) {
				if (event.mouseButton.x < exit_sprite.getPosition().x + 135 && event.mouseButton.y < exit_sprite.getPosition().y + 82) {
					throw ExitSim();
				}
			}
		}
	}
	window.clear(sf::Color::Black);
	sf::Text header(sort_name[selected_sort] + " sort", font);
	header.setPosition(50, 50);
	header.setStyle(sf::Text::Bold);
	header.setFillColor(sf::Color::Cyan);
	header.setCharacterSize(50);
	for (const auto& i : rect_v)
		window.draw(i);
	window.draw(exit_sprite);
	window.draw(header);
	window.display();
	sleep(sf::milliseconds(100));
}

void gui::changePos(sf::RectangleShape& dst, sf::RectangleShape& src) {
	dst.setSize(src.getSize());
	dst.setPosition(sf::Vector2f(dst.getPosition().x, src.getPosition().y));
}

void gui::display_loading_screen()
{
	sf::Text loading("LOADING", font);
	loading.setStyle(sf::Text::Bold);
	loading.setCharacterSize(40);
	loading.setFillColor(sf::Color::White);
	loading.setPosition(420, 320);
	window.draw(loading);
	window.display();
}

void gui::benchmark_sort(std::vector<double>& runtime) {
	std::vector<sf::Text> time_text;
	std::vector<sf::Text> sort_rect;
	init_sort_texts(sort_rect, false);
	exit_sprite.setPosition(sf::Vector2f(435, 630));
	float start_height = 80;
	for (auto i = 0U; i < runtime.size(); i++) {
		time_text.emplace_back(sf::Text(std::to_string(runtime[i]), font));
		time_text[i].setStyle(sf::Text::Bold);
		time_text[i].setFillColor(sf::Color::White);
		time_text[i].setPosition(640, start_height + i * 50);
	}

	window.clear();
	update_vec(sort_rect);
	update_vec(time_text);
	sf::Text sorts_header("Sorts:", font);
	sorts_header.setFillColor(sf::Color::Cyan);
	sorts_header.setStyle(sf::Text::Bold);
	sorts_header.setCharacterSize(40);
	sorts_header.setPosition(140, 10);
	window.draw(sorts_header);
	sf::Text time_header("Time (ms):", font);
	time_header.setFillColor(sf::Color::Cyan);
	time_header.setStyle(sf::Text::Bold);
	time_header.setCharacterSize(40);
	time_header.setPosition(640, 10);
	window.draw(time_header);
	window.draw(exit_sprite);
	window.display();
	
	sf::Event event;
	while (true) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				throw ProgramExit();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.x > exit_sprite.getPosition().x && event.mouseButton.y > exit_sprite.getPosition().y) {
					if (event.mouseButton.x < exit_sprite.getPosition().x + 135 && event.mouseButton.y < exit_sprite.getPosition().y + 82) {
						throw ExitBenchmark();
					}
				}
			}
		}
	}
}
