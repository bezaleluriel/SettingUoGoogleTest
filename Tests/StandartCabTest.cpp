#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include "../src/StandardCab.h"


//using testing::Eq;

class StandardCabTest : public ::testing::Test {

protected:
    StandardCab standardCab;
    Grid map;
    GridNode* gridNode;
   // char Fiat = Fiat;
   // char Blue = Blue;

   virtual void SetUp() {
       map = Grid(10,10);
       gridNode = map.getNode(Point(0, 4));
       standardCab = StandardCab(12345, 2, 'F', 'B',
                 &map);
    }

    virtual void TearDown() {
        std::cout << "Tear down" << std::endl;
    }
public:
};

/**
 *this test may cause a exit 139 error that we told is ok
 * anyway we add it with comment to prevent problems.
**/
TEST_F(StandardCabTest, moveTest){
    standardCab.move();
    EXPECT_FALSE(gridNode->getPoint().compare(standardCab.getLocation()->getPoint()));
}
