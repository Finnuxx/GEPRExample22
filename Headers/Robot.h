//
// Created by A1 on 18.06.2020.
//

#include "Point.h"
#include "Renderer.h"
#include "MoveStrategy.h"

#ifndef GEPREXAMPLE22_ROBOT_H
#define GEPREXAMPLE22_ROBOT_H

class Robot: public Renderer {
private:
    Point* location;
    MoveStrategy* strategy;
    int resourceCounter;

public:
    Robot(Point *location, MoveStrategy *strategy, int resourceCounter) : location(location), strategy(strategy),
                                                                          resourceCounter(resourceCounter) {}

    void move() {
        this->strategy->move(location);
    }

    void move2() {
        this->strategy->move2(location);
    }

    string render() {
        return "x";
    }

    bool isCoordinate(int x, int y) {
        return location->getX() == x && location->getY() == y;
    }

    string getCoordinateKey() {
        return to_string(location->getX())+ ':' + to_string(location->getY());
    }

    void harvest(int amount) {
        resourceCounter += amount;
    }

    int getResourceCounter() const {
        return resourceCounter;
    }
};

#endif //GEPREXAMPLE22_ROBOT_H
