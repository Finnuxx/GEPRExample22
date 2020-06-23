#include <map>
#include <set>
#include <string>
#include <cstdio>
#include <chrono>

#include "Headers/Point.h"
#include "Headers/Resource.h"
#include "Headers/Field.h"
#include "Headers/Robot.h"
#include "Headers/MoveStrategy.h"
#include "Headers/Utility.h"
#include "Headers/Game.h"

using namespace std::chrono;

int X_BOUNDARY;
int Y_BOUNDARY;
int RESOURCE_AMOUNT;
int RESOURCE_AMOUNT_VALUE;
int ROBOT_AMOUNT;


int main() {
    cout << "Welcome to Robominer!" << endl;
    cout << "Please insert the size of the field!" << endl;
    cout << "Width: ";
    cin >> X_BOUNDARY;
    while (cin.fail()) {
        cout << "Please insert an integer!" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> X_BOUNDARY;
    }
    cout << "Height: ";
    cin >> Y_BOUNDARY;
    while (cin.fail()) {
        cout << "Please insert an integer!" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> Y_BOUNDARY;
    }
    cout << "Maximum fields with resources: ";
    cin >> RESOURCE_AMOUNT;
    while (cin.fail()) {
        cout << "Please insert an integer!" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> RESOURCE_AMOUNT;
    }
    cout << "Maximum value a resource can have: ";
    cin >> RESOURCE_AMOUNT_VALUE;
    while (cin.fail()) {
        cout << "Please insert an integer!" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> RESOURCE_AMOUNT_VALUE;
    }
    cout << "How many robots should work? ";
    cin >> ROBOT_AMOUNT;
    while (cin.fail()) {
        cout << "Please insert an integer!" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> ROBOT_AMOUNT;
    }
    cout << endl;


    std::map<string, Resource*> resources;
    int amount_resources = Utility::randomRange(RESOURCE_AMOUNT);
    int amount = 0;
    for (int i = 0; i < amount_resources; i++) {
        int x, y, value;
        x = Utility::randomRange(X_BOUNDARY);
        y = Utility::randomRange(Y_BOUNDARY);
        value = Utility::randomRange(RESOURCE_AMOUNT_VALUE); // +1 if minimum value should be at least 1

        amount += value;
        resources[to_string(x) + ":" + to_string(y)] = new Resource(value);
    }

    std::set<Robot*> robots;
    for (int i = 0; i < ROBOT_AMOUNT; i++) {
        int x, y, selection;
        x = Utility::randomRange(X_BOUNDARY);
        y = Utility::randomRange(Y_BOUNDARY);
        Point* robotPoint = new Point(x, y);

        cout << "Please select strategy:\n";
        cout << "0) random \n";
        cout << "1) row by row \n";

        cin >> selection;
        while (selection > 2 || cin.fail()) {
            cout << "Please insert an integer 0 or 1!" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> selection;
        }

        MoveStrategy* moveStrategy;

        switch (selection) {
            case 0:
                moveStrategy = new RandomMove(X_BOUNDARY, Y_BOUNDARY);
                break;

            case 1:
                moveStrategy = new RowByRowMove(X_BOUNDARY, Y_BOUNDARY);
                break;
        }

        robots.insert(new Robot(robotPoint, moveStrategy, 0));
    }

    Field* field = new Field(resources, X_BOUNDARY, Y_BOUNDARY, robots);

    Game* game = new Game(field);

    auto start = high_resolution_clock::now();
    game->run();
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<seconds>(stop - start);
    cout << "The robots took " << duration.count() << " seconds to mine all resources!" << endl;

    cin.clear();
    cin.ignore(256, '\n');

    cout << "Press any key to quit";
    getchar();

    return 0;
}

