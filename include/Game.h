//
// Created by Juan Diego Castro Padilla on 6/05/22.
//

#ifndef CS2013_PROJECT_GAME_H
#define CS2013_PROJECT_GAME_H

#include "AI.h"
#include "Menu.h"
#include "Options.h"

class Game {

private:

    Player computer {};
    Player player {};
    AI robotAI;
    Board board;
    Menu menu;
    Options opciones;
    bool turnoSeleccionado = false;

public:

    Game() = default;
    explicit Game(AI& robotAI): robotAI(robotAI){}
    void ejecutar();

private:

    Player IniciarJuego();
    int MostrarMenu();
    void MostrarOpciones();
    void MostrarInstrucciones();
    void MostrarGanador(Player winner);
    std::pair<bool, std::pair<int, int>> computerTurn();
    bool playerTurn(pos2D<int> pos);

};

#endif //CS2013_PROJECT_GAME_H
