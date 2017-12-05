//
// Created by inet2005 on 12/4/17.
//

#include "Organism.h"

Organism::Organism() {
}

Organism::Organism(World *world, int xPos, int yPos) {
    this->world = world;
    this->xPos = xPos;
    this->yPos = yPos;
}
Organism::~Organism() {
    delete this;
}

void Organism::setPosition(int x, int y) {
    xPos = x;
    yPos = y;
}
void Organism::newTurn() {
    hasConverted=false;
    hasMoved=false;
}
