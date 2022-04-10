
#include <iostream>
#include "Node.h"

Node::Node(int row, int col, int distanceToS)
{
    // TODO
    this->row = row;
    this->col = col;
    this->distanceToS = distanceToS;
}

Node::~Node()
{
    // TODO
    row = 0;
    col =0;
    distanceToS= 0;
}

int Node::getRow()
{
    return this->row;
}

int Node::getCol()
{
    return this->col;
}

int Node::getDistanceToS()
{
    return this->distanceToS;
}

void Node::setDistanceToS(int distanceToS)
{
    this->distanceToS = distanceToS;
}
