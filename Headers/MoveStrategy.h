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
    int xBoundary = 100; // currently we think of symmetrical fields (square)
    int yBoundary = 100;

    int newCoordinate(int value) {
        int newCoordinate = value + Utility::randomMove();

        return newCoordinate >= lowerBoundary
               ? newCoordinate <= xBoundary
                 ? newCoordinate
                 : xBoundary
               : lowerBoundary
                ;

    }

    int moveLeftUp(int value) {
        int moveLeft = value - 1;

        return moveLeft >= lowerBoundary
               ? moveLeft <= xBoundary
                 ? moveLeft
                 : xBoundary
               : lowerBoundary
                ;
    }

    int moveRightDown(int value) {
        int moveLeft = value + 1;

        return moveLeft >= lowerBoundary
               ? moveLeft <= xBoundary
                 ? moveLeft
                 : xBoundary
               : lowerBoundary
                ;
    }



public:

    MoveStrategy(int xBoundary, int yBoundary) : xBoundary(xBoundary), yBoundary(yBoundary) {}

    void move(Point* p) {
        p->setX(this->newCoordinate(p->getX()));
        p->setY(this->newCoordinate(p->getY()));
    }

    void move2(Point* p) {
        if (p->getX() > 0) {
            p->setX(this->moveLeftUp(p->getX()));
        } else if (p->getY() > 0) {
            p->setY(this->moveLeftUp(p->getY()));
        }

    }


};

#endif //GEPREXAMPLE22_MOVESTRATEGY_H
