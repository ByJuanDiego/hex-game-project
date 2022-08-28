//
// Created by Juan Diego Castro Padilla on 3/07/22.
//

#ifndef CS2013_PROJECT_RECTANGLE_H
#define CS2013_PROJECT_RECTANGLE_H

#include "figure.h"
#include "Word.h"
#include <string>

class rectangle : public figure{
private:
    float width = 0;
    float height = 0;
    sf::RectangleShape* rectangleSprite;
public:
    explicit rectangle(const float& w, const float& h, const float& x, const float& y, const int& n);
    sf::RectangleShape* getShape() const;

    void mouseEnterEvent(const std::string& Color);
    void mouseLeaveEvent();

    bool isOnBound(int x, int y) override;
    void setColor(int n) override;
};


#endif //CS2013_PROJECT_RECTANGLE_H
