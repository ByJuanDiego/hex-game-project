//
// Created by Juan Diego Castro Padilla on 3/07/22.
//

#include "Options.h"

Options::Options() {
    if(!font.loadFromFile("../assets/fonts/ChrustyRock.ttf")){
        cout<< "No font";
    }
    buttons.reserve(2);

    string componente, texto;
    int id;
    float x, y, w, h, textSize;
    ifstream file("../assets/components/labels.txt");

    while (file >> componente >> id >> x >> y >> w >> h >> texto >> textSize){
        rectangle* currentRectangle = RectangleFactory<float, float, float, float, int>::get_instance()->create(componente, x * cFactor, y * cFactor, w * cFactor, h * cFactor, id);
        Word currentWord(font, texto, {x * cFactor, y * cFactor}, textSize * cFactor, sf::Color::Black);

        // Esta parte es para centrar el texto con el rectangulo
        const auto bounds(currentWord.texto.getLocalBounds());
        const auto box(currentRectangle->getShape()->getSize());
        currentWord.texto.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
        buttons.emplace_back(currentRectangle, currentWord);
    }
}

void Options::draw() {
    auto& canvas = render<sf::RenderWindow>::get_instance(
            sf::VideoMode(myWindow::modeWidth, myWindow::modeHeight), myWindow::title)->get();
    for (auto& item: buttons){
        canvas->draw(*item.first->getShape());
        canvas->draw(item.second.getFont());
    }
}
