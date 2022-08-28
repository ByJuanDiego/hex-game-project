//
// Created by Juan Diego Castro Padilla on 20/06/22.
//

#ifndef CS2013_PROJECT_HEXAGONFACTORY_H
#define CS2013_PROJECT_HEXAGONFACTORY_H

#include "hexagon.h"

template<typename ... CreateParams>
class HexagonFactory{
private:
    std::unordered_map<std::string, std::function<hexagon*(CreateParams...)>> callbacks;
    inline static HexagonFactory* instance {};
public:
    hexagon* create(const std::string& key, CreateParams... params){
        return callbacks.at(key)(params...);
    }
    bool atach_function(const std::string& key, const std::function<hexagon*(CreateParams...)>& createFunction) {
        return callbacks.insert({key, createFunction}).second;
    }
    static HexagonFactory* get_instance() noexcept{
        if (instance == nullptr){
            instance = new HexagonFactory();
        }
        return instance;
    }
};
// Registrando la creacion de un hexagon
namespace {
    auto crearHexagono = HexagonFactory<float, float, float, int, int, int>::get_instance()
        -> atach_function("hexagono", [](float x, float y, float r, int n, int i, int j){
        return new hexagon(r, x, y, n, i, j);
    });
}


#endif //CS2013_PROJECT_HEXAGONFACTORY_H
