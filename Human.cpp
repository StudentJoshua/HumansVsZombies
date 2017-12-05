//
// Created by inet2005 on 12/4/17.
//

#include <cstdlib>
#include "Human.h"
Human::Human()=default;
Human::Human(World *world, int xPos, int yPos) {
    this->world = world;
    this->xPos=xPos;
    this->yPos=yPos;
}
Human::~Human() {
    delete this;
}

speciesType Human::getSpecies() {
    return HUMAN;
}
void Human::move() {
    int possibleMoves[4][2] = {
            {(xPos+MOVE_LEFT), yPos},
            {xPos, (yPos+MOVE_UP)},
            {(xPos+MOVE_RIGHT), yPos},
            {xPos, (yPos+MOVE_DOWN)}
    };
    int tmpX = 0;
    int tmpY = 0;
    bool isMoving = false;
    Organism *organism;
    int i = rand()%4;
        tmpX = possibleMoves[i][0];
        tmpY = possibleMoves[i][1];
        if(tmpX < MAXROW && tmpX > -1 && tmpY < MAXCOL && tmpY > -1){
            organism = this->world->getOrganism(tmpX, tmpY);
            if(organism == nullptr){
                isMoving = true;
            }
        }

    hasMoved = true;
    if(isMoving){
        int oldX = xPos;
        int oldY = yPos;
        xPos = tmpX;
        yPos = tmpY;
        this->world->setOrganism(xPos, yPos, this);
        this->world->setOrganism(oldX, oldY, nullptr);
    }

}

void Human::convert() {
    if(recruit >= SPAWNHUMANS){
        recruit = -1;
        int possibleMoves[4][2] = {
                {(xPos+MOVE_LEFT), yPos},
                {xPos, (yPos+MOVE_UP)},
                {(xPos+MOVE_RIGHT), yPos},
                {xPos, (yPos+MOVE_DOWN)}
        };
        int tmpX = 0;
        int tmpY = 0;
        Organism *organism;
        bool foundEmpty = false;
        for(int i=0;i<4;i++){
            tmpX = possibleMoves[i][0];
            tmpY = possibleMoves[i][1];
            if(tmpX < MAXROW && tmpX > -1 && tmpY < MAXCOL && tmpY > -1) { //check if out of bounds first
                organism = this->world->getOrganism(tmpX, tmpY);
                if (organism == nullptr) {
                    foundEmpty = true;
                }
            }
        }
        if(foundEmpty){
            foundEmpty = false;
            do{
                int i = rand()%4;
                tmpX = possibleMoves[i][0];
                tmpY = possibleMoves[i][1];
                if(tmpX < MAXROW && tmpX > -1 && tmpY < MAXCOL && tmpY > -1) { //check if out of bounds first
                    organism = this->world->getOrganism(tmpX, tmpY);
                    if (organism == nullptr) {
                        foundEmpty = true;
                    }
                }
            }while(!foundEmpty);
            auto *newHuman = new Human(world, tmpX, tmpY);
            newHuman->hasMoved = true;
            this->world->setOrganism(tmpX, tmpY, (Organism*) newHuman);
        }
    }
    recruit++;
    moves++;
    hasConverted = true;
}
