//
// Created by uriel on 18/12/16.
//

#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include "../src/LuxuryCab.h"


//using testing::Eq;

class LaxuryCabTest : public ::testing::Test {

protected:
    LuxuryCab luxuryCab;
    Grid map;
    GridNode* gridNode;

    virtual void SetUp() {
        map = Grid(10,10);
        gridNode = map.getNode(Point(0, 4));
        luxuryCab = LuxuryCab(12345, 2, 'F', 'B',
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
TEST_F(LaxuryCabTest, moveTest){
    luxuryCab.move();
    EXPECT_FALSE(gridNode->getPoint().compare(luxuryCab.getLocation()->getPoint()));
}
