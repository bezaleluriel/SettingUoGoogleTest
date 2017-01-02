#include "Grid.h"
#include <boost/serialization/export.hpp>

/**
 * this class simulates a grid of nodes. it contains a two dimensional array and is capable of receiving
 * a size and creating a "grid" with of all of the points on it.
 */

/**
 * deafult constructor.
 * @return void.
 */
Grid::Grid(){}

/**
 * constructor.
 * @param sizeX is the width of the grid.
 * @param sizeY is the height of the grid.
 * @return void.
 */
Grid::Grid(int x, int y){
    sizeX = x;
    sizeY = y;
    createNodes();
}

/**
 * getX - returns the width of the structure.
 * @return the width of the structure.
 */
int Grid::getX() {return sizeX;}

/**
 * getY - returns the height of the grid.
 * @return the height of the grid.
 */
int Grid::getY() {return sizeY;}

/**
 * createNodes - creates all the needed nodes on the grid and sets their neighbors.
 */
void Grid::createNodes() {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            nodesOnStructure[i][j] = GridNode(Point(i, j));
        }
    }
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            //check for left neighbor
            if (i - 1 >= 0) { nodesOnStructure[i][j].setLeftNeighbor(&nodesOnStructure[i - 1][j]); }
            //check for upper neighbor
            if (j + 1 <= sizeY - 1) { nodesOnStructure[i][j].setUpperNeighbor(&nodesOnStructure[i][j + 1]); }
            //check for right neighbor
            if (i + 1 <= sizeX - 1) { nodesOnStructure[i][j].setRightNeighbor(&nodesOnStructure[i + 1][j]); }
            //check for lower neighbor
            if (j - 1 >= 0) { nodesOnStructure[i][j].setLowerNeighbor(&nodesOnStructure[i][j - 1]); }
        }
    }
}

/**
 * flagNode - goes to a specific node and marks it as visited.
 * @param p is the point contained in the node we will want to flag.
 */
void Grid::flagNode(Point p) {
    nodesOnStructure[p.getX()][p.getY()].setWasItVisited();
}

/**
 * getNode - returns a pointer to a node from the grid.
 * @param p is the point that the pointer we want to return will contain.
 * @return a pointer to node containing the point we received.
 */
GridNode* Grid::getNode (Point p){
    return &nodesOnStructure[p.getX()][p.getY()];
}

/**
 * this func mark a node as an obstacle with its specific Point.
 * @param p the Point on the grid that we want to update.
 */
void Grid::markObstacle(Point p) {
    nodesOnStructure[p.getX()][p.getY()].setObstacle(true);
}

