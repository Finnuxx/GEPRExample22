//
// Created by A1 on 18.06.2020.
//

#include <string>
#include "Point.h"
#include "Renderer.h"
#include "Robot.h"

using namespace std;

#ifndef GEPREXAMPLE22_RESOURCE_H
#define GEPREXAMPLE22_RESOURCE_H

class Resource: public Renderer {
private:
    int value;

public:
    Resource(int value) :  value(value) {}

    int getValue() const {
        return value;
    }

    string render() {
        return to_string(this->value);
    }

    void harvest(Robot* r) {
        if (value > 0) {
            value -= 1;
            r->harvest(1);
        }
    }
};

#endif //GEPREXAMPLE22_RESOURCE_H
