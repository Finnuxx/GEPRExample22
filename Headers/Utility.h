//
// Created by A1 on 18.06.2020.
//

#include <ctime>
#include <cstdlib>
#include <math.h>

#ifndef GEPREXAMPLE22_UTILITY_H
#define GEPREXAMPLE22_UTILITY_H

class Utility {
public:
    static int randomMove() {
        srand((unsigned int)time(nullptr));

        auto number = (int) round((double) rand()/RAND_MAX);
        auto prefix = (int) round((double) rand()/RAND_MAX);

        return prefix == 0 ? number * -1 : number;
    }

    static int randomRangeX(int upperBoundary) {
        srand((unsigned int)time(nullptr));

        return rand() % upperBoundary;
    }

    static int randomRangeY(int upperBoundary) {
        srand((unsigned int)time(nullptr));

        return rand() % upperBoundary;
    }

    static int randomWithTimeRange(int upperBoundary) {
        srand((unsigned int)time(nullptr));

        return rand() % upperBoundary;
    }
};

#endif //GEPREXAMPLE22_UTILITY_H
