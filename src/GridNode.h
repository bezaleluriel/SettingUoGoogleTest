#ifndef EX1_NODE_H
#define EX1_NODE_H
#include "Point.h"
#include <iostream>

/**
 * this class contains a point in it and surrounds it with more capabilities that will help to activate an
 * algorithm on it such as having a father,brothers and flags.
 */
class GridNode {

private:
    Point point;
    bool visited;
    bool obstacle;
    GridNode* father;
    GridNode* leftNeighbor;
    GridNode* upperNeighbor;
    GridNode* rightNeighbor;
    GridNode* lowerNeighbor;


public:
    /**
     * default constructor.
     * @return void.
     */
    GridNode();

    /**
     * constructor.
     * @param p is a point that we will set as member.
     * @return void.
     */
    GridNode(Point p);

    /**
     * getPoint - returns the point that node holds.
     * @return the point that node holdes.
     */
    Point getPoint();

    /**
     * wasItVisited - this is a boolean that symbolyzes if a node was visited during the algorithm.
     * @return wasItVisited which is a boolean that node holdes.
     */
    bool wasItVisited();

    /**
     * getfather - returns a pointer to node that node holdes. it leads to its "father" in the algorithm.
     * @return a pointer to the "father".
     */
    GridNode* getFather();

    /**
     * returns a pointer to node symbolizing this nodes "left neighbor".
     * @return a pointer to the "left neighbor".
     */
    GridNode* getLeftNeighbor();

    /**
     * returns a pointer to node symbolizing this nodes "upper neighbor".
     * @return the "upper neighbor".
     */
    GridNode* getUpperNeighbor();

    /**
     * returns a pointer to node symbolizing this nodes "right neighbor".
     * @return the "right neighbor".
     */
    GridNode* getRightNeighbor();

    /**
     * returns a pointer to node symbolizing this nodes "lower neighbor".
     * @return the "lower neighbor".
     */
    GridNode* getLowerNeighbor();

    /**
     * setWasItVisited - sets the wasItVisited boolean to true to show it was visited.
     */
    void setWasItVisited();

    /**
     * sets the father pointer with an address of the father's node.
     * @param p is a pointer to the father's node.
     */
    void setFather(GridNode* p);

    /**
     *  sets the left neighbor pointer with an address of the left neighbor's node.
     * @param p is a pointer to the left neighbor's node.
     */
    void setLeftNeighbor(GridNode* p);

    /**
     * setUpperNeighbor - sets the upper neighbor pointer with an address of the upper neighbor's node.
     * @param p is a pointer to the upper neighbor's node.
     */
    void setUpperNeighbor(GridNode* p);

    /**
     * setRightNeighbor - sets the right neighbor pointer with an address of the right neighbor's node.
     * @param p is a pointer to the right neighbor's node.
     */
    void setRightNeighbor(GridNode* p);

    /**
     * setLowerNeighbor - sets the lower neighbor pointer with an address of the lower neighbor's node.
     * @param p is a pointer to the lower neighbor's node.
     */
    void setLowerNeighbor(GridNode* p);
    /**
     * checks if a node is an obstacle.
     * @return
     */
    bool isObstacle();

    /**
     * set a node to be mark as an obstacle.
     */
    void setObstacle(bool b);

};



#endif //EX1_NODE_H
