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
        static bool hasRand = false;

        if (!hasRand) {
            srand((unsigned int)time(nullptr));
            hasRand = true;
        }


        auto number = (int) round((double) rand()/RAND_MAX);
        auto prefix = (int) round((double) rand()/RAND_MAX);

        return prefix == 0 ? number * -1 : number;
    }

    static int randomRange(int upperBoundary) {
        static bool hasRand = false;

        if (!hasRand) {
            srand((unsigned int)time(nullptr));
            hasRand = true;
        }

        return rand() % upperBoundary;
    }


    static int randomWithTimeRange(int upperBoundary) {
        static bool hasRand = false;

        if (!hasRand) {
            srand((unsigned int)time(nullptr));
            hasRand = true;
        }

        return rand() % upperBoundary;
    }
};

#endif //GEPREXAMPLE22_UTILITY_H
