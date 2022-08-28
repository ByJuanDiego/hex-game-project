//
// Created by Juan Diego Castro Padilla on 6/05/22.
//

#include "../include/Game.h"

void Game::ejecutar(){
    int opcion = 0;

    while (true){
        if (opcion == 0){// Opcion por defecto (Mostrar menu)
            opcion = MostrarMenu();
        }
        else if (opcion == 1){// Iniciar una partida
            Player winner = IniciarJuego();
            MostrarGanador(winner);
            opcion = 0;
        }
        else if (opcion == 2){// Mostrar opciones para la partida
            MostrarOpciones();
            opcion = 0;
        }
        else if (opcion == 3){// Como se juega hex
            MostrarInstrucciones();
            opcion = 0;
        }
        else if (opcion == 4){// Salir
            break;
        }
    }
}

std::pair<bool, std::pair<int, int>> Game::computerTurn(){
    auto move = robotAI.next(board, computer);
    board.place(move.first, move.second, computer);
    return {board.win(move.first, move.second), {move.first, move.second}};
}

bool Game::playerTurn(pos2D<int> pos){
    board.place(pos.first, pos.second, player);
    return board.win(pos.first, pos.second);
}

int Game::MostrarMenu() {
    auto& canvas = render<sf::RenderWindow>::get_instance(
            sf::VideoMode(myWindow::modeWidth, myWindow::modeHeight), myWindow::title)->get();
    canvas->clear();

    while (canvas->isOpen()){
        sf::Event event {};

        while (canvas->pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Up:
                            menu.MoveUp();
                            break;

                        case sf::Keyboard::Down:
                            menu.MoveDown();
                            break;

                        case sf::Keyboard::Return:
                            switch (menu.GetPressedItem())
                            {
                                case 0 ... 2:
                                    return menu.GetPressedItem()+1;
                                case 3:
                                    canvas->close();
                                    return 4;
                            }
                            break;
                    }
                    break;
                case sf::Event::Closed:
                    return 4;

            }
        }
        canvas->clear();
        menu.draw();
        canvas->display();
    }
    return 1;
}

Player Game::IniciarJuego() {
    board = Board(BOARD_SIZE);
    board.crearTablero();

    if (!turnoSeleccionado){
        player = Player::WHITE;
        computer = Player::BLACK;
    }
    int turn = (computer == Player::BLACK ? 0:1);

    auto& canvas = render<sf::RenderWindow>::get_instance(
            sf::VideoMode(myWindow::modeWidth, myWindow::modeHeight), myWindow::title)->get();

    sf::Texture texture;
    texture.loadFromFile("../assets/images/map.png");

    sf::Sprite sprite(texture);
    sprite.setScale({2.1f*cFactor, 2.1f*cFactor});
    sprite.setPosition(207*cFactor, 120*cFactor);

    while (canvas->isOpen()){
        sf::Event event {};
        bool win = false;
        while (canvas->pollEvent(event))
        {// Patron Observer
            if (turn){
                hexagon* selectedHex;
                switch (event.type) {
                    case sf::Event::Closed:
                        canvas->close();
                    case sf::Event::MouseButtonPressed:
                        sf::Vector2i mousePos = sf::Mouse::getPosition(*canvas);
                        auto current_x = mousePos.x;
                        auto current_y = mousePos.y;
                        for (auto& [id, hex] : board.getTablero()){
                            if (hex->isOnBound(current_x, current_y) && !hex->getColored()){
                                selectedHex = hex;
                                hex->mousePressedEvent(static_cast<int>(player));
                                if (playerTurn(selectedHex->getPositionTabla())){
                                    return player;
                                }
                                turn = !turn;
                                break;
                            }
                        }
                }
            }
            else{
                auto [w, jugada] = computerTurn();
                for (auto& [id, hex] : board.getTablero()){
                    if (hex->getPositionTabla() == jugada){
                        hex->mousePressedEvent(static_cast<int>(computer));
                        break;
                    }
                }
                if (w){
                    return computer;
                }
                turn = !turn;
            }
        }

        canvas->clear();
        canvas->draw(sprite);
        for (auto& [id, hex]: board.getTablero()){
            canvas->draw(*hex->getShape());
        }
        canvas->display();
    }
}

