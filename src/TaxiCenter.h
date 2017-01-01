#ifndef EX1_TAXICENTER_H
#define EX1_TAXICENTER_H
#include <iostream>
#include <list>
#include "Driver.h"
#include "TripInformation.h"
#include "Structure.h"
#include "BaseCab.h"
#include "MaritalStatus.h"

/**
 * this class contains the information about all its' employees (drivers), their location, the
cabs and the trips. basically acts as the main part of the taxi company.
 */

class TaxiCenter {

private:
    Structure* map;
    std::list <Driver*> driversList;
    std::list <BaseCab*> taxiCabsList;
    std::list <TripInformation*> tripInformationList;

public:
    /**
     * constructor.
     */
    TaxiCenter();

    /**
     * destructor.
     */
    ~TaxiCenter();

    /**
     * constructor.
     * @param structure is the structure we will use as our map.
     */
    TaxiCenter(Structure* structure);

    /**
     * adds a new driver to the taxi center list.
     */
    void addDriver(int id, int age, MaritalStatus status, int experience, int vehicleId);

    /**
     * creates a new taxi.
     */
    void addTaxiCab(int cabId, int taxiType, char manufacturer, char color);

    /**
     * return driver list.
     * @return driver list.
     */
    std::list <Driver*>* getDriverList();

    /**
     * return taxi list.
     * @return taxo list.
     */
    std::list <BaseCab*>* getTaxiList();

    /**
     * return trip info list.
     * @return trip info list.
     */
    std::list <TripInformation*>* getTripInfoList();

    /**
     * adds a ride to the taxi center - meaning create and adds a trip info to the list.
     * @param id is the ride id.(dont forget has to be following number of last one).
     * @param startX the x value of start point of the ride.
     * @param startY the y value of start point of the ride.
     * @param endX the x value of end point of the ride.
     * @param endY the y value of end point of the ride.
     * @param numOfPassengers is the number of passengers for this ride.
     * @param tarriff is the tariff for this ride.
     */
    void addRide(int id, int startX, int startY, int endX, int endY, int numOfPassengers, double tarriff);

    /**
     * assigns drivers to the trip infos(from oldest ones to newest ones ) and puts the if ofthe driver
     * as the id of the driver in the trip info.
     */
    void assignDrivers();

    /**
     * moves all drivers to end point of their current trip.
     * meaning changes the cab location of each driver to the node on grid containing the end point
     * of the trip they are responsible for.
     */
    void getTo();

    /**
     * calls assign drivers and get to. marks all drivers as available, deletes trip infos for rides that are over.
     */
    void completeTrip();

    /**
     * prints out the location of the driver with the id received.
     * @param id is the id of the driver who'slocation we want to print .
     */
    void printDriverLocation(int id);

};


#endif //EX1_TAXICENTER_H
