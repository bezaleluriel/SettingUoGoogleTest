#include "MainFlow.h"

std::map<int, std::queue<int>> instructionsMap;

MainFlow::MainFlow() {}

MainFlow::MainFlow(Structure* map) {
    MainFlow::map = map;
    taxiCenter = TaxiCenter(map);
}

void MainFlow::parseSize(std::string size) {
    std::vector<std::string> vec = beginningInfoReader.split(size);
    mapX = atoi( vec[0].c_str());
            //stoi(vec[0]);
    mapY = atoi( vec[1].c_str());
            //stoi(vec[1]);
}

int MainFlow::getMapX() {return mapX;}

int MainFlow::getMapY() {return mapY;}

void MainFlow::setNumOfObstacles(int num) {numOfObstacles = num;}

void MainFlow::setObstacle(std::string obstacleLocation) {
    std::vector<std::string> vec = beginningInfoReader.split(obstacleLocation);
    int x =atoi( vec[0].c_str());
            //stoi(vec[0]);
    int y = atoi( vec[1].c_str());
            //stoi(vec[1]);
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
             *case 2 is to insert a new ride.
             */
        case 2 : {
            int rideId = atoi( vec[0].c_str());//stoi(vec[0]);
            int startX = atoi( vec[1].c_str());//stoi(vec[1]);
            int startY = atoi( vec[2].c_str());//stoi(vec[2]);
            int endX = atoi( vec[3].c_str());//stoi(vec[3]);
            int endY = atoi( vec[4].c_str());//stoi(vec[4]);
            int numOfPassengers = atoi( vec[5].c_str());//stoi(vec[5]);
            double tariff = atof( vec[6].c_str());//stod(vec[6]);
            int time = atoi( vec[7].c_str());//stoi(vec[7]);
            taxiCenter.addRide(rideId, startX, startY, endX, endY, numOfPassengers, tariff, time);
            break;
        }

            /*
             *case 3 is to insert a new taxi.
             */
        case 3 : {
            int cabId = atoi( vec[0].c_str());//stoi(vec[0]);
            int taxiType = atoi( vec[1].c_str());//stoi(vec[1]);
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
            int searchId = atoi(s.c_str());//stoi(s);
            taxiCenter.printDriverLocation(searchId);
            break;
                }
            /*
     * case 5 is to insert a driver.
     */
        case 5 : {
            int driverId = atoi( vec[0].c_str());//stoi(vec[0]);
            int age = atoi( vec[1].c_str());//stoi(vec[1]);
            char status = (vec[2])[0];
            int experience = atoi( vec[3].c_str());//stoi(vec[3]);
            int vehicleId = atoi( vec[4].c_str());//stoi(vec[4]);
            taxiCenter.addDriver(driverId, age, status, experience, vehicleId);
            break;
        }

        default :
            break;

        }
}

 TaxiCenter* MainFlow::getTaxiCenter()  {
    return &taxiCenter;
}

void MainFlow::changeTime() {
    taxiCenter.checkTime();

}







