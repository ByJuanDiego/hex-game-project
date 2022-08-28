//
// Created by Juan Diego Castro Padilla on 3/07/22.
//

#ifndef CS2013_PROJECT_OPTIONS_H
#define CS2013_PROJECT_OPTIONS_H

#include "definitions.h"
#include "RectangleFactory.h"
#include "Render.h"
#include "rectangle.h"
#include "Word.h"

struct Options {
    explicit Options();
    void draw();
    sf::Font font;
    std::vector<std::pair<rectangle*, Word>> buttons;
};


#endif //CS2013_PROJECT_OPTIONS_H
