//
// Created by A1 on 18.06.2020.
//

#include <string>

using namespace std;

#ifndef GEPREXAMPLE22_RENDERER_H
#define GEPREXAMPLE22_RENDERER_H

class Renderer {
    virtual string render();
};

string Renderer::render() {
    return string();
}

#endif //GEPREXAMPLE22_RENDERER_H
