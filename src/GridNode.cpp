#include <iostream>
#include "GridNode.h"

/**
 * this class contains a point in it and surrounds it with more capabilities that will help to activate an
 * algorithm on it such as having a father,brothers and flags.
 */

/**
 * default constructor.
 * @return void.
 */
GridNode::GridNode(){}

/**
 * constructor.
 * @param p is a point that we will set as member.
 * @return void.
 */
GridNode::GridNode(Point p){
    point = p;
    visited = false;
    obstacle = false;
    father = NULL;
    leftNeighbor = NULL;
    upperNeighbor = NULL;
    rightNeighbor = NULL;
    lowerNeighbor = NULL;
}

/**
 * getPoint - returns the point that node holds.
 * @return the point that node holdes.
 */
Point GridNode::getPoint(){
    return Point(point.getX(),point.getY());
}

/**
 * wasItVisited - this is a boolean that symbolyzes if a node was visited during the algorithm.
 * @return wasItVisited which is a boolean that node holdes.
 */
bool GridNode::wasItVisited(){
    return visited;
}

/**
 * getfather - returns a pointer to node that node holdes. it leads to its "father" in the algorithm.
 * @return a pointer to the "father".
 */
GridNode* GridNode::getFather(){
    return father;
}

/**
 * returns a pointer to node symbolizing this nodes "left neighbor".
 * @return a pointer to the "left neighbor".
 */
GridNode* GridNode::getLeftNeighbor(){
    return leftNeighbor;
}

/**
 * returns a pointer to node symbolizing this nodes "upper neighbor".
 * @return the "upper neighbor".
 */
GridNode* GridNode::getUpperNeighbor(){
    return upperNeighbor;
}

/**
 * returns a pointer to node symbolizing this nodes "right neighbor".
 * @return the "right neighbor".
 */
GridNode* GridNode::getRightNeighbor(){
    return rightNeighbor;
}

/**
 * returns a pointer to node symbolizing this nodes "lower neighbor".
 * @return the "lower neighbor".
 */
GridNode* GridNode::getLowerNeighbor(){
    return lowerNeighbor;
}

/**
 * setWasItVisited - sets the wasItVisited boolean to true to show it was visited.
 */
void GridNode::setWasItVisited(bool b){
    visited = b;
}

/**
 * sets the father pointer with an address of the father's node.
 * @param p is a pointer to the father's node.
 */
void GridNode::setFather(GridNode* f){
    father = f;
}

/**
 *  sets the left neighbor pointer with an address of the left neighbor's node.
 * @param p is a pointer to the left neighbor's node.
 */
void GridNode::setLeftNeighbor(GridNode* left){
    leftNeighbor = left;
}

/**
 * setUpperNeighbor - sets the upper neighbor pointer with an address of the upper neighbor's node.
 * @param p is a pointer to the upper neighbor's node.
 */
void GridNode::setUpperNeighbor(GridNode* upper){
    upperNeighbor = upper;
}

/**
 * setRightNeighbor - sets the right neighbor pointer with an address of the right neighbor's node.
 * @param p is a pointer to the right neighbor's node.
 */
void GridNode::setRightNeighbor(GridNode* right){
    rightNeighbor = right;
}

/**
 * setLowerNeighbor - sets the lower neighbor pointer with an address of the lower neighbor's node.
 * @param p is a pointer to the lower neighbor's node.
 */
void GridNode::setLowerNeighbor(GridNode* lower){
    lowerNeighbor = lower;
}

bool GridNode::isObstacle() {
    return obstacle;
}

void GridNode::setObstacle(bool b) {
    obstacle = b;
}


