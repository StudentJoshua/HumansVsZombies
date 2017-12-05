//
// Created by inet2005 on 12/4/17.
//

#ifndef HUMANSVSZOMBIES_ZOMBIE_H
#define HUMANSVSZOMBIES_ZOMBIE_H


#include "Organism.h"

class Zombie : public Organism {
private:
    int hunger = 0;
    int conversion = 0;
    World *world;
public:

    Zombie();
    Zombie(World *world, int xPos, int yPos);
    virtual ~Zombie();

    virtual speciesType getSpecies();
    virtual void move();
    virtual void convert();
    bool isStarved();
};


#endif //HUMANSVSZOMBIES_ZOMBIE_H
