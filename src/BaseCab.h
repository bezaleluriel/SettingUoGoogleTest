#ifndef SETTINGUOGOOGLETEST_BaseCab_H
#define SETTINGUOGOOGLETEST_BaseCab_H

#include "Point.h"
#include "GridNode.h"
#include "Passenger.h"
#include "Structure.h"
#include "Manufacturer.h"
#include "Color.h"
#include "Grid.h"
#include <string>
#include <iostream>
#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>

class BaseCab {
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & cabId;
        ar & numOfKmPassed;
        ar & velocity;
        ar & taxiType;
        ar & coEfficient;
        ar & manufacturer;
        ar & color;
        ar & location;
        ar.register_type(static_cast<Grid*>(NULL));
        ar & map;
    }

protected:
    int cabId;
    int numOfKmPassed;
    int velocity;
    int taxiType;

protected:
    double coEfficient;
    Manufacturer manufacturer;
    Color color;
    GridNode* location;


    Structure* map;

public:

    /**
     * constructor.
     */
    BaseCab();

    /**
     * constructor.
     * @param cabId is the cab's id.
     * @param taxiType is a number representing the taxi type - 1 standard , 2- luxury.
     * @param manufacturer is a char representing the manufacturer of the car(will be made into enum).
     * @param color is a char representing the color of the car(will be made into enum).
     */
    BaseCab(int cabId, int taxiType, char manufacturer, char color,Structure* map);


    /**
     * returs the BaseCab's id.
     * @return the BaseCab's id.
     */
    int getCabId();

    /**
     * return the num of km passed.
     * @return the num of km passed.
     */
    int getNumOfKmPassed();

    /**
     * retur// exampple of boo

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // ar & status;
        //ar & location;
        //ar & passengers;
        ar & id;
        ar & age;
        ar & yearsOfExperience;
        ar & vehicleId;
        ar & available;
        ar & taxiCab;
        ar & averageSatisfaction;
        ar & tripInformation;


}ns the manufacturer(enum).
     * @return the manufacturer(enum).
     */
    Manufacturer getManufacturer();

    /**
     * returns the color(enum).
     * @return the color(enum).
     */
    Color getColor();

    /**
    * get the current location of the taxiBaseCab.
    * @return a pointer to GridNode that is the specific node that the taxi is onn, on the grid.
    */
    GridNode *getLocation();

    /**
     * set the current location of the taxiBaseCab.
     * @param location is a pointer to the node that the taxi BaseCab is at right now.
     */
    void setLocation(GridNode *location);

    /**
     * returns a point representation of the taxi's location.
     * @return a point representing the taxi's location.
     */
    Point returnLocationInPoint();

    /**
     * moves the BaseCab meaning changing its location gridNode to one of its neighbors.
     * this function will be virtual because the deriven class called luxuryBaseCab will be faster
     * and we want its function to be the one to work when the function is called.
     */
    virtual void move( Point point )=0;

    int getTaxiType() ;

};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(BaseCab)

#endif //SETTINGUOGOOGLETEST_BaseCab_H



