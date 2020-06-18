//
// Created by A1 on 18.06.2020.
//

#include "Field.h"
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <set>

using namespace std;
std::recursive_mutex mtx;

#ifndef GEPREXAMPLE22_GAME_H
#define GEPREXAMPLE22_GAME_H

class Game {
private:
    Field* field;

    bool static gameNotOver(std::map<string, Resource*> resources) { // time-complexity O(n)

        if (mtx.try_lock()) {
            for (auto resource: resources) {
                if (resource.second->getValue() > 0) {
                    mtx.unlock();
                    return true;
                }
            }

            mtx.unlock();
            return false;
        }

        return true;
    }

public:
    Game(Field *field) : field(field) {}

    int getMaxResources() {
        int sum = 0;
        for (auto resource: field->getResources()) {
            sum += resource.second->getValue();
        }
        return sum;
    }

    void static runRobot(Robot* robot, std::map<string, Resource*> resources) {

        while (Game::gameNotOver(resources)) {
            if (mtx.try_lock()) {
                robot->move();

                string coordinateKey = robot->getCoordinateKey();
                if (resources.count(coordinateKey) > 0) {
                    Resource *resource = resources.find(coordinateKey)->second;
                    resource->harvest(robot);
                }

                mtx.unlock();
            }
        }
    }

    /*void static renderGame(Field* field) {
        int round = 0;
        while (Game::gameNotOver(field->getResources())) {
            cout << "Round " << round << endl;
            if (mtx.try_lock()) {
                cout << field->render();
                mtx.unlock();
            }

            round++;
        }
    }*/

    int run() {
        int maxResources = getMaxResources();
        cout << "Maximum available Resources: " << maxResources << endl;

        int size = this->field->getRobots().size();
        std::thread myThreads[size];
        int pos = 0;

        for (auto robot: this->field->getRobots()) {
            myThreads[pos] = std::thread(runRobot, robot, this->field->getResources());
            pos++;
        }

        //std::thread renderThread (renderGame, this->field);

        for (int i = 0; i < size; i++) {
            myThreads[i].join();
        }
        //renderThread.join();


        cout << "Maximum available Resources: " << maxResources << endl;

        int maxRobotResourceCounter = 0;
        int countRobots = 0;
        for (auto robot: this->field->getRobots()) {
            countRobots++;

            int robotResourceCounter = robot->getResourceCounter();
            maxRobotResourceCounter += robotResourceCounter;

            cout << "Robot " << countRobots << ": " << robotResourceCounter << endl;
        }
        cout << "Totally harvested resources: " << maxRobotResourceCounter << endl;

        return 0;
    }
};

#endif //GEPREXAMPLE22_GAME_H
