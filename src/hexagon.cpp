//
// Created by Juan Diego Castro Padilla on 20/06/22.
//

#include "../include/hexagon.h"

hexagon::hexagon(const float& r, const float& x, const float& y, const int& n, const int& i, const int& j) : figure(x, y, n) {
    radio = r;
    posicionTabla  = {i, j};
    hexSprite = new sf::CircleShape(radio, 6);
    hexSprite->setPosition({posicionWindow.first, posicionWindow.second});
}

pos2D<int> hexagon::getPositionTabla() const{
    return this->posicionTabla;
}

bool hexagon::isOnBound(int x, int y){
    auto centerX = hexSprite->getPosition().x + radio;
    auto centerY = hexSprite->getPosition().y + radio;
    // (radio-10) Para asegurar que no haya superposicion entre hex
    return std::sqrt(std::pow(x-centerX, 2) + std::pow(y-centerY, 2)) < (radio-10);
}

void hexagon::mousePressedEvent(int turno) {
    coloreado = true;
    color = turno;
    hexSprite->setFillColor(mapaColores[color]);
}

void hexagon::setColor(int n) {
    if(n == 0 || n == 1 || n == 2) {
        this->hexSprite->setFillColor(mapaColores[n]);
        this->color = n;
    }
}

sf::CircleShape* hexagon::getShape() const {
    return this->hexSprite;
}
