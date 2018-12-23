#include "graphics.h"
#include "graphic_sort.h"


std::vector<sf::RectangleShape> gui::rect_v;
sf::RenderWindow gui::window(sf::VideoMode(1024, 768), "Sorting Algorithms Visualization and Benchmarking");
sf::Font gui::font;
sf::Texture gui::start_btn;
sf::Texture gui::stop_btn;
sf::Texture gui::exit_btn;
sf::Texture gui::check_on;
sf::Texture gui::check_off;
sf::Texture gui::radio_on;
sf::Texture gui::radio_off;
sf::Sprite gui::exit_sprite;



bool gui::is_inside_shape(const sf::Event& e, const sf::RectangleShape& rect) {
	if (e.mouseButton.x >= rect.getPosition().x && e.mouseButton.x <= rect.getPosition().x + rect.getSize().x) {
		if (e.mouseButton.y >= rect.getPosition().y && e.mouseButton.y <= rect.getPosition().y + rect.getSize().y) {
			return true;
		}
	}
	return false;
}

void gui::init_sort_texts(std::vector<sf::Text>& texts)
{
	float start_height = 80;
	for(auto i = 0U; i < NumOfSorts; i++) {
		texts.emplace_back(sf::Text(sort_name[i], font));
		texts[i].setStyle(sf::Text::Bold);
		texts[i].setFillColor(sf::Color::White);
		texts[i].setPosition(140, start_height + i * 50);
	}
}

void gui::init_type_texts(std::vector<sf::Text>& texts)
{
	float start_height = 80;
	for (auto i = 0U; i < NumOfTypes; i++) {
		texts.emplace_back(sf::Text(type_name[i], font));
		texts[i].setStyle(sf::Text::Bold);
		texts[i].setFillColor(sf::Color::White);
		texts[i].setPosition(640, start_height + i * 50);
	}
}

void gui::init_radio_btn(std::vector<sf::Sprite>& radio_btn) {
	float start_height = 88;
	for (auto i = 0U; i < NumOfSorts; i++) {
		radio_btn.emplace_back(sf::Sprite(radio_off));
		radio_btn[i].setPosition(100, start_height + i * 50);
	}
}

void gui::init_check_box(std::vector<sf::Sprite>& check)
{
	float start_height = 86;
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
	switch (selected_sort)
	{
	case Insertion:
		gui_sorting::insertion_sort<int>(v, gui_sorting::less);
		break;
	case Heap:
		gui_sorting::heap_sort<int>(v, gui_sorting::less);
		break;
	case Shell:
		gui_sorting::shell_sort<int>(v, gui_sorting::less);
		break;
	case Shaker:
		gui_sorting::shaker_sort<int>(v, gui_sorting::less);
		break;
	case Quick:
		gui_sorting::quick_sort(v, gui_sorting::less);
		break;
	case Bubble:
		gui_sorting::bubble_sort(v, gui_sorting::less);
		break;
	case Selection:
		gui_sorting::selection_sort(v, gui_sorting::less);
		break;
	case Merge:
		gui_sorting::merge_sort(v, gui_sorting::less);
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
	for (const auto& i : rect_v)
		window.draw(i);
	window.draw(exit_sprite);
	window.display();
	sleep(sf::milliseconds(100));
}

void gui::changePos(sf::RectangleShape& dst, sf::RectangleShape& src) {
	dst.setSize(src.getSize());
	dst.setPosition(sf::Vector2f(dst.getPosition().x, src.getPosition().y));
}
