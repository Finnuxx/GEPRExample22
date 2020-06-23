//
// Created by A1 on 18.06.2020.
//

#include "Point.h"
#include "Utility.h"

#ifndef GEPREXAMPLE22_MOVESTRATEGY_H
#define GEPREXAMPLE22_MOVESTRATEGY_H
class MoveStrategy {
public:
    virtual void move(Point* p);
};

void MoveStrategy::move(Point *p) {

}

class RandomMove: public MoveStrategy {
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

public:

    RandomMove(int xBoundary, int yBoundary) : xBoundary(xBoundary), yBoundary(yBoundary) {}

    void move(Point* p) {
        p->setX(this->newCoordinate(p->getX()));
        p->setY(this->newCoordinate(p->getY()));
    }

};

class RowByRowMove: public MoveStrategy {
private:
    int lowerBoundary = 0;
    int xBoundary = 100; // currently we think of symmetrical fields (square)
    int yBoundary = 100;


    int moveLeftOrUp(int value) {
        int moveLeft = value - 1;

        return moveLeft >= lowerBoundary
               ? moveLeft <= xBoundary
                 ? moveLeft
                 : xBoundary
               : lowerBoundary
                ;
    }

    int moveRightOrDown(int value) {
        int moveLeft = value + 1;

        return moveLeft >= lowerBoundary
               ? moveLeft <= xBoundary
                 ? moveLeft
                 : xBoundary
               : lowerBoundary
                ;
    }

public:

    RowByRowMove(int xBoundary, int yBoundary) : xBoundary(xBoundary), yBoundary(yBoundary) {}

    bool isInFirstRow = false;
    bool isInFirstColumn = false;
    bool isRowDone = false;

    void move(Point* p) {


        while (p->getX() > 0 && !isInFirstRow) {
            p->setX(this->moveLeftOrUp(p->getX()));
        }
        isInFirstRow = true;

        while (p->getY() > 0 && !isInFirstColumn) {
            p->setY(this->moveLeftOrUp(p->getY()));
        }
        isInFirstColumn = true;

        if (!isRowDone) {
            p->setX(this->moveRightOrDown(p->getX()));
            if (p->getX() == xBoundary) {
                isRowDone = true;
                if (isRowDone && p->getY() == yBoundary) {
                    isInFirstRow = false;
                    isInFirstColumn = false;
                }
                p->setY(this->moveRightOrDown(p->getY()));
                for (int i; i < xBoundary; i++) {
                    p->setX(this->moveLeftOrUp(p->getX()));
                }
                isRowDone = false;
            }
        }
    }


};

#endif //GEPREXAMPLE22_MOVESTRATEGY_H
