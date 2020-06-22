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
    Field *field;

    bool static gameNotOver(std::map<string, Resource *> resources) { // time-complexity O(n)

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

    void static runRobot(Robot *robot, std::map<string, Resource *> resources) {

        while (Game::gameNotOver(resources)) {
            if (mtx.try_lock()) {
                robot->move2();

                string coordinateKey = robot->getCoordinateKey();
                if (resources.count(coordinateKey) > 0) {
                    Resource *resource = resources.find(coordinateKey)->second;
                    resource->harvest(robot);
                }

                mtx.unlock();
            }
        }
    }

    void static renderGame(Field* field) {
        if (mtx.try_lock()) {
            cout << field->render();
            mtx.unlock();
        }
    }


    int run() {
        int maxResources = getMaxResources();
        cout << "Maximum available Resources: " << maxResources << endl;
        renderGame(this->field);

        int size = this->field->getRobots().size();
        std::thread myThreads[size];
        int pos = 0;

        for (auto robot: this->field->getRobots()) {
            myThreads[pos] = std::thread(runRobot, robot, this->field->getResources());
            pos++;
        }

        for (int i = 0; i < size; i++) {
            myThreads[i].join();
        }

        int maxRobotResourceCounter = 0;
        int countRobots = 0;

        Robot *robots[this->field->getRobots().size()];
        int robPos = 0;
        for (auto robot: this->field->getRobots()) {
            robots[robPos] = robot;
            robPos++;
        }

        for (auto i = 0; i < this->field->getRobots().size(); i++) {
            for (auto j = i + 1; j < this->field->getRobots().size(); j++) {
                if (robots[i]->getResourceCounter() < robots[j]->getResourceCounter()) {
                    Robot *temp = robots[i];
                    robots[i] = robots[j];
                    robots[j] = temp;
                }
            }
        }


        for (auto robot: robots) {
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
