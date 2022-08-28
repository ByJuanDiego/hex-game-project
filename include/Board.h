//
// Created by Juan Diego Castro Padilla on 6/05/22.
//

#ifndef CS2013_PROJECT_BOARD_H
#define CS2013_PROJECT_BOARD_H

#include "definitions.h"
#include "hexagon.h"

class Board {

private:

    static int direct[6][2];
    static char white;
    static char black;
    static char empty;
    int size;
    std::vector<std::vector<char>> board;
    std::unordered_map<int, hexagon*> tablero;

private:

    bool inBoard(int x, int y) const;
    void borders(int x, int y, std::vector<bool>& condition, char side);
    void bfsSearch(std::vector<std::pair<int,int>>& start, std::vector<bool>& condition);
    std::vector<std::vector<std::pair<int, int>>> dijkstra(std::pair<int, int> src, char currentPlayer, std::vector<std::vector<char>> circuito, int filas, int columnas);
    std::vector<std::pair<int, int>> vecino(int x, int y, std::vector<std::vector<bool>>& visitados, char currentPlayer, std::vector<std::vector<char>> circuito);

public:

    explicit Board() = default;
    explicit Board(int size);
    void crearTablero();

    bool place(int x, int y, Player p);
    bool placeEmpty(int x, int y);
    std::vector<std::pair<int,int>> getEmpty();
    std::vector<std::vector<char>>& getBoard();
    std::vector<std::pair<int, int>> getShortestPath(Player player);
    bool win(int x, int y);
    std::unordered_map<int, hexagon*>& getTablero();
};


#endif //CS2013_PROJECT_BOARD_H
