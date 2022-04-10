
#include "PathPlanner.h"
//#include "milestone4.h"

#include <iostream>
#include <queue>

// to intialize a path planner the goal and start node must be intalized
//  for a path to be generated
PathPlanner::PathPlanner(Env env, int rows, int cols) {
    this->env = env;
    this->maxSize = rows * cols;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            this->env[i][j] = env[i][j];
            if (env[i][j] == SYMBOL_START) {
                // call this function to set starting position
                initialPosition(i, j);
            }
            if (this->env[i][j] == SYMBOL_GOAL) {
                // set goal node with row and cols , distance from start will be set
                // later
                this->goal = new Node(i, j, 0);
            }
        }
    }
}

PathPlanner::~PathPlanner() {
    delete reachableNodes;
    delete initPos;
    delete goal;
    initPos = nullptr;
    goal = nullptr;
}

void PathPlanner::initialPosition(int row, int col) {
    this->initPos = new Node(row, col, 0);
}

NodeList *PathPlanner::getReachableNodes() {
    NodeList o;
    o.setMaxSize(maxSize);
    o.addBack(this->initPos);
    NodeList c;
    c.setMaxSize(maxSize); // closed list
    NodePtr p = o.get(0);  // assign pointer to start position
    int dist = 1;
    bool stop=false;
    while (!stop) {
        stop=true;
        char pDown = env[p->getRow() + 1][p->getCol()];
        char pUp = env[p->getRow() - 1][p->getCol()];
        char pRight = env[p->getRow()][p->getCol() + 1];
        char pLeft = env[p->getRow()][p->getCol() - 1];
        NodePtr neighborUp = new Node(p->getRow() - 1, p->getCol(), dist);
        NodePtr neighborRight = new Node(p->getRow(), p->getCol() + 1, dist);
        NodePtr neighborDown = new Node(p->getRow() + 1, p->getCol(), dist);
        NodePtr neighborLeft = new Node(p->getRow(), p->getCol() - 1, dist);
        if (pUp == SYMBOL_EMPTY && !o.containsNode(neighborUp)) {
            o.addBack(neighborUp);
        }
        if (pRight == SYMBOL_EMPTY && !o.containsNode(neighborRight)) {
            o.addBack(neighborRight);
        }
        if (pDown == SYMBOL_EMPTY && !o.containsNode(neighborDown)) {
            o.addBack(neighborDown);
        }
        if (pLeft == SYMBOL_EMPTY && !o.containsNode(neighborLeft)) {
            o.addBack(neighborLeft);
        }
        dist++;
        NodePtr pNode = new Node(p->getRow(), p->getCol(), p->getDistanceToS());
        c.addBack( pNode);
        for (int i = 0; i < o.getLength(); ++i) {
            if (!c.containsNode(o.get(i))) {
                p = o.get(i);
                stop=false;
            }
        }
        delete pNode;
        delete neighborDown;
        delete neighborLeft;
        delete neighborRight;
        delete neighborUp;
    }
    /*
     *invoking copy constructor on open list, because open list members
     *will be freed when exiting this scope
     */
    this->reachableNodes = new NodeList(o);
    NodeList *copy = new NodeList(o);
    return copy;
}

NodeList *PathPlanner::getPath() {
    NodeList path;
    path.setMaxSize(maxSize);
    NodePtr currentNode = this->goal;
    path.addBack(currentNode);
    for (int i = reachableNodes->getLength() - 1; i > 0; --i) {

        if ((reachableNodes->get(i)->getRow() + 1 == currentNode->getRow()) &&
            (reachableNodes->get(i)->getCol() == currentNode->getCol())) {
            this->goal->setDistanceToS(reachableNodes->get(i)->getDistanceToS() + 1);
            currentNode = reachableNodes->get(i);
            path.addBack(currentNode);
        }
        if ((reachableNodes->get(i)->getRow() == currentNode->getRow()) &&
            (reachableNodes->get(i)->getCol() - 1 == currentNode->getCol())) {
            this->goal->setDistanceToS(reachableNodes->get(i)->getDistanceToS() + 1);
            currentNode = reachableNodes->get(i);
            path.addBack(currentNode);
        }
        if ((reachableNodes->get(i)->getRow() - 1 == currentNode->getRow()) &&
            (reachableNodes->get(i)->getCol() == currentNode->getCol())) {
            this->goal->setDistanceToS(reachableNodes->get(i)->getDistanceToS() + 1);
            currentNode = reachableNodes->get(i);
            path.addBack(currentNode);
        }
        if ((reachableNodes->get(i)->getRow() == currentNode->getRow()) &&
            (reachableNodes->get(i)->getCol() + 1 == currentNode->getCol())) {
            this->goal->setDistanceToS(reachableNodes->get(i)->getDistanceToS() + 1);
            currentNode = reachableNodes->get(i);
            path.addBack(currentNode);
        }
    }
    NodeList *reversePath = new NodeList();
    reversePath->setMaxSize(path.getLength());
    for (int i = path.getLength() - 1; i >= 0; --i) {
        NodePtr node = new Node(path.get(i)->getRow(), path.get(i)->getCol(),path.get(i)->getDistanceToS());
        reversePath->addBack(node);
        delete node;
    }
    return reversePath;
}
