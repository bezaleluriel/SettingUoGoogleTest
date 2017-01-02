#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include <list>
#include "../src/Point.h"
#include "../src/TripInformation.h"
#include "../src/Grid.h"
#include "../src/Driver.h"

//using testing::Eq;

class TripInformationTest : public ::testing::Test {

protected:
    TripInformation tripInformation;
    virtual void SetUp() {
        Grid map(9,9);
        std::list <Driver> driversList;
        int rideId = 123;
        int numberOfPassengers = 1;
        char Married = Married;
        double tariff = 2;
        Point start(4,4);
        Point end(7,8);
        //Driver driver(12345, 50, MaritalStatus::Married, 20);
        Driver driver(12345, 50, Married, 5, 20);
        Passenger passenger(start, end);
        tripInformation = TripInformation(rideId, start.getX(), start.getY(),end.getX(), end.getY(), numberOfPassengers, tariff,0);
        std::cout << "Set up" << std::endl;
    }

    virtual void TearDown() {
        std::cout << "Tear down" << std::endl;
    }
};

/**
 * checking the ride over flag.
 * we turned it on and checked it.
 */
TEST_F(TripInformationTest, rideOverTest){
    tripInformation.setRideIsOver(true);
    EXPECT_TRUE(tripInformation.getRideIsOver());
}

///**
// * we updated the kmpassed and checked that it was updated.
// */
//TEST_F(TripInformationTest, updateKmPassedTest){
//    int before = tripInformation.getTotalMetersPassed();
//    tripInformation.setTotalMetersPassed(100);
//    int after = tripInformation.getTotalMetersPassed();
//    EXPECT_GT(before, after);
//}

