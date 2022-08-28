//
// Created by hola on 9/6/2022.
//



#include "../include/Menu.h"
using namespace sf;
using namespace std;

Menu::Menu() : MenuSelected(0) {
    if(!font.loadFromFile("../assets/fonts/ChrustyRock.ttf")){
        cout<< "No font";
    }
    menu.reserve(MAX_MAIN_MENU);

    string texto;
    float pos_x, pos_y, textSize;
    ifstream file("../assets/components/seleccionables.txt");

    while(file >> texto >> pos_x >> pos_y >> textSize){
        menu.emplace_back(font, texto, std::make_pair(pos_x * cFactor, pos_y * cFactor), textSize * cFactor, sf::Color::White);
    }
}

Menu::~Menu() = default;

void Menu::draw() {
    auto& canvas = render<sf::RenderWindow>::get_instance(
            sf::VideoMode(myWindow::modeWidth, myWindow::modeHeight), myWindow::title)->get();
    for(int i = 0 ; i < MAX_MAIN_MENU ; ++i){
        canvas->draw(menu[i].getFont());
    }
}

void Menu::MoveUp() {
    if(MenuSelected  >= 0){
        menu[MenuSelected].setFillColor(Color::White);
        MenuSelected--;
        if(MenuSelected == -1){
            MenuSelected = 3;
        }
        menu[MenuSelected].setFillColor(Color::Blue);
    }
}

void Menu::MoveDown() {
    if(MenuSelected + 1 <= MAX_MAIN_MENU){
        menu[MenuSelected].setFillColor(Color::White);
        MenuSelected ++ ;
        if(MenuSelected == MAX_MAIN_MENU){
            MenuSelected = 0;
        }
        menu[MenuSelected].setFillColor(Color::Blue);
    }
}

int Menu::GetPressedItem() const {
    return MenuSelected;
}
