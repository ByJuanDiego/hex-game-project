//
// Created by Juan Diego Castro Padilla on 3/07/22.
//

#ifndef CS2013_PROJECT_RECTANGLEFACTORY_H
#define CS2013_PROJECT_RECTANGLEFACTORY_H

#include "rectangle.h"

template<typename ... CreateParams>
class RectangleFactory{
private:
    std::unordered_map<std::string, std::function<rectangle*(CreateParams...)>> callbacks;
    inline static RectangleFactory* instance {};
public:
    rectangle* create(const std::string& key, CreateParams... params){
        return callbacks.at(key)(params...);
    }
    bool atach_function(const std::string& key, const std::function<rectangle*(CreateParams...)>& createFunction) {
        return callbacks.insert({key, createFunction}).second;
    }
    static RectangleFactory* get_instance() noexcept{
        if (instance == nullptr){
            instance = new RectangleFactory();
        }
        return instance;
    }
};
// Registrando la creacion de un rectangulo
namespace {
    auto crearRectangulo = RectangleFactory<float, float, float, float, int>::get_instance()
        -> atach_function("rectangulo", [](float x, float y, float w, float h, int n){
        return new rectangle(w, h, x, y, n);
    });
    auto crearCuadrado = RectangleFactory<float, float, float, int>::get_instance()
            -> atach_function("cuadrado", [](float x, float y, float sz, int n){
                return new rectangle(sz, sz, x, y, n);
            });
}


#endif //CS2013_PROJECT_RECTANGLEFACTORY_H
