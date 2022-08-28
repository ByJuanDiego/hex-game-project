//
// Created by Juan Diego Castro Padilla on 3/07/22.
//

#include "rectangle.h"

rectangle::rectangle(const float& w, const float& h, const float& x, const float& y, const int& n) : figure(x, y, n) {
    width = w;
    height = h;
    rectangleSprite = new sf::RectangleShape({w, h});
    rectangleSprite->setPosition({posicionWindow.first, posicionWindow.second});
}

sf::RectangleShape* rectangle::getShape() const {
    return rectangleSprite;
}

bool rectangle::isOnBound(int x, int y) {
    return (x > posicionWindow.first && x < posicionWindow.first + width) && (y > posicionWindow.second && y < posicionWindow.second + height);
}

void rectangle::setColor(int n) {
    if(n == 0 || n == 1 || n == 2) {
        this->rectangleSprite->setFillColor(mapaColores[n]);
        this->color = n;
    }
}

void rectangle::mouseEnterEvent(const std::string& Color){
    color = (Color == "Red")? 1 : 0;
    coloreado = true;
    rectangleSprite->setFillColor(mapaColores[color]);
}

void rectangle::mouseLeaveEvent(){
    color = 2;
    coloreado = false;
    rectangleSprite->setFillColor(mapaColores[color]);
}
