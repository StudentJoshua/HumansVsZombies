//
// Created by inet2005 on 12/4/17.
//

#ifndef HUMANSVSZOMBIES_ORGANISM_H
#define HUMANSVSZOMBIES_ORGANISM_H

#include "World.h"

class World;

enum speciesType {HUMAN, ZOMBIE};
const int MOVE_LEFT = -1;
const int MOVE_RIGHT = 1;
const int MOVE_UP = -1;
const int MOVE_DOWN = 1;

class Organism {
private:
    World *world; //temp world for moving

public:
    Organism();
    Organism(World *world, int xPos, int yPos);
    virtual ~Organism();

    int moves; //personal movement
    bool hasMoved;
    bool hasConverted;
    void newTurn();

    int xPos, yPos; //position in world

    //virtual methods
    virtual void move() =0; //move abstract
    virtual void convert()=0; //convert abstract | Zombies: Eat Humans(Spawn Zombies), Humans: Spawn Humans
    virtual speciesType getSpecies()=0; //HUMANS, ZOMBIES

    //zombies: starve

    void setPosition(int x, int y);
};


#endif //HUMANSVSZOMBIES_ORGANISM_H
