//
// Created by Juan Diego Castro Padilla on 26/06/22.
//

#ifndef CS2013_PROJECT_WORD_H
#define CS2013_PROJECT_WORD_H

#include "definitions.h"

struct Word{
    sf::Text texto;
    std::string mensaje;
    pos2D<float> position;
    explicit Word(sf::Font& font, const std::string& str, const pos2D<float>& pos, const float& textSize, sf::Color color);
    sf::Text& getFont();
    void setFillColor(sf::Color nuevo);
};


#endif //CS2013_PROJECT_WORD_H
