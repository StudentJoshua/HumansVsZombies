//
// Created by inet2005 on 12/4/17.
//

#include <cstdlib>
#include <vector>
#include "Zombie.h"
#include "Human.h"

Zombie::Zombie()=default;
Zombie::Zombie(World *world, int xPos, int yPos) {
    this->world = world;
    this->xPos = xPos;
    this->yPos = yPos;
}
Zombie::~Zombie() {
}
speciesType Zombie::getSpecies() {
    return ZOMBIE;
}

//movement
void Zombie::move() {
    std::vector<std::vector<int>> possibleMoves = {
            {(xPos+MOVE_LEFT), (yPos+MOVE_UP)}, //UP DOWN LEFT RIGHT DIAGONALS COORDINATES
            {xPos, (yPos+MOVE_UP)},
            {(xPos+MOVE_RIGHT), (yPos+MOVE_UP)},
            {(xPos+MOVE_RIGHT), yPos},
            {(xPos+MOVE_RIGHT), (yPos+MOVE_DOWN)},
            {xPos, (yPos+MOVE_DOWN)},
            {(xPos+MOVE_LEFT), (yPos+MOVE_DOWN)},
            {(xPos+MOVE_LEFT), yPos}
    };

    int tmpX = 0;
    int tmpY = 0;
    bool isEating = false;
    bool isMoving = false;
    Organism *organism;
    std::vector<std::vector<int>> goodMoves;
    goodMoves.clear();

    for(int i=0;i<8;i++){
        tmpX = possibleMoves[i][0];
        tmpY = possibleMoves[i][1];
        if(tmpX < MAXROW && tmpX > -1 && tmpY < MAXCOL && tmpY > -1){
            organism = this->world->getOrganism(tmpX, tmpY);
            if(organism != nullptr){
                if(organism->getSpecies() == HUMAN){
                    isEating = true;
                }
            }
        }
    }
    for(int i=0;i<8;i++){
        tmpX = possibleMoves[i][0];
        tmpY = possibleMoves[i][1];
        if(tmpX < MAXROW && tmpX > -1 && tmpY < MAXCOL && tmpY > -1){
            organism = this->world->getOrganism(tmpX, tmpY);
            if(organism != nullptr){
                if(organism->getSpecies() == HUMAN){
                    goodMoves.push_back(possibleMoves[i]);
                }
            }
            else if(!isEating){
                goodMoves.push_back(possibleMoves[i]);
            }
        }
    }

    tmpX = xPos;
    tmpY = yPos;
    //get move
    if(goodMoves.size() > 0){
        isMoving = true;
        int i = rand()%(int)goodMoves.size();
        tmpX = goodMoves[i][0];
        tmpY = goodMoves[i][1];
    }
    /////

    hasMoved = true;
    if(isMoving){
        if(isEating){
            hunger = 0;
        }
        else{
            hunger++;
        }
        int oldX = xPos;
        int oldY = yPos;
        xPos = tmpX;
        yPos = tmpY;
        this->world->setOrganism(xPos, yPos, this);
        this->world->setOrganism(oldX, oldY, nullptr);

    }
}
void Zombie::convert() {
    if(conversion >= SPAWNZOMBIES){
        int possibleMoves[8][2] = {
                {(xPos+MOVE_LEFT), (yPos+MOVE_UP)}, //UP DOWN LEFT RIGHT DIAGONALS COORDINATES
                {xPos, (yPos+MOVE_UP)},
                {(xPos+MOVE_RIGHT), (yPos+MOVE_UP)},
                {(xPos+MOVE_RIGHT), yPos},
                {(xPos+MOVE_RIGHT), (yPos+MOVE_DOWN)},
                {xPos, (yPos+MOVE_DOWN)},
                {(xPos+MOVE_LEFT), (yPos+MOVE_DOWN)},
                {(xPos+MOVE_LEFT), yPos}
        };
        int tmpX = 0;
        int tmpY = 0;
        Organism *organism;
        bool foundHuman = false;
        for(int i=0;i<8;i++){
            tmpX = possibleMoves[i][0];
            tmpY = possibleMoves[i][1];
            if(tmpX < MAXROW && tmpX > -1 && tmpY < MAXCOL && tmpY > -1) { //check if out of bounds first
                organism = this->world->getOrganism(tmpX, tmpY);
                if (organism != nullptr) {
                    if (organism->getSpecies() == HUMAN) {
                        foundHuman =true;
                    }
                }
            }
        }
        if(foundHuman){
            foundHuman = false;
            do{
                int i = rand()%8;
                tmpX = possibleMoves[i][0];
                tmpY = possibleMoves[i][1];
                if(tmpX < MAXROW && tmpX > -1 && tmpY < MAXCOL && tmpY > -1) { //check if out of bounds first
                    organism = this->world->getOrganism(tmpX, tmpY);
                    if (organism != nullptr) {
                        if (organism->getSpecies() == HUMAN) {
                            foundHuman =true;
                        }
                    }
                }
            }while(!foundHuman);
            this->world->setOrganism(tmpX, tmpY, new Zombie(world, tmpX, tmpY));
            hunger = 0;
            conversion = 0;
        }
    }
    if(hunger >= STARVEZOMBIE){
        auto *newHuman = new Human(world, xPos, yPos);
        newHuman->hasMoved = true;
        this->world->setOrganism(xPos, yPos, (Organism*) newHuman);
    }
    conversion++;
    moves++;
    hasConverted = true;
}