#include <iostream>
#include <queue>
#include <stack>
#include "Bfs.h"

/**
 * this class is the holder of the bfs algorithm. it receives a start and end point and a data structure and
 * it has a function that can calculate the shortest way between two points on the data structure.

/**
 * default constructor.
 * @return void.
 */
Bfs::Bfs(){}

/**
 * constructor.
 * @param start is the starting point.
 * @param end is the end point.
 * @param grid is the data structure.
 * @return void.
 */
Bfs::Bfs(Structure *structure ) {
    Bfs::structure = structure;
}

/**
 * setStart - set the start point.
 * @param start is the value we will give to start point.
 */
void Bfs::setStart(Point p){
    start = p;
}

/**
 * getStart - returns the start point.
 * @return the start point.
 */
Point Bfs::getStart(){
    return start;
}

/**
 * setEnd - set the end point.
 * @param end is the value we will give to end point.
 */
void Bfs::setEnd(Point p){
    end = p;
}

/**
* getEnd - returns the end point.
* @return the end point.
*/
Point Bfs::getEnd(){
    return end;
}

/**
 * flagStructureNode - marks a specific node contained by the data structure as visited.
 * @param p is the value of that specific point held by a node we want to mark as visited.
 */
void Bfs::flagStructureNode(Point p) {
    structure->flagNode(p);
}

/**
 * run - this is the function that activates the bfs function resulting by printing the shortest
 * path betweeb two points.
 */
std::vector<Point> Bfs::run() {
    GridNode* root = (structure->getNode(start));
    std::queue <GridNode*> bfsQueue;
    std::stack <Point> pointStack;



    for (int i = 0; i< 11 ; i++){
        for (int j = 0; j <11 ; ++j) {
            structure->getNode(Point(i, j))->setWasItVisited(false);
            structure->getNode(Point(i, j))->setFather(NULL);
        }
    }


    //in case the start point is the end point is the same one.
    if(start.compare(end)){
        pointStack.push(start);
    }
    //root is put in the que and marked as visited.
    bfsQueue.push(root);
    root->setWasItVisited(true);
    //as long as the root is not the end point - keep setting neighbors for each root and changing roots.
    while(!(root->getPoint().compare(end))){
        setNeighbors(root,bfsQueue);
        bfsQueue.pop();
        root = bfsQueue.front();
    }
    //the node at the top of the que is the ending point,
    GridNode* node=bfsQueue.front();
    /*
     we will go to the father recursively until stopped by while loop because father pointer is null
       vec = bfs2.run();  and during this we will push the point of each node in to a stack. this is needed in order to
     print the track from start point to end point.
     */
    while(node->getFather()){
        pointStack.push(node->getPoint());
        //node->setWasItVisited(false);
        node = node->getFather();
    }
    pointStack.push(node->getPoint());

    //we will now empty the stack and print the points of each node to create the path .
    while(!(pointStack.empty())){
//        std::cout << pointStack.top() << std::endl;
        vec.push_back(pointStack.top());
        pointStack.pop();
    }
    return vec;
}

/**
 * setNeighbors - if a node has a neighbor that exists and was not visited it will push it in to the que,
 * mark it as visited and set itself as its father.
 * @param node is the node that will be checked for neighbors.
 * @param queueBfs is the queue of the algorithm where the nodes of the path pass.
 */
void Bfs::setNeighbors(GridNode* newRoot , std::queue <GridNode*> &queueBfs){
    if ((newRoot->getLeftNeighbor()) && !(newRoot->getLeftNeighbor()->wasItVisited())
        && !(newRoot->getLeftNeighbor()->isObstacle())){
        queueBfs.push(newRoot->getLeftNeighbor());
        newRoot->getLeftNeighbor()->setWasItVisited(true);
        newRoot->getLeftNeighbor()->setFather(queueBfs.front());
    }
    if ((newRoot->getUpperNeighbor()) && !(newRoot->getUpperNeighbor()->wasItVisited())
        && !(newRoot->getUpperNeighbor()->isObstacle())){
        queueBfs.push(newRoot->getUpperNeighbor());
        newRoot->getUpperNeighbor()->setWasItVisited(true);
        newRoot->getUpperNeighbor()->setFather(queueBfs.front());
    }
    if ((newRoot->getRightNeighbor()) && !(newRoot->getRightNeighbor()->wasItVisited())
        && !(newRoot->getRightNeighbor()->isObstacle())){
        queueBfs.push(newRoot->getRightNeighbor());
        newRoot->getRightNeighbor()->setWasItVisited(true);
        newRoot->getRightNeighbor()->setFather(queueBfs.front());
    }
    if ((newRoot->getLowerNeighbor()) && !(newRoot->getLowerNeighbor()->wasItVisited())
        && !(newRoot->getLowerNeighbor()->isObstacle())){
        queueBfs.push(newRoot->getLowerNeighbor());
        newRoot->getLowerNeighbor()->setWasItVisited(true);
        newRoot->getLowerNeighbor()->setFather(queueBfs.front());
    }
}