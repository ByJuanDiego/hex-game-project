//
// Created by Juan Diego Castro Padilla on 6/05/22.
//

#ifndef CS2013_PROJECT_AI_H
#define CS2013_PROJECT_AI_H

#include "Board.h"

class AI{
private:
    float alphaBetaPruned(Board& board, int& depth, bool isMaximizing, int x, int y,
                          Player current, float Alpha, float Beta, Player computadora);
    static float getHeuristicScore(Board& board, Player current, Player computadora);
public:
    std::pair <int, int> next(Board& board, Player p);
};

#endif //CS2013_PROJECT_AI_H
