//
// Created by A1 on 18.06.2020.
//

#include <map>
#include <set>
#include <iostream>
#include <stdlib.h>

#include "Resource.h"
#include "Renderer.h"
#include "string"

using namespace std;

#ifndef GEPREXAMPLE22_FIELD_H
#define GEPREXAMPLE22_FIELD_H

class Field: public Renderer {
private:
    std::map<string, Resource*> resources;
    int sizeX = 50;
    int sizeY = 50;

    set<Robot*> robots;

public:

    Field(const map<string, Resource *> &resources, int sizeX, int sizeY, const set<Robot *> & robots) : resources(
            resources), sizeX(sizeX), sizeY(sizeY), robots(robots) {}

    string render() {
        string field;


        for (int y = 0; y < sizeY; y++) {
            for (int x = 0; x < sizeX; x++) {
                bool paintRobot = false;

                for (auto robot: this->robots) {
                    if (robot->isCoordinate(x, y)) {
                        paintRobot = true;
                        break;
                    }
                }

                if (paintRobot) {
                    field += " R";

                } else {
                    string coordinateKey = to_string(x) + ":" + to_string(y);
                    if (this->resources.count(coordinateKey)) {
                        Resource* resource = this->resources.find(coordinateKey)->second;

                        field += " ";
                        field += resource->render();
                    } else {
                        field += " .";
                    }
                }
            }
            field += "\r\n";
        }

        return field;
    };

    const map<string, Resource *> &getResources() const {
        return resources;
    }

    const set<Robot*> & getRobots() const{
        return robots;
    }
};

#endif //GEPREXAMPLE22_FIELD_H
