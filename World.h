//
// Created by inet2005 on 12/4/17.
//

#ifndef HUMANSVSZOMBIES_WORLD_H
#define HUMANSVSZOMBIES_WORLD_H

#include "Organism.h"

class Organism;

const int MAXROW = 20;
const int MAXCOL = 20;
const int INITHUMANS = 100;//Initial population of humans
const int INITZOMBIES = 5;//Initial population of zombies
const int SPAWNHUMANS = 3;//A step in time when humans spawn
const int SPAWNZOMBIES = 8;//A step in time when zombies spawn
const int STARVEZOMBIE = 3;//A step in time when zombies starve

class World {
private:
    Organism *grid[MAXROW][MAXCOL];
    void populateWorld();
    void moveOrganisms();
    void spawnOrganisms();

public:
    World();
    virtual ~World();

    Organism* getOrganism(int x, int y);
    void setOrganism(int x, int y, Organism *organism);

    int turn = 0;
    int longestLife = 0;
    int numHumans = 0;
    int numZombies = 0;
    void updateStats();

    void display();
    void next();
};


#endif //HUMANSVSZOMBIES_WORLD_H
