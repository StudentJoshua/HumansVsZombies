//
// Created by inet2005 on 12/4/17.
//

#include <cstdlib>
#include <vector>
#include "Human.h"
Human::Human()=default;
Human::Human(World *world, int xPos, int yPos) {
    this->world = world;
    this->xPos=xPos;
    this->yPos=yPos;
    recruit=0;
    hasMoved=true;
    hasConverted=true;
}
Human::~Human() {
}

speciesType Human::getSpecies() {
    return HUMAN;
}
void Human::move() {
    std::vector<std::vector<int>> possibleMoves = {
            {(xPos+MOVE_LEFT), yPos},
            {xPos, (yPos+MOVE_UP)},
            {(xPos+MOVE_RIGHT), yPos},
            {xPos, (yPos+MOVE_DOWN)}
    };
    std::vector<std::vector<int>> goodMoves;
    goodMoves.clear();
    int tmpX = 0;
    int tmpY = 0;
    bool isMoving = false;
    Organism *organism;
    for(int i=0;i<4;i++){
        tmpX = possibleMoves[i][0];
        tmpY = possibleMoves[i][1];
        if(tmpX < MAXROW && tmpX > -1 && tmpY < MAXCOL && tmpY > -1) {
            organism = this->world->getOrganism(tmpX, tmpY);
            if (organism == nullptr) {
                isMoving = true;
                goodMoves.push_back(possibleMoves[i]);
            }
        }
    }

    hasMoved = true;
    if(isMoving){
        int i = rand()%(int)goodMoves.size();
        tmpX = goodMoves[i][0];
        tmpY = goodMoves[i][1];
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
