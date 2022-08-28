//
// Created by hola on 9/6/2022.
//

#ifndef UNTITLED8_MENU_H
#define UNTITLED8_MENU_H

#pragma once
#include "Word.h"
#include "Render.h"
#define MAX_MAIN_MENU 4

using namespace std;

class Menu{
public:
    Menu();
    ~Menu();
    void draw();
    void MoveUp();
    void MoveDown();
    int GetPressedItem() const;
private:
    int MenuSelected;
    sf::Font font;
    vector<Word> menu;
};

#endif //UNTITLED8_MENU_H
