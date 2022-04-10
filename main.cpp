#include <iostream>

#include <chrono>
#include <iomanip>
#include <string>
#include <vector>

#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"
#include "Types.h"
#include "milestone4.h"
// Helper test functions
// void testNode();

// void testNodeList();

void printReachablePositions(Env env, NodeList *positions);

// Read a environment from standard input.

Env readEnvStdin(int *envRow, int *envCol);
// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printPath(Env env, NodeList *solution, int rows, int cols);

int main(int argc, char **argv) {


  // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
  // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
  // AS YOU GO ALONG.
  // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
  //    std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" <<
  //    std::endl; testNode(); testNodeList(); std::cout << "DONE TESTING" <<
  //    std::endl << std::endl;

  // Load Environment

  int rows =0;
  int cols =0;
  Env env = readEnvStdin(&rows, &cols);

  // auto start = std::chrono::system_clock::now();
  //  Some computation here

  // Solve using forwardSearch
  // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
  PathPlanner *pathplanner = new PathPlanner(env, rows, cols);
    NodeList* reachablePositions = nullptr;
 reachablePositions=  pathplanner->getReachableNodes();
  // printReachablePositions(env, reachablePositions);
  //  Get the path
  //  THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
  NodeList *solution = pathplanner->getPath();
  // print the path
  printPath(env, solution, rows, cols);
  delete pathplanner;
  delete reachablePositions;
  delete solution;
  delete_env(env, rows, cols);

}

Env readEnvStdin(int *envRow, int *envCol) {

  std::cout << "enter a 20x20 maze " << std::endl;
  //
  std::string totalString;

  std::string rowString;
  int rows = 0;
  int cols = 0;
  char c= '\0';
  while (std::cin.get(c)) //
      {
    if (c == '\n' ) {
      totalString += rowString;
      rows++; // increment num of rows every new line
      if (rows == 1) {
        cols = (int)rowString.length();
      }
      if (cols != (int)rowString.length()) {
        std::cout << "column lenghts do not match" << std::endl;
        exit(0);
      }
      rowString = ""; // reset the chars in the row as new line is reached
    } else if (c != SYMBOL_EMPTY && c != SYMBOL_GOAL && c != SYMBOL_WALL &&
               c != SYMBOL_START) {
      std::cout << "invalid char detected " << std::endl;
      exit(0);
    } else if (c != '\n') {
      // if the char is a valid char and not a new line add c to the row
      rowString += c;
    }
  }
  totalString +=rowString;
  rows++;
  int startCount=0;
  int endCount=0;
    for (char i : totalString) {
        if (i == SYMBOL_START ){
            startCount++;
        }
        if (i == SYMBOL_EMPTY ){
            endCount++;
        }
    }
    if (endCount > 1 || startCount > 1){
        std::cout<<"more than one start or goal node detected"<<std::endl;
    }

  *envRow = rows;
  *envCol = cols;
  Env env = make_env(*envRow, cols);
  int index = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      env[i][j] = totalString[index];
      index++;
    }
  }
  return env;
}

void printPath(Env env, NodeList *solution, int rows, int cols) {
  /* if length of solutiion node list is 1 then that means
   * it only containst the start node therefore there is no path
   */
  if (solution->getLength() == 1) {
    std::cout << "cannot find path" << std::endl;
    exit(1);
  }
  std::cout << "THE SOLUTION" << std::endl;
  /*loop through the env and assign arrows depnding on the position
   * of the next node
   */
  for (int i = 1; i < solution->getLength(); ++i) {
    NodePtr prevNode = solution->get(i - 1);
    NodePtr curNode = solution->get(i);

    if ((prevNode->getRow() + 1 == curNode->getRow()) &&
        (prevNode->getCol() == curNode->getCol())) {
      env[prevNode->getRow()][prevNode->getCol()] = 'v';
    }
    if ((prevNode->getRow() - 1 == curNode->getRow()) &&
        (prevNode->getCol() == curNode->getCol())) {
      env[prevNode->getRow()][prevNode->getCol()] = '^';
    }
    if ((prevNode->getRow() == curNode->getRow()) &&
        (prevNode->getCol() + 1 == curNode->getCol())) {
      env[prevNode->getRow()][prevNode->getCol()] = '>';
    }
    if ((prevNode->getRow() == curNode->getRow()) &&
        (prevNode->getCol() - 1 == curNode->getCol())) {
      env[prevNode->getRow()][prevNode->getCol()] = '<';
    }
  }
  // print the solution/path
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      std::cout << env[i][j];
    }
    std::cout << std::endl;
  }
}

void printReachablePositions(Env env, NodeList *reachablePositions) {
  // loop through reachable positions and print all nodes as string
  for (int i = 0; i < reachablePositions->getLength(); ++i) {
    std::cout << "row: " << reachablePositions->get(i)->getRow();
    std::cout << std::setw(10)
              << "col: " << reachablePositions->get(i)->getCol();
    std::cout << std::setw(10)
              << "dis: " << reachablePositions->get(i)->getDistanceToS()
              << std::endl;
  }
}

void testNode() {
  std::cout << "TESTING Node" << std::endl;

  // Make a Node and print out the contents
  Node *node = new Node(1, 1, 2);
  std::cout << node->getRow() << ",";
  std::cout << node->getCol() << ",";
  std::cout << node->getDistanceToS() << std::endl;
  delete node;

  // Change Node and print again
  node = new Node(4, 2, 3);
  std::cout << node->getRow() << ",";
  std::cout << node->getCol() << ",";
  std::cout << node->getDistanceToS() << std::endl;
  delete node;
}

void testNodeList() {
  std::cout << "TESTING NodeList" << std::endl;

  // Make a simple NodeList, should be empty size
  NodeList *nodeList = new NodeList();
  std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

  // Add a Node to the NodeList, print size
  Node *b1 = new Node(1, 1, 1);
  nodeList->addBack(b1);
  std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

  // Add second Nodetest
  Node *b2 = new Node(0, 0, 1);
  nodeList->addBack(b2);
  std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

  // Test Get-ith - should be 0,0,1
  Node *getB = nodeList->get(1);
  std::cout << getB->getRow() << ",";
  std::cout << getB->getCol() << ",";
  std::cout << getB->getDistanceToS() << std::endl;

  // Print out the NodeList
  std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO"
            << std::endl;
  for (int i = 0; i < nodeList->getLength(); ++i) {
    Node *nodeP = nodeList->get(i);
    std::cout << nodeP->getRow() << ",";
    std::cout << nodeP->getCol() << ",";
    std::cout << nodeP->getDistanceToS() << std::endl;
  }
}