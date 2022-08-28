//
// Created by Juan Diego Castro Padilla on 6/05/22.
//

#include "../include/Board.h"
#include "../include/HexagonFactory.h"
#include <map>
#include <fstream>
#include <random>

// variables estaticas
int Board::direct[6][2] = {
                {-1, 0},
                {-1, 1},
                {0,-1},
                {0,1},
                {1, -1},
                {1, 0}
        };
char Board::white = 'W';
char Board::black = 'B';
char Board::empty = '+';

std::unordered_map<int, hexagon*>& Board::getTablero(){
    return tablero;
}

bool Board::inBoard(int x, int y) const{
    return (x < size && y < size && x >= 0 && y >= 0);
}

void Board::crearTablero(){
    HexagonFactory<float, float, float, int, int, int>* hf = HexagonFactory<float, float, float, int, int, int>::get_instance();

    std::ifstream file("../assets/components/hexagonos.txt");
    int id, i, j;
    float x, y, radio;
    string component;

    hexagon* current;
    while (file >> component >> id >> x >> y >> radio >> i >> j){
        current = hf->create(component, x*cFactor, y*cFactor, radio*cFactor, id, i, j);
        tablero.insert({id, current});
    }
}



void Board::borders(int x, int y, std::vector<bool>& condition, char side){
    if(side == black)
    {
        if(y == 0)
            condition[0] = true;
        if(y == size - 1)
            condition[1] = true;

    }
    else
    {
        if(x == 0)
            condition[0] = true;
        if(x == size - 1)
            condition[1] = true;
    }
}

Board::Board(int size) : size(size),board(size,std::vector<char>(size,'+')) {
}


bool Board::place(int x, int y, Player p){
    if(inBoard(x,y) && board[x][y] == empty)
    {
        if (p == Player::BLACK)
            board[x][y] = black;
        else
            board[x][y] = white;
        return true;
    }
    return false;
}

bool Board::placeEmpty(int x, int y){
    if(inBoard(x,y) && board[x][y] != empty)
    {
        board[x][y] = empty;
        return true;
    }
    return false;
}

std::vector<std::pair<int,int>> Board::getEmpty(){
    std::vector<std::pair<int,int>> blankSpots;
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
            if(board[i][j] == empty)
                blankSpots.emplace_back(i,j);
    }
    return blankSpots;
}

std::vector<std::vector<char>>& Board::getBoard(){
    return board;
}

void Board::bfsSearch(std::vector<std::pair<int,int>>& start, std::vector<bool>& condition){
    if(!start.empty()){
        int x = start.at(0).first;
        int y = start.at(0).second;
        char side = board[x][y];
        std::vector<std::vector<bool>> visited(size, std::vector<bool>(size));
        std::queue<std::pair<int,int>> trace;
        for (const std::pair<int, int> & pos : start){
            trace.push(pos);
            visited[pos.first][pos.second] = true;
        }
        while(!(trace.empty())){
            auto top = trace.front();
            borders(top.first, top.second, condition, side);
            trace.pop();

            for(auto & [xDirect, yDirect] : direct){
                int xCursor = (top.first + xDirect);
                int yCursor = (top.second + yDirect);
                if(inBoard(xCursor, yCursor) && board[xCursor][yCursor] == side && !visited[xCursor][yCursor]) {
                    visited[xCursor][yCursor] = true;
                    trace.push({xCursor,yCursor});
                }
            }
        }
    }
}


bool Board::win(int x, int y){
    if(inBoard(x,y) && board[x][y] != empty)
    {
        std::vector<bool> condition(2, false);
        std::vector<std::pair<int,int>> start(1, std::make_pair(x,y));

        bfsSearch(start, condition);
        return (condition[0] && condition[1]);
    }
    return false;
}

std::pair<int, int> minDistance(
        std::vector<std::vector<bool>>& vistados,
        std::vector<std::vector<float>>& distances,
        std::vector<std::vector<std::pair<int, int>>>& coordenadas,
        std::vector<std::vector<char>>& board
){

    float min = 1000000;
    int min_x, min_y;

    for (int k = 0; k < board.size(); k++) {
        for (int l = 0; l < board[0].size(); l++) {
            if(!vistados[k][l] && distances[k][l] <= min){
                min = distances[k][l];
                min_x = k;
                min_y = l;
            }
        }
    }

    return {min_x, min_y};
}

