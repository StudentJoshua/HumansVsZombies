//
// Created by inet2005 on 12/4/17.
//

#include <iostream>
#include "World.h"
#include "Human.h"
#include "Zombie.h"

World::World() {
    for(int x=0;x<MAXROW;x++) {
        for (int y = 0; y < MAXCOL; y++) {
            grid[x][y] = nullptr;
        }
    }
    populateWorld();
}
World::~World() {
    for(int x=0;x<MAXROW;x++) {
        for (int y = 0; y < MAXCOL; y++) {
            delete grid[x][y];
        }
    }
    delete[] grid;
    delete this;
}

void World::populateWorld(){
    int x;
    int y;
    int failsafe =0;
    srand (time(NULL));
    while(numZombies < INITZOMBIES || numHumans < INITHUMANS && failsafe < 100){
        x = rand()%20;
        y = rand()%20;
        if(this->grid[x][y] == nullptr) {
            if (numHumans < INITHUMANS) {
                this->grid[x][y] = new Human(this, x, y);
                numHumans++;
            }
            else if(numZombies < INITZOMBIES){
                this->grid[x][y] = new Zombie(this, x, y);
                numZombies++;
            }
        }else{
            failsafe++;
        }
    }
}

void World::moveOrganisms() {
    //zombies first
    for(int x=0;x<MAXROW;x++){
        for(int y=0;y<MAXCOL;y++){
            if(this->grid[x][y] != nullptr){
                if(this->grid[x][y]->getSpecies() == ZOMBIE){
                    if(!this->grid[x][y]->hasMoved){
                        this->grid[x][y]->move();
                    }
                }
            }
        }
    }
    //humans second
    for(int x=0;x<MAXROW;x++){
        for(int y=0;y<MAXCOL;y++){
            if(this->grid[x][y] != nullptr) {
                if (this->grid[x][y]->getSpecies() == HUMAN) {
                    if (!this->grid[x][y]->hasMoved) {
                        this->grid[x][y]->move();
                    }
                }
            }
        }
    }
}
void World::spawnOrganisms(){
    //zombies first
    for(int x=0;x<MAXROW;x++){
        for(int y=0;y<MAXCOL;y++){
            if(this->grid[x][y] != nullptr){
                if(this->grid[x][y]->getSpecies() == ZOMBIE){
                    if(!this->grid[x][y]->hasConverted){
                        this->grid[x][y]->convert();
                    }
                }
            }
        }
    }
    //humans second
    for(int x=0;x<MAXROW;x++){
        for(int y=0;y<MAXCOL;y++){
            if(this->grid[x][y] != nullptr) {
                if (this->grid[x][y]->getSpecies() == HUMAN) {
                    if (!this->grid[x][y]->hasConverted) {
                        this->grid[x][y]->convert();
                    }
                }
            }
        }
    }
}

void World::updateStats() {
    numZombies = 0;
    numHumans = 0;
    for(int x=0;x<MAXROW;x++){
        for(int y=0;y<MAXCOL;y++){
            if(this->grid[x][y] != nullptr){
                if(this->grid[x][y]->getSpecies() == ZOMBIE){
                    numZombies++;
                }
                else{
                    numHumans++;
                }
                if(this->grid[x][y]->moves > longestLife){
                    longestLife = this->grid[x][y]->moves;
                }
            }
        }
    }
}

void World::next() {
    turn++;
    for(int x=0;x<MAXROW;x++) {
        for (int y = 0; y < MAXCOL; y++) {
            if(this->grid[x][y] != nullptr) {
                this->grid[x][y]->hasMoved=false;
                this->grid[x][y]->hasConverted=false;
            }
        }
    }
    moveOrganisms();
    spawnOrganisms();
    updateStats();
}

void World::display() {
    std::string H = "\033[1;32m█\033[0m";
    std::string Z = "\033[1;31m█\033[0m";
    for(int x=0;x<MAXROW;x++) {
        for (int y = 0; y < MAXCOL; y++) {
            if(this->grid[x][y] != nullptr){
                if(this->grid[x][y]->getSpecies() == HUMAN){
                    std::cout<<H;
                }
                else{
                    std::cout<<Z;
                }
            }
            else{
                std::cout<<"█";
            }

        }
        std::cout << "\n";
    }
    std::cout << std::endl;
    std::cout << " Zombies: " << numZombies << " " << Z
              << " | Humans: " << numHumans << " " << H
              <<" | Turn: " << turn
              << " | Longest Life: " << longestLife << std::endl;
}

Organism* World::getOrganism(int x, int y) {
    return this->grid[x][y];
}
void World::setOrganism(int x, int y, Organism *organism) {
    this->grid[x][y] = organism;
}