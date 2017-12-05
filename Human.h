//
// Created by inet2005 on 12/4/17.
//

#ifndef HUMANSVSZOMBIES_HUMAN_H
#define HUMANSVSZOMBIES_HUMAN_H

#include "Organism.h"

class Human : public Organism {
private:
    World *world;
    int recruit = 0;

public:
    Human();
    Human(World *world, int xPos, int yPos);
    virtual ~Human();

    virtual speciesType getSpecies();
    virtual void move();
    virtual void convert();
};


#endif //HUMANSVSZOMBIES_HUMAN_H
