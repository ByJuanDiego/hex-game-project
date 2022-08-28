//
// Created by Juan Diego Castro Padilla on 20/06/22.
//

#ifndef CS2013_PROJECT_RENDER_H
#define CS2013_PROJECT_RENDER_H

#include <SFML/Graphics.hpp>
#include "definitions.h"

#include <memory>

using namespace std;


template <typename T>
using smart_ptr = std::unique_ptr<T>;

template <typename T, typename ...Params>
auto make_smart (Params ...params) { return std::make_unique<T>(params...); };

template <typename T>
class render {
    smart_ptr<T> data {};
    inline static render<T>* instance;
    template <typename ...Params>
    explicit render(Params... params): data(make_smart<T>(params...)) {}
public:
    template <typename ...Params>
    static render<T>* get_instance(Params ...params) {
        if (instance == nullptr) instance = new render<T>(params...);
        return instance;
    }
    smart_ptr<T>& get(){ return data; }
};


#endif //CS2013_PROJECT_RENDER_H
