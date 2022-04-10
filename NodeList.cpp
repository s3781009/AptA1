
#include "NodeList.h"
#include <iostream>

NodeList::NodeList() { this->length = 0; }

NodeList::NodeList(NodeList &other) {
  this->nodes = new Node *[other.getLength()];
  for (int i = 0; i < other.length; ++i) {
    nodes[i] = new Node(other.get(i)->getRow(), other.get(i)->getCol(),
                        other.get(i)->getDistanceToS());
  }
  this->length = other.length;
}

NodeList::~NodeList() {
  clear();
  delete[] nodes;
}

int NodeList::getLength() { return this->length; }

NodePtr NodeList::get(int i) { return this->nodes[i]; }

void NodeList::addBack(NodePtr newNode) {
  NodePtr copyNode =
      new Node(newNode->getRow(), newNode->getCol(), newNode->getDistanceToS());
  this->nodes[length] = copyNode;
  length++; // after setting the node increment the length so the next node can
            // be added to the next index
            // delete newNode;
}

bool NodeList::containsNode(NodePtr node) {
  /* return true of node exist in the node list else return fasle */
  for (int i = 0; i < this->length; ++i) {
    if (this->nodes[i]->getRow() == node->getRow() &&
        this->nodes[i]->getCol() == node->getCol()) {
      return true;
    }
  }
  return false;
}

void NodeList::clear() {
  for (int i = this->length - 1; i >= 0; --i) {
    delete nodes[i];
    length--;
  }
}

void NodeList::setMaxSize(int maxSize) { this->nodes = new Node *[maxSize]; }
