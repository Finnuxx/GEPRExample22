//
// Created by A1 on 18.06.2020.
//

#ifndef GEPREXAMPLE22_POINT_H
#define GEPREXAMPLE22_POINT_H

struct Point {
private:
    int x, y;

public:
    Point (int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setX(int x) {
        Point::x = x;
    }

    void setY(int y) {
        Point::y = y;
    }

    bool operator < (const Point& rhs) const{
        return x+y < rhs.getX() + rhs.getY();
    }
};

#endif //GEPREXAMPLE22_POINT_H
