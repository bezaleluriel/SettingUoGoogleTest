#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include "../src/GridNode.h"
#include "../src/Grid.h"
#include "../src/Point.h"
//using testing::Eq;
class GridNodeTest : public ::testing::Test {

protected:
    Point *p1;
    Point *p2;
    Point *p3;
    Point *p4;
    GridNode *gridNode1;
    GridNode *gridNode2;
    Grid grid;

    virtual void SetUp() {
        std::cout << "Set up" << std::endl;
        p1 = new Point(0, 0);
        p2 = new Point(0, 1);
        p3 = new Point(0, 2);
        p4 = new Point(1, 0);
        gridNode1 = new GridNode(*p1);
        gridNode2 = new GridNode(*p3);
        grid=Grid(5,5);
        grid.createNodes();
    }

    virtual void TearDown() {
        std::cout << "Tear down" << std::endl;
        delete p2;
        delete p1;
        delete p3;
        delete p4;
        delete gridNode1;
        delete gridNode2;
    }
};

/**
 * tests the get point func.
 * we compare the point returned from a node with what we know is supposed to be returned.
 */
TEST_F(GridNodeTest, getPointCheck){
    ASSERT_EQ(p1->getX(),gridNode1->getPoint().getX());
    ASSERT_EQ(p1->getY(),gridNode1->getPoint().getY());
}

/**
 * tests the was it visited func.
 * the visited bool member is initialized to false when created.
 * we check that the node visited bool is actually false.
 */
TEST_F(GridNodeTest, wasVisitedCheck){
    EXPECT_FALSE(gridNode1->wasItVisited());
}

/**
 * we test the get father func. we set a node as the father of another node and then check that it is actually
 * it's father.
 *
 */
TEST_F(GridNodeTest, GetFatherCheck){
    std::cout << "GetFatherCheck" << std::endl;
    gridNode2->setFather(gridNode1);
    ASSERT_EQ(gridNode2->getFather()->getPoint().getX(),p1->getX());
}

/**
 *check the Get/setLeftCheck func, we set a left neigbor and check if it was
 * set as well
 */
TEST_F(GridNodeTest, GeLeftCheck){
    std::cout << "GetLeftCheck" << std::endl;
    gridNode2->setLeftNeighbor(gridNode1);
    ASSERT_TRUE(gridNode2->getLeftNeighbor()->getPoint().compare(gridNode1->getPoint()));
}

/**
 * check that node with point (0,0 does not have a left neighbor.
 */
TEST_F(GridNodeTest, GridNodeCheckLeftNeighborNotExist_Test){
    std::cout << "GridNodeCheckLeftNeighborNotExist_Test" << std::endl;
    EXPECT_FALSE((grid.getNode(Point(0,0))->getLeftNeighbor()));
}

/**
 * check that (0,0) has a right neighbor.
 */
TEST_F(GridNodeTest, GridNodeCheckRughtNeighborIsExist_Test){
    std::cout << "GridNodeCheckRightNeighborIsExist_Test" << std::endl;
    Point p10 = grid.getNode(Point(0,0))->getRightNeighbor()->getPoint();
    EXPECT_TRUE((p10.compare(p4->getPoint())));
}

/**
 * check that point (3,4) is the value in upper neighbor of node with point (3,3).
 */
TEST_F(GridNodeTest, GridNodeCheckUpperNeighborIsExist_Test){
    std::cout << "GridNodeCheckUpperNeighborIsExist_Test" << std::endl;
    Point p11 = grid.getNode(Point(3,3))->getUpperNeighbor()->getPoint();
    Point p12 = Point(3, 4);
    EXPECT_TRUE((p11.compare(p12)));
}

/**
 * check that node with point(3,3) has a lower neighbor.
 */
TEST_F(GridNodeTest, GridNodeCheckLowerNeighborIsExist_Test){
    std::cout << "GridNodeCheckLowerNeighborIsExist_Test" << std::endl;
    EXPECT_TRUE(grid.getNode(Point(2,3))->getLowerNeighbor()->getPoint().isExist());
}

/**
 * check that grid node 1 is marked as visited.
 */
TEST_F(GridNodeTest, CheckSetWasVisited){
    std::cout << "CheckSetWasVisited" << std::endl;
    gridNode1->setWasItVisited(true);
    EXPECT_TRUE(gridNode1->wasItVisited());
}
/**
 * checks that gridnode marked as an obstacle.
 */
TEST_F(GridNodeTest, CheckIsObstacle){
    gridNode1->setObstacle(true);
    EXPECT_TRUE(gridNode1->isObstacle());
}

