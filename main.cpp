#include <map>
#include <set>

#include "Headers/Point.h"
#include "Headers/Resource.h"
#include "Headers/Field.h"
#include "Headers/Robot.h"
#include "Headers/MoveStrategy.h"
#include "Headers/Utility.h"
#include "Headers/Game.h"



const int X_BOUNDARY = 20;
const int Y_BOUNDARY = 20;
const int RESOURCE_AMOUNT = 10;
const int RESOURCE_AMOUNT_VALUE = 10;
const int ROBOT_AMOUNT = 8;

int main() {
    MoveStrategy* moveStrategy = new MoveStrategy(X_BOUNDARY);

    std::map<string, Resource*> resources;
    srand((unsigned int)time(nullptr));
    int amount_resources = rand() % RESOURCE_AMOUNT;
    int amount = 0;
    for (int i = 0; i < amount_resources; i++) {
        int x, y, value;
        x = rand() % X_BOUNDARY;
        y = rand() % Y_BOUNDARY;
        value = rand() % RESOURCE_AMOUNT_VALUE; // +1 if minimum value should be at least 1

        amount += value;
        resources[to_string(x) + ":" + to_string(y)] = new Resource(value);
    }

    std::set<Robot*> robots;
    for (int i = 0; i < ROBOT_AMOUNT; i++) {
        int x, y;
        x = rand() % X_BOUNDARY;
        y = rand() % Y_BOUNDARY;
        Point* robotPoint = new Point(x, y);

        robots.insert(new Robot(robotPoint, moveStrategy, 0));
    }

    Field* field = new Field(resources, X_BOUNDARY, Y_BOUNDARY, robots);

    Game* game = new Game(field);

    game->run();

    return 0;
}
