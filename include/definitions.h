//
// Created by Juan Diego Castro Padilla on 5/05/22.
//

#ifndef CS2013_PROJECT_DEFINITIONS_H
#define CS2013_PROJECT_DEFINITIONS_H

//C++ Standard Libraries {{{1
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <unordered_map>
#include <queue>
#include <array>
#include <algorithm>
#include <map>
#include <cmath>
#include <set>
#include <functional>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <random>

//Third-party Libraries {{{1
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

#define BOARD_SIZE 11

#if defined _WIN32 || defined _WIN64
    constexpr float cFactor = 0.5f;
#elif defined __APPLE__
    constexpr float cFactor = 0.7f;
#elif __linux__
    constexpr float cFactor = 0.5f;
#endif

//Structs {{{1
struct myWindow {
    constexpr inline static const char* title = "\"Hex-Game\"";
    constexpr inline static unsigned int modeWidth = 2200 * cFactor;
    constexpr inline static unsigned int modeHeight = 1600 * cFactor;
};

//Enums {{{1
enum class Player {
    BLACK, WHITE
};

//Templates {{{1
template <typename T>
using pos2D = std::pair<T, T>;

//Herencia{{{1
class OpSprite: public sf::Drawable{
    sf::Sprite _sprite;
    sf::Texture _texture;
    std::string direccion;
    int x=0; int y=0;
public:
    OpSprite(const std::string& str, int _x, int _y):direccion(str),x(_x),y(_y){
        _texture.loadFromFile(direccion);
        _sprite.setTexture(_texture);
        _sprite.setPosition(x * cFactor, y * cFactor);
    }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override{
        target.draw(_sprite, states);
    } // para dibujar
};


#endif //CS2013_PROJECT_DEFINITIONS_H
