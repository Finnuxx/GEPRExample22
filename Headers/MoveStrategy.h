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
               ? newCoordinate <= xBoundary-1
                 ? newCoordinate
                 : xBoundary-1
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


    int moveLeft(int value) {
        int moveLeft = value - 1;

        return moveLeft >= lowerBoundary
               ? moveLeft <= xBoundary-1
                 ? moveLeft
                 : xBoundary-1
               : lowerBoundary
                ;
    }

    int moveUp(int value) {
        int moveLeft = value - 1;

        return moveLeft >= lowerBoundary
               ? moveLeft <= xBoundary-1
                 ? moveLeft
                 : xBoundary-1
               : lowerBoundary
                ;
    }

    int moveRight(int value) {
        int moveLeft = value + 1;

        return moveLeft >= lowerBoundary
               ? moveLeft <= xBoundary-1
                 ? moveLeft
                 : xBoundary-1
               : lowerBoundary
                ;
    }

    int moveDown(int value) {
        int moveLeft = value + 1;

        return moveLeft >= lowerBoundary
               ? moveLeft <= xBoundary-1
                 ? moveLeft
                 : xBoundary-1
               : lowerBoundary
                ;
    }

public:

    RowByRowMove(int xBoundary, int yBoundary) : xBoundary(xBoundary), yBoundary(yBoundary) {}

    bool isOnTheTop = true;
    bool isRowDoneLeft = true;
    bool isOnTheBottom = false;
    bool isRowDoneRight = false;
    bool thisRowIsDone = false;


    void move(Point* p) {


        /*while (p->getX() > 0 && !isInFirstRow) {
            p->setX(this->moveLeftOrUp(p->getX()));
        }
        isInFirstRow = true;

        while (p->getY() > 0 && !isInFirstColumn) {
            p->setY(this->moveLeftOrUp(p->getY()));
        }
        isInFirstColumn = true;*/

        if (isRowDoneLeft && isOnTheTop && !thisRowIsDone) { //goes right down
            p->setX(this->moveRight(p->getX()));
            if (p->getX() == xBoundary-1) {
                thisRowIsDone = true;
                if (p->getY() == yBoundary-1) { //if is on right bottom == everything done -> move up
                    isOnTheTop = false;
                    isOnTheBottom = true;
                    return;
                }
                return;
            }
        } else if (isRowDoneRight && isOnTheTop && !thisRowIsDone) { //goes left down
            p->setX(this->moveLeft(p->getX()));
            if (p->getX() == lowerBoundary) {
                thisRowIsDone = true;
                if (p->getY() == yBoundary-1) { //if is on left bottom == everything done -> move up
                    isOnTheTop = false;
                    isOnTheBottom = true;
                    return;
                }
                return;
            }
        } else if (isRowDoneLeft && isOnTheBottom && !thisRowIsDone) { //goes right up
            p->setX(this->moveRight(p->getX()));
            if (p->getX() == xBoundary-1) {
                thisRowIsDone = true;
                if (p->getY() == lowerBoundary) { //if is on right top == everything done -> move down
                    isOnTheTop = true;
                    isOnTheBottom = false;
                    return;
                }
                return;
            }
        } else if (isRowDoneRight && isOnTheBottom && !thisRowIsDone) { //goes left up
            p->setX(this->moveLeft(p->getX()));
            if (p->getX() == lowerBoundary) {
                thisRowIsDone = true;
                if (p->getY() == lowerBoundary) { //if is on left top == everything done -> move down
                    isOnTheTop = true;
                    isOnTheBottom = false;
                    return;
                }
                return;
            }
        }

        if (p->getX() == xBoundary-1 && isOnTheTop && thisRowIsDone) { //is right upper corner
            isRowDoneLeft = false;
            isRowDoneRight = true;
            p->setY(this->moveDown(p->getY())); //next row down if is on right side
            thisRowIsDone = false;
            return;
        } else if (p->getX() == lowerBoundary && isOnTheTop && thisRowIsDone) {
            isRowDoneLeft = true;
            isRowDoneRight = false;
            p->setY(this->moveDown(p->getY())); //nex row down if is on left side
            thisRowIsDone = false;
            return;
        } else if (p->getX() == xBoundary-1 && isOnTheBottom && thisRowIsDone) {
            isRowDoneLeft = false;
            isRowDoneRight = true;
            p->setY(this->moveUp(p->getY())); //next row up if is on right side
            thisRowIsDone = false;
            return;
        } else if (p->getX() == lowerBoundary && isOnTheBottom && thisRowIsDone) {
            isRowDoneLeft = true;
            isRowDoneRight = false;
            p->setY(this->moveUp(p->getY())); //nex row up if is on left side
            thisRowIsDone = false;
            return;
        }
    }


};

#endif //GEPREXAMPLE22_MOVESTRATEGY_H