void Game::MostrarOpciones() {
    auto& canvas = render<sf::RenderWindow>::get_instance(
            sf::VideoMode(myWindow::modeWidth, myWindow::modeHeight), myWindow::title)->get();

    float prior_x = 0, prior_y = 0;
    float actual_x = 0, actual_y = 0;

    while (canvas->isOpen())
    {
        sf::Event event {};
        while (canvas->pollEvent(event))
        {// Patron Observer
            switch (event.type) {
                case sf::Event::MouseButtonPressed:
                    for (const auto&[rectangle, word]: opciones.buttons){
                        if (rectangle->isOnBound(actual_x, actual_y)){
                            if (word.mensaje == "Blue"){
                                player = Player::BLACK;
                                computer = Player::WHITE;
                            }
                            else{
                                player = Player::WHITE;
                                computer = Player::BLACK;
                            }
                            turnoSeleccionado = true;
                            return;
                        }
                    }
                    break;
                case sf::Event::MouseMoved:
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*canvas);
                    actual_x = mousePos.x;
                    actual_y = mousePos.y;

                    for (const auto&[rectangle, word]: opciones.buttons) {
                        if (rectangle->isOnBound(actual_x, actual_y)) {
                            rectangle->mouseEnterEvent(word.mensaje);
                        }
                        else if (rectangle->isOnBound(prior_x, prior_y)){
                            rectangle->mouseLeaveEvent();
                        }
                    }
                    prior_x = actual_x;
                    prior_y = actual_y;
                    break;
            }
        }
        canvas->clear();
        opciones.draw();
        canvas->display();
    }
}

void Game::MostrarGanador(Player winner){
    auto& canvas = render<sf::RenderWindow>::get_instance(sf::VideoMode(myWindow::modeWidth, myWindow::modeHeight), myWindow::title)->get();

    sf::Font font;
    font.loadFromFile("../assets/fonts/ChrustyRock.ttf");
    Word* WinnerMessage = new Word(font, ((winner == player)? "Ganaste!":"Perdiste!"), {850 * cFactor, 500 * cFactor}, 100, sf::Color::White);
    Word* LeaveMessage = new Word(font, "(Click en cualquier parte para salir)", {400 * cFactor, 700 * cFactor}, 80, sf::Color::White);

    while (canvas->isOpen()){
        sf::Event event{};
        while(canvas->pollEvent(event)){
            if (event.type == sf::Event::MouseButtonPressed){
                return;
            }
        }
        canvas->clear();
        canvas->draw(WinnerMessage->getFont());
        canvas->draw(LeaveMessage->getFont());
        canvas->display();
    }
}

void Game::MostrarInstrucciones() {
    std::vector<OpSprite*> Sprites;
    std::string ruta;
    int x, y;
    sf::Font font;
    font.loadFromFile("../assets/fonts/ChrustyRock.ttf");
    ifstream file("../assets/components/imagenes.txt");
    while (file >> ruta >> x >> y){
        Sprites.emplace_back(new OpSprite(ruta, x, y));
    }

    std::pair<rectangle*, Word*> Salida;
    Salida.first = RectangleFactory<float, float, float, int>::get_instance()->create("cuadrado", 120 * cFactor, 1100 * cFactor, 200 * cFactor, 0);
    Salida.second = new Word(font, "Salir", {120 * cFactor, 1100 * cFactor}, 40 * cFactor, sf::Color::Black);
    const auto bounds(Salida.second->texto.getLocalBounds());
    const auto box(Salida.first->getShape()->getSize());
    Salida.second->texto.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);

    auto& canvas = render<sf::RenderWindow>::get_instance(
            sf::VideoMode(myWindow::modeWidth, myWindow::modeHeight), myWindow::title)->get();

    int actual_x, actual_y;
    while (canvas->isOpen()){
        sf::Event event{};
        while(canvas->pollEvent(event)){
            if (event.type==sf::Event::Closed){
                canvas->close();
            }
            sf::Vector2i mousePos = sf::Mouse::getPosition(*canvas);
            actual_x = mousePos.x;
            actual_y = mousePos.y;
            if (event.type==sf::Event::MouseButtonPressed){
                if (Salida.first->isOnBound(actual_x, actual_y)){
                    return;
                }
            }
        }
        canvas->clear();
        for (auto& imagen : Sprites){
            canvas->draw(*imagen);
        }
        canvas->draw(*Salida.first->getShape());
        canvas->draw(Salida.second->getFont());
        canvas->display();
    }
}
