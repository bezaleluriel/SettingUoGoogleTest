#include "MainFlow.h"

MainFlow::MainFlow() {}

MainFlow::MainFlow(Structure* map) {
    MainFlow::map = map;
    taxiCenter = TaxiCenter(map);
}

void MainFlow::parseSize(std::string size) {
    std::vector<std::string> vec = beginningInfoReader.split(size);
    mapX = stoi(vec[0]);
    mapY = stoi(vec[1]);
}

int MainFlow::getMapX() {return mapX;}

int MainFlow::getMapY() {return mapY;}

void MainFlow::setNumOfObstacles(int num) {numOfObstacles = num;}

void MainFlow::setObstacle(std::string obstacleLocation) {
    std::vector<std::string> vec = beginningInfoReader.split(obstacleLocation);
    int x = stoi(vec[0]);
    int y = stoi(vec[1]);
    //this creates a point representing the location of the obstacle.
    Point p = Point(x,y);
    //we will now get the node from the grid at that point and mark it as to contain an obstacle.
    map->markObstacle(p);
}

void MainFlow::choiceMenu(int choice, std::string s) {
    //splits the input received by user to parts and returns in a vector.
    std::vector<std::string> vec = beginningInfoReader.split(s);
    switch (choice) {
        /*
         * case 1 is to insert a driver.
         */
//        case 1 : {
//
//
//
//
//
//            int driverId = stoi(vec[0]);
//            int age = stoi(vec[1]);
//            char status = (vec[2])[0];
//            int experience = stoi(vec[3]);
//            int vehicleId = stoi(vec[4]);
//            taxiCenter.addDriver(driverId, age, status, experience, vehicleId);
//            break;
//        }


            /*
             *case 2 is to insert a new ride.
             */
        case 2 : {
            int rideId = stoi(vec[0]);
            int startX = stoi(vec[1]);
            int startY = stoi(vec[2]);
            int endX = stoi(vec[3]);
            int endY = stoi(vec[4]);
            int numOfPassengers = stoi(vec[5]);
            double tariff = stod(vec[6]);
            taxiCenter.addRide(rideId, startX, startY, endX, endY, numOfPassengers, tariff);
            break;
        }

            /*
             *case 3 is to insert a new taxi.
             */
        case 3 : {
            int cabId = stoi(vec[0]);
            int taxiType = stoi(vec[1]);
            char manufacturer = (vec[2])[0];
            char color = (vec[3])[0];
            taxiCenter.addTaxiCab(cabId, taxiType, manufacturer, color);
            break;
        }

            /*
             *case 4 is to print on the screen the location of the driver which has the id to match
             * the string that we received. location will be output in format '(x,y)'.
             */
        case 4 : {
            int searchId = stoi(s);
            taxiCenter.printDriverLocation(searchId);
            break;
                }

        default :
            break;

        }
}

void MainFlow::choiceMenu() {
    taxiCenter.completeTrip();
}

void MainFlow::addDriver(Driver *driver) {
    taxiCenter.addDriver(driver->getId(), driver->getAge(), driver->getMaritalStatus(),
                         driver->getYearsOfExperience(), driver->getVehicleId());

}







