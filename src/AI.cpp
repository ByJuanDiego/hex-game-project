//
// Created by Juan Diego Castro Padilla on 6/05/22.
//

#include "../include/AI.h"

const float MAX = 1000;
const float MIN = -1000;

float AI::getHeuristicScore(Board& board, Player current, Player computadora){
    Player human = (computadora==Player::BLACK)? Player::WHITE : Player::BLACK;
    std::vector<std::pair<int, int>> computerPath = board.getShortestPath(computadora);
    std::vector<std::pair<int, int>> playerPath = board.getShortestPath(human);
    auto getScoreForPath = [&board](std::vector<std::pair<int, int>>& path)
    {
        if (path.empty()) {
            return 0.0f;
        }

        float vacios = 0.0f;
        for (const auto & [x, y]: path){
            if (board.getBoard()[x][y] == '+'){
                vacios++;
            }
        }
        return (vacios == 0.0f)? -30.0f : vacios;
    };
    float computerScore = getScoreForPath(computerPath);
    float playerScore = getScoreForPath(playerPath);

    return playerScore - computerScore;
}

float AI::alphaBetaPruned(Board &board, int& depth, bool isMaximizing, int x, int y, Player current, float Alpha, float Beta, Player computadora) {
    float alpha = Alpha;
    float beta = Beta;
    if (depth == 2 || board.win(x, y)){
        return getHeuristicScore(board, current, computadora);
    }

    Player nextPlayer = (current==Player::BLACK)? Player::WHITE : Player::BLACK;
    auto blank = board.getEmpty();
    if (!blank.empty()){
        if (isMaximizing)
        {
            float bestScore = MIN;
            for (std::pair<int, int> &i: blank)
            {
                board.place(i.first, i.second, nextPlayer);
                float score = alphaBetaPruned(board, ++depth, false, i.first, i.second, nextPlayer, alpha, beta, computadora);
                board.placeEmpty(i.first, i.second);
                bestScore = std::max(score, bestScore);
                alpha = std::max(alpha, bestScore);
                if (beta <= alpha){
                    break;
                }
            }
            return bestScore;
        }
        else
        {
            float bestScore = MAX;
            for (std::pair<int, int> &i: blank)
            {
                board.place(i.first, i.second, nextPlayer);
                float score = alphaBetaPruned(board, ++depth, true, i.first, i.second, nextPlayer, alpha, beta, computadora);
                board.placeEmpty(i.first, i.second);
                bestScore = std::min(score, bestScore);
                beta = std::min(beta, bestScore);
                if (beta <= alpha) {
                    break;
                }
            }
            return bestScore;
        }
    }else{
        return getHeuristicScore(board, current, computadora);
    }
}



std::pair<int, int> AI::next(Board& board, Player current){
    Player computadora = current;
    auto blank = board.getEmpty();
    float bestScore = MIN;
    std::pair<int, int> move;
    for (std::pair<int, int> &i : blank) {
        int depth = 0;
        int x = i.first;
        int y = i.second;

        board.place(x, y, current);
        float score = alphaBetaPruned(board, depth,false, x, y, current, MAX, MIN, computadora);
        board.placeEmpty(x, y);
        if (score >= bestScore){
            bestScore = score;
            move = {x, y};
        }
    }

    return move;
}
