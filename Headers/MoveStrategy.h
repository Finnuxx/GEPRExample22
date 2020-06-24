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

class RowByRowMove: public MoveStrategy { //another moveStrategy (rowbyrow)
private:
    int lowerBoundary = 0;
    int xBoundary = 100; // currently we think of symmetrical fields (square)
    int yBoundary = 100;


    int moveLeft(int value) { // is the same like moveUp() but the code is easier to read now
        int moveLeft = value - 1;

        return moveLeft >= lowerBoundary
               ? moveLeft <= xBoundary-1
                 ? moveLeft
                 : xBoundary-1
               : lowerBoundary
                ;
    }

    int moveUp(int value) { // is the same like moveLeft() but the code is easier to read now
        int moveUp = value - 1;

        return moveUp >= lowerBoundary
               ? moveUp <= yBoundary - 1
                 ? moveUp
                 : yBoundary-1
               : lowerBoundary
                ;
    }

    int moveRight(int value) { // is the same like moveDown() but the code is easier to read now
        int moveRight = value + 1;

        return moveRight >= lowerBoundary
               ? moveRight <= xBoundary - 1
                 ? moveRight
                 : xBoundary-1
               : lowerBoundary
                ;
    }

    int moveDown(int value) { // is the same like moveRight() but the code is easier to read now
        int moveDown = value + 1;

        return moveDown >= lowerBoundary
               ? moveDown <= yBoundary - 1
                 ? moveDown
                 : yBoundary-1
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
        } else if (p->getX() == lowerBoundary && isOnTheTop && thisRowIsDone) { //is left upper corner
            isRowDoneLeft = true;
            isRowDoneRight = false;
            p->setY(this->moveDown(p->getY())); //nex row down if is on left side
            thisRowIsDone = false;
            return;
        } else if (p->getX() == xBoundary-1 && isOnTheBottom && thisRowIsDone) { //is right lower corner
            isRowDoneLeft = false;
            isRowDoneRight = true;
            p->setY(this->moveUp(p->getY())); //next row up if is on right side
            thisRowIsDone = false;
            return;
        } else if (p->getX() == lowerBoundary && isOnTheBottom && thisRowIsDone) { //is left lower corner
            isRowDoneLeft = true;
            isRowDoneRight = false;
            p->setY(this->moveUp(p->getY())); //nex row up if is on left side
            thisRowIsDone = false;
            return;
        }
    }


};

#endif //GEPREXAMPLE22_MOVESTRATEGY_H
