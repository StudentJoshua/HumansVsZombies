#include <iostream>
#include <zconf.h>
#include "World.h"

const int MAXTURNS = 1000;
const int FRAMERATE = 100000;

int main() {

    World world;
    std::string temp;

    while(world.numHumans > 0 && world.numZombies > 0 && world.turn < MAXTURNS){
        world.next();
        world.display();
        usleep(FRAMERATE);
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
    }
    world.display();

    return 0;
}