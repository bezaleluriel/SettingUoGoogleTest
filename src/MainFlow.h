#ifndef EX1_MAINFLOW_H
#define EX1_MAINFLOW_H
#include <iostream>
#include "BeginningInfoReader.h"
#include "Structure.h"
#include "Grid.h"
#include "TaxiCenter.h"

/**
 * this class will be responsible for parsing the input given by the user and applying it
 * on out taxi center.
 * it will create a map and put the obastacles in it, all classes will use this same map.
 * it will be responsible for creating the objects needed for this program such as
 * drivers, taxi's , trip info's , passengers.
 *
 */

class MainFlow {

private:
    BeginningInfoReader beginningInfoReader;
    Structure* map;
    int mapX;
    int mapY;
    int numOfObstacles;
    TaxiCenter taxiCenter;//initiallized in constructor.

public:
    /**
     * constructor.
     */
    MainFlow();

    /**
     * constructor.
     * it will set the map received as the map of this class and will create a taxi center
     * and set it as it's map as well.
     * @param structure is the map that we will use.
     * @return
     */
    MainFlow(Structure* map);

    /**
     * returns the width ( x value) of map.
     * @return the width ( x value) of map.
     */
    int getMapX();

    /**
     * returns the length ( y value) of map.
     * @return the length ( y value) of map.
     */
    int getMapY();

    /**
     * this func is used to parse the input representing the size of the map and use
     * BeginningInfoReader to do so. it will then create a grid with the size received.
     * @param size is the string received representing size will be of form: int x(space)int y.
     */
    void parseSize(std::string size);

    /**
     * this func recieves an int and sets it as number of ostacles.
     */
    void setNumOfObstacles(int);

    /**
     * this function receives a string representing the obstacles locations and sets obstacles in those
     * locations.
     * @param obstaclesLocations is the string representing the obstacles locations.
     */
    void setObstacle(std::string obstacleLocation);

    /**
     * this function is in function overloading there is another func with same name and different parameters.
     * this function is specifically for choice number 6 - we used function overloading for this func
     * because in option 6 it doesn't receive a string a input , only an int.
     * @param choice is the user's choice in this case it will be 6 for sure.
     */
    void choiceMenu();

    /**
     * this function is in function overloading there is another func with same name and different parameters.
     * this func will receive a choice and a string.
     * it will parse the input using beginning info reader and do what the number of the
     * choice represents.
     * @param choice is the user's choice.
     * @param s is the string that provides the input for that choice.
     */
    void choiceMenu(int choice, std::string s);

    /**
     * adds driver to taxi center.
     * @param driver is the driver.
     */
    void addDriver(Driver* driver);

};


#endif //EX1_MAINFLOW_H
