//
// Created by Juan Diego Castro Padilla on 20/06/22.
//

#ifndef CS2013_PROJECT_HEXAGON_H
#define CS2013_PROJECT_HEXAGON_H

#include "figure.h"




class hexagon : public figure{
private:

    sf::CircleShape* hexSprite {};
    float radio {};
    pos2D<int> posicionTabla {};

public:

    explicit hexagon() = default;
    explicit hexagon(const float& r, const float& x, const float& y, const int& n, const int& i, const int& j);
    pos2D<int> getPositionTabla() const;
    void mousePressedEvent(int turno);
    sf::CircleShape* getShape() const;
    bool isOnBound(int x, int y) override;
    void setColor(int n) override;

};

#endif //CS2013_PROJECT_HEXAGON_H