std::vector<std::pair<int, int>> Board::vecino(int x, int y, std::vector<std::vector<bool>>& visitados, char currentPlayer, std::vector<std::vector<char>> circuito){
    std::vector<std::pair<int, int>> vec;
    for(auto & [xDirect, yDirect] : direct){

        int xCursor = (x + xDirect);
        int yCursor = (y + yDirect);
        if((xCursor < circuito.size() && yCursor < circuito[0].size() && xCursor >= 0 && yCursor >= 0) && !visitados[xCursor][yCursor] && (circuito[xCursor][yCursor] == '+' || circuito[xCursor][yCursor] == currentPlayer)) {
            if (currentPlayer == 'W'){
                if(xCursor!=0){
                    vec.emplace_back(xCursor, yCursor);
                }
            }else{
                if(yCursor!=0){
                    vec.emplace_back(xCursor, yCursor);
                }
            }

        }
    }

    return vec;
}

std::vector<std::pair<int, int>> getCaminos(unsigned int minx, unsigned int miny, std::vector<std::vector<std::pair<int, int>>>& coordsPrev){
    std::vector<std::pair<int, int>> temp;
    int current_x = minx;
    int current_y = miny;

    while (current_x != -1 && current_y != -1){
        temp.emplace_back(current_x, current_y);
        auto [ux, uy] = coordsPrev[current_x][current_y];
        current_x = ux;
        current_y = uy;
    }

    return temp;
}

std::vector<std::vector<int>> crearCostos(std::vector<std::vector<char>>& board, char currentPlayer){
    std::vector<int> fila;
    int filas = static_cast<int>(board.size());
    int columnas = static_cast<int>(board[0].size());

    std::vector<std::vector<int>> costos_celdas(filas, std::vector<int>(columnas,0));

    char rival = (currentPlayer == 'W')? 'B' : 'W';

    for (int i=0; i<filas; ++i){
        for (int j=0; j<columnas; ++j){
            if (board[i][j] == currentPlayer)
                costos_celdas[i][j] = 0;
            else if (board[i][j] == rival)
                costos_celdas[i][j] = 1000000;
            else
                costos_celdas[i][j] = 1;
        }
    }
    return costos_celdas;
}

std::vector<std::vector<std::pair<int, int>>> Board::dijkstra(std::pair<int, int> src, char currentPlayer, std::vector<std::vector<char>> circuito, int filas, int columnas){
    std::vector<std::vector<int>> costosDeViaje = crearCostos(circuito, currentPlayer);
    std::vector<std::vector<bool>> visitados(filas, std::vector<bool>(columnas, false));
    std::vector<std::vector<std::pair<int, int>>> coorsPrev(filas, std::vector<std::pair<int, int>>(columnas));
    std::vector<std::vector<float>> distances(filas, std::vector<float>(columnas, 1000000));

    auto [x, y] = src;
    distances[x][y] = 0;
    coorsPrev[x][y] = {-1, -1};

    for (int i=0; i<filas; ++i){
        for (int j=0; j<columnas; ++j){
            auto [ux, uy] = minDistance(visitados, distances, coorsPrev, circuito);

            auto vecinos = vecino(ux, uy, visitados, currentPlayer, circuito);

            visitados[ux][uy] = true;
            for (auto & [vx, vy] : vecinos){
                if (distances[ux][uy] + costosDeViaje[vx][vy] < distances[vx][vy] && distances[ux][uy] != 1000000){
                    coorsPrev[vx][vy] = {ux, uy};
                    distances[vx][vy] = distances[ux][uy] + costosDeViaje[vx][vy];
                }
            }
        }
    }

    float min = 1000000;
    int camino_infinito=0;

    std::vector<std::pair<int,int>> coordenadas_minimas;

    if (currentPlayer == 'W'){
        unsigned int i = filas-1;
        for (int j=0; j<columnas; j++){
            if(distances[i][j]==1000000){
                camino_infinito++;
            }
            if (min == distances[i][j]){
                coordenadas_minimas.emplace_back(std::pair<int,int>{i,j});
            }
            else if (min > distances[i][j]){
                coordenadas_minimas.clear();
                min = distances[i][j];
                coordenadas_minimas.emplace_back(std::pair<int,int>{i,j});
            }
        }
    }
    else {
        unsigned int j = columnas-1;
        for (int i=0; i<filas; i++){
            if(distances[i][j]==1000000){
                camino_infinito++;
            }
            if (min == distances[i][j]){
                coordenadas_minimas.emplace_back(std::pair<int,int>{i,j});
            }
            else if (min > distances[i][j]){
                coordenadas_minimas.clear();
                min = distances[i][j];
                coordenadas_minimas.emplace_back(std::pair<int,int>{i,j});
            }
        }
    }

    if (camino_infinito == board.size()){
        return {{{-1,-1}}};
    }

    std::vector<std::vector<std::pair<int,int>>> res;
    for(auto& par:coordenadas_minimas){
        std::vector<std::pair<int,int>> camino_corto = getCaminos(par.first, par.second, coorsPrev);
        res.emplace_back(camino_corto);
    }
    return res;
}

