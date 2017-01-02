#ifndef EX1_GRID_H
#define EX1_GRID_H

#include "GridNode.h"
#include "Structure.h"
#include <boost/serialization/base_object.hpp>

#include <boost/archive/tmpdir.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>

/**
 * this class simulates a grid of nodes. it contains a two dimensional array and is capable of receiving
 * a size and creating a "grid" with of all of the points on it.
 */
class Grid: public Structure {

private:
    int sizeX;
    int sizeY;
    GridNode nodesOnStructure [11][11];

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & sizeX;
        ar & sizeY;
        ar & nodesOnStructure;
        ar & boost::serialization::base_object<Structure>(*this);
    }

public:
    /**
     * deafult constructor.
     * @return void.
     */
    Grid();

    /**
     * constructor.
     * @param sizeX is the width of the grid.
     * @param sizeY is the height of the grid.
     * @return void.
     */
    Grid(int sizeX , int sizeY);

    /**
     * getX - returns the width of the structure.
     * @return the width of the structure.
     */
    int getX();

    /**
     * getY - returns the height of the grid.
     * @return the height of the grid.
     */
    int getY();

    /**
     * createNodes - creates all the needed nodes on the grid and sets their neighbors.
     */
    void createNodes();

    /**
     * flagNode - goes to a specific node and marks it as visited.
     * @param p is the point contained in the node we will want to flag.
     */
    void flagNode(Point p);

    /**
     * getNode - returns a pointer to a node from the grid.
     * @param p is the point that the pointer we want to return will contain.
     * @return a pointer to node containing the point we received.
     */
    GridNode* getNode (Point p);

    /**
     * this func mark a node as an obstacle with its specific Point.
    * @param p the Point on the grid that we want to update.
    */
    void markObstacle(Point p);

};


#endif //EX1_GRID_H
