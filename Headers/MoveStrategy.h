//
// Created by A1 on 18.06.2020.
//

#include "Point.h"
#include "Utility.h"

#ifndef GEPREXAMPLE22_MOVESTRATEGY_H
#define GEPREXAMPLE22_MOVESTRATEGY_H

class MoveStrategy {
private:
    int lowerBoundary = 0;
    int upperBoundary = 100; // currently we think of symmetrical fields (square)

    int newCoordinate(int value) {
        int newCoordinate = value + Utility::randomMove();

        return newCoordinate >= lowerBoundary
               ? newCoordinate <= upperBoundary
                 ? newCoordinate
                 : upperBoundary
               : lowerBoundary
                ;

    }

public:

    MoveStrategy(int upperBoundary) : upperBoundary(upperBoundary) {}

    void move(Point* p) {
        p->setX(this->newCoordinate(p->getX()));
        p->setY(this->newCoordinate(p->getY()));
    }


};

#endif //GEPREXAMPLE22_MOVESTRATEGY_H
