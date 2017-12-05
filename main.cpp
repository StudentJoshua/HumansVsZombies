#include <iostream>
#include <zconf.h>
#include "World.h"

int main() {

    World world;
    std::string temp;

    while(world.numHumans > 0 && world.numZombies > 0 && world.turn < 1000){
        world.next();
        world.display();
        sleep(1);
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
    }

    return 0;
}