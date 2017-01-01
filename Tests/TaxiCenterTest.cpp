#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include "../src/TaxiCenter.h"
//using testing::Eq;

class TaxiCenterTest : public ::testing::Test {

protected:
    TaxiCenter taxiCenter;
    Structure* map;
    Grid grid;

    virtual void SetUp(){
        grid = Grid(5,5);
        map = &grid;
        taxiCenter = TaxiCenter(map);
        std::cout << "Set up" << std::endl;
    }

    virtual void TearDown(){
        std::cout << "Tear down" << std::endl;
    }

public:
};
/**
 * checking that the center adds a driver to the driver list.
 */
TEST_F(TaxiCenterTest, addDriver){
    std::string s;
    taxiCenter.addDriver(1,20,MaritalStatus::Divorced ,2,3);
    EXPECT_TRUE((taxiCenter.getDriverList()->size() > 0));
}
/**
 * checking that the center sends the closest driver to the pickup.
 * we created drivers and chheckd that the closest one's id was added to the trip info list.
 */
TEST_F(TaxiCenterTest, assignToClosestDriver){
    taxiCenter.addTaxiCab(1,1,'T','G');
    taxiCenter.addDriver(12345, 50,MaritalStatus::Divorced, 20, 1);
    taxiCenter.addRide(1,0,0,2,2,1,25);
    taxiCenter.assignDrivers();
    EXPECT_TRUE(taxiCenter.getTripInfoList()->front()->getDriverId() == 12345);
}