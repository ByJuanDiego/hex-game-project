//
// Created by Juan Diego Castro Padilla on 3/07/22.
//

#include "figure.h"


float figure::getPositionX() const{
    return this->posicionWindow.first;
}

float figure::getPositionY() const{
    return this->posicionWindow.second;
}

figure::figure(const float &x, const float &y, const int &n) {
    id = n;
    posicionWindow = {x, y};
    coloreado = false;
    color = 2;
}

bool figure::getColored() const{
    return this->coloreado;
}

int figure::getColor() const{
    return this->color;
}

void figure::setColored(int n) {
    if (n == 0 || n == 1){
        this->coloreado = n;
    }
}
