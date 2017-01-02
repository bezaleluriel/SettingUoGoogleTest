#ifndef EX1_TRIPINFORMATION_H
#define EX1_TRIPINFORMATION_H
#include "Point.h"
#include "Passenger.h"
#include <iostream>
#include <boost/serialization/access.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
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
using namespace std;
using namespace boost::archive;


/**
 * this class represents information about a spesific trip.
 */

class TripInformation {

private:
    int driverId;
    int rideId;
    int totalMetersPassed;//needs to be updated on every point which the car moves, starting by 0
    int numberOfPassengers;
    double tariff;
    Point start;
    Point end;
    bool rideIsOver; //will be set as false in constructor.
    bool hasDriver; // will be set as false in constructor.
    int startTime;

private:

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {

        ar & driverId;
        ar & rideId;
        ar & totalMetersPassed;
        ar & numberOfPassengers;
        ar & tariff;
        ar & start;
        ar & end;
        ar & rideIsOver;
        ar & hasDriver;


    }

public:

    /**
     * constructor.
     */
    TripInformation();

    /**
     * constructor.
     * @param rideId is the rideid.
     * @param numberOfPassengers is the number of passengers
     * @param tariff is the tariff.
     * @param start is the beginning point of the ride.
     * @param end is the ending point od the drive.
     * @param driver is the driver of the taxi.
     * @param passenger is the passenger.
     */
    TripInformation(int id, int startX, int startY, int endX, int endY, int numOfPassengers,
                    double tarriff,int time);

    /**
     * returns the ride id.
     * @return the ride id.
     */
    int getRideId();

    /**
     * sets the ride id.
     * @param rideId
     */
    void setRideId(int rideId);

    /**
     * returns the meters passed in this ride.
     * @return
     */
    int getTotalMetersPassed();

    /**
     * set the number of meters passed in this ride to this curent point.
     * @param totalMetersPassed
     */
    void setTotalMetersPassed(int totalMetersPassed);

    /**
     * returns the number of passengers riding in this specific ride.
     * @return
     */
    int getNumberOfPassengers();

    /**
     * sets the number of passengers riding in this specific ride.
     * @param numberOfpassengers
     */
    void setNumberOfPassengers(int numberOfpassengers);

    /**
     * returns the tariff for this ride.
     * @return the tariff for this ride.
     */
    double getTariff();

    /**
     * set the tariff for this ride.
     * @param tariff is the tariff set for this ride.
     */
    void setTariff(double tariff);

    /**
     * returns the start point for this ride.
     * @return the start point for this ride.
     */
     Point getStart() ;

    /**
     * sets the starting point for this ride.
     * @param start is the start point for this ride.
     */
    void setStart(Point start);

    /**
     * returns the end point of this ride.
     * @return the end point of this ride.
     */
    Point getEnd();

    /**
     * sets the end point for this ride.
     * @param end is the end point for this ride.
     */
    void setEnd(Point end);


    /**
     * this function switches rideisover member to true.
     */
    void setRideIsOver(bool b);

    /**
     * returns true if ride is over false otherwise.
     * @return a bool which is true or false.
     */
    bool getRideIsOver();

    /**
     * returns the id of the driver for this ride.
     * @return the id of the driver for this ride.
     */
    int getDriverId();

    /**
     * sets the driver id as the id of the driver that will drive for this ride.
     * @param driverId is the id of the driver.
     */

    void setDriverId(int driverId);

    /**
     *
     * @return
     */
    bool getHasDriver();

    /**
     *
     * @param b
     */
    void setHasDriver(bool b);

    /**
     *
     * @return
     */
    int getStartTime() ;

    /**
     *
     * @param startTime
     */
    void setStartTime(int startTime);

};


#endif //EX1_TRIPINFORMATION_H
