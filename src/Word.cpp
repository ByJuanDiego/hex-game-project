//
// Created by Juan Diego Castro Padilla on 26/06/22.
//

#include "../include/Word.h"

Word::Word(sf::Font &font, const std::string &str, const pos2D<float>& pos, const float& fontSize, sf::Color color) : mensaje(str), position(pos){
    texto.setFont(font);
    texto.setFillColor(color);
    texto.setString(str);
    texto.setCharacterSize(static_cast<int>(fontSize));
    texto.setPosition(position.first, position.second);
}

sf::Text& Word::getFont() {
    return texto;
}

void Word::setFillColor(sf::Color nuevo) {
    texto.setFillColor(nuevo);
}
