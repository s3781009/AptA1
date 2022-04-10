#ifndef COSC_ASS_ONE_NODE_LIST
#define COSC_ASS_ONE_NODE_LIST

#include "Node.h"
#include "Types.h"

class NodeList {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // Create a New Empty List
   NodeList();

   NodeList(NodeList& other);

    // Clean-up the list
   ~NodeList();

   // Number of items in the list
   int getLength();

   // Get a pointer to the ith node in the node list
   NodePtr get(int i);

   // Add a COPY node element to the BACK of the nodelist
   //    This class now has control over the pointer
   //    And should delete the pointer if the position-distance 
   //    is removed from the list
   void addBack(NodePtr newNode);

   // Checks if the list contains a node with the same co-ordinate
   //    as the given node.
   bool containsNode(NodePtr node);

   // Remove everything from the list
   // Don't forget to clean-up the memory!
   void clear();

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */
    void setMaxSize(int maxSize);

   /* This is a suggestion of what you could use. */
   /* You can change this code.                   */
private:

   // NodeList: list of node objects
   // You may assume a fixed size for M1, M2, M3
   Node**    nodes;
   // Number of nodes currently in the NodeList
   int      length;


};

#endif // COSC_ASS_ONE_NODE_LIST