std::vector<std::pair<int, int>> Board::getShortestPath(Player player) {
    const char current = (player == Player::WHITE)? 'W' : 'B';
    const char oponent = (current == 'W')? 'B' : 'W';
    int filas, columnas;
    if (current == 'W'){
        filas = static_cast<int>(board.size())+2;
        columnas = static_cast<int>(board[0].size());
    }else{
        filas = static_cast<int>(board.size());
        columnas = static_cast<int>(board[0].size())+2;
    }
    std::vector<std::vector<char>> circuito(filas, std::vector<char>(columnas,' '));

    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            if(current == 'W'){
                if(i == 0 || i == filas - 1){
                    circuito[i][j] = 'W';
                }else{
                    circuito[i][j] = board[i-1][j];
                }
            }else{
                if(j == 0 || j == columnas-1){
                    circuito[i][j] = 'B';
                }else{
                    circuito[i][j] = board[i][j-1];
                }
            }
        }
    }


    std::vector<std::pair<int, int>> starts;

    if (current == 'W'){
        int i=0;
        for (int j=0; j<columnas; j++){
            starts.emplace_back(i, j);
        }
    }
    else{
        int j=0;
        for (int i=0; i<filas; i++){
            starts.emplace_back(i, j);
        }
    }

    std::vector<std::vector<std::pair<int, int>>> caminos_minimos;

    for (auto& [x, y] : starts){
        std::vector<std::vector<std::pair<int,int>>> caminos_cortos = dijkstra({x, y}, current, circuito, filas, columnas);
        if(caminos_cortos[0][0].first != -1 && caminos_cortos[0][0].second != -1){
            for(auto& camino_corto:caminos_cortos){
                caminos_minimos.emplace_back(camino_corto);
            }
        }
    }
    if(caminos_minimos.empty()){
        return {};
    }

    int index = 0;
    std::vector<float> vacios(caminos_minimos.size(), 0);
    int k = 0;
    for (auto& camino:caminos_minimos){
        for (auto& [x, y] : camino){
            if (circuito[x][y] == '+'){
                vacios[k]++;
            }
        }
        k++;
    }

    float min = 1000000;
    for (int n = 0; n < vacios.size(); n++){
        // Camino tiene menos o igual vacios y el tamanio es mas corto
        if (vacios[n] <= min && caminos_minimos[n].size() < caminos_minimos[index].size()){
            min = vacios[n];
            index = n;
        }
        // Camino tienes mas vacios
        else if (vacios[n] < min){
            min = vacios[n];
            index = n;
        }
    }

    std::vector<std::pair<int,int>> res;
    if(current == 'W'){
        for(int i=0; i<caminos_minimos[index].size();i++){
            if(caminos_minimos[index][i].first != 0 && caminos_minimos[index][i].first != filas-1){
                res.emplace_back(std::pair<int,int>{caminos_minimos[index][i].first-1,caminos_minimos[index][i].second});
            }
        }
    }else{
        for(int i=0; i<caminos_minimos[index].size();i++){
            if(caminos_minimos[index][i].second != 0 && caminos_minimos[index][i].second != columnas-1){
                res.emplace_back(std::pair<int,int>{caminos_minimos[index][i].first,caminos_minimos[index][i].second-1});
            }
        }
    }

    return res;
}
