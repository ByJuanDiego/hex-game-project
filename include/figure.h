//
// Created by Juan Diego Castro Padilla on 3/07/22.
//

#ifndef CS2013_PROJECT_FIGURE_H
#define CS2013_PROJECT_FIGURE_H

#include "definitions.h"
using namespace std;

inline unordered_map<int, sf::Color> mapaColores {
        {0, sf::Color::Blue},
        {1, sf::Color::Red},
        {2, sf::Color::White}
};


class figure {
protected:

    pos2D<float> posicionWindow {};
    int id {}; // para idenfiticar con el algoritmo para la computadora
    int color {};  // 0 if red, 1 if blue
    bool coloreado {};

public:

    explicit figure() = default;
    explicit figure(const float& x, const float& y, const int& n);

    float getPositionX() const;
    float getPositionY() const;
    bool getColored() const;
    int getColor() const;
    void setColored(int n);

    virtual void setColor(int n) = 0;
    virtual bool isOnBound(int x, int y) = 0;

};


#endif //CS2013_PROJECT_FIGURE_H
