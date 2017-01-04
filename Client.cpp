//
// Created by uriel on 01/01/17.
//uriel the king

#include <iostream>
#include "src/Bfs.h"
#include "src/BeginningInfoReader.h"
#include "src/MainFlow.h"
//#include <boost/thread.hpp>
#include "src/sockets/Udp.h"
#include "src/Driver.h"
#include "src/StandardCab.h"
#include "src/LuxuryCab.h"
#include "src/Grid.h"
#include <unistd.h>
#include <boost/serialization/access.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/serialization/export.hpp>
#include "src/StandardCab.h"
#include "src/LuxuryCab.h"
#include <boost/serialization/export.hpp>

using namespace std;

BOOST_CLASS_EXPORT_GUID(StandardCab, "src/StandardCab")
BOOST_CLASS_EXPORT_GUID(LuxuryCab, "src/LuxuryCab")
BOOST_CLASS_EXPORT_GUID(Grid,"src/Grid")

int main(int argc, char *argv[]) {
    std::list <Driver*> clientDriversList;
    std::list <BaseCab*> clientTaxiCabsList;
    std::list <TripInformation*> clientTripInformationList;
    BeginningInfoReader beginningInfoReader;
    Structure* map ;
    ///receiving info for driver and creating one.
    std::string info;
    cin >> info;
    std::vector<std::string> vec = beginningInfoReader.split(info);
    int driverId = stoi(vec[0]);
    int age = stoi(vec[1]);
    char status = (vec[2])[0];
    int experience = stoi(vec[3]);
    int vehicleId = stoi(vec[4]);
    Driver* driver = new Driver(driverId, age, status, experience, vehicleId);
    clientDriversList.push_back(driver);

    std::cout << "Client Is Running" <<std::endl;

    ///open socket
    cout << argv[1] << endl;
    Udp udp(0, atoi(argv[1]));
    udp.initialize();

    ///serialize and send driver info.
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << info;
    s.flush();
    char buffer[1024];
    udp.sendData(serial_str);
    std::cout << "send driver info" << std::endl;

    ///receiving serialized map info.
    udp.reciveData(buffer, sizeof(buffer));///receiving data from the client
    string str6(buffer, sizeof(buffer));
    std::string mapInfo;///creating a pointer to driver test
    boost::iostreams::basic_array_source<char> device6(str6.c_str(), str6.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s6(device6);
    boost::archive::binary_iarchive ic6(s6);
    ic6 >> mapInfo;///serialized object will be put in this pointer to driversTest
    std::vector<std::string> mapInfoVec = beginningInfoReader.split(mapInfo);
    map = new Grid(stoi(mapInfoVec[0]), stoi(mapInfoVec[1]));///initiallizing size of grid.
    ///adding obstacles to grid.
    for(int i = 2; i<mapInfoVec.size(); i+=2){
        map->markObstacle(Point(stoi(mapInfoVec[i]),stoi(mapInfoVec[i+1])));
    }

    std::cout << "receiving the map info serialization"<< std::endl;
    std::cout << mapInfo<< std::endl;




    ///receiving seriaized taxi cab.
    udp.reciveData(buffer, sizeof(buffer));///receiving data from the client
    std::cout << "receiving seriaized taxi cab"<< std::endl;

    string str20(buffer, sizeof(buffer));
    std::string taxiInfo;///creating a pointer to driver test
    boost::iostreams::basic_array_source<char> device20(str20.c_str(), str20.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s20(device20);
    boost::archive::binary_iarchive ic(s20);
    ic >> taxiInfo;///serialized object will be put in this pointer to driversTest
    std::vector<std::string> vec2 = beginningInfoReader.split(taxiInfo);
    int cabId = stoi(vec2[0]);
    int taxiType = stoi(vec2[1]);
    char manufacturer = (vec2[2])[0];
    char color = (vec2[3])[0];
    BaseCab* taxi;
    //in case the taxi type is standard cab:
    if(taxiType == 1){
        std::cout << "in case the taxi type is standard cab"<< std::endl;
        taxi = new StandardCab(cabId, taxiType, manufacturer, color, map);
        taxi->setLocation(map->getNode(Point(0,0)));
        clientTaxiCabsList.push_back(taxi);
    }
    //in case the taxi type is luxury cab:
    if(taxiType == 2){
        std::cout << "in case the taxi type is luxury cab"<< std::endl;
        taxi = new LuxuryCab(cabId, taxiType, manufacturer, color, map);
        taxi->setLocation(map->getNode(Point(0,0)));
        clientTaxiCabsList.push_back(taxi);
    }

    ///connecting driver with taxi.
    std::list<Driver*>::iterator driverIt = clientDriversList.begin();
    std::list<BaseCab*>::iterator taxiIt = clientTaxiCabsList.begin();
    while(driverIt != clientDriversList.end()){
        if((*(driverIt))->getVehicleId() == taxi->getCabId()){
            (*(driverIt))->setTaxiCab(taxi);
            break;
        }
        else{
            taxiIt++;
        }
    }

    ///test for receiving cab from server:
    std::cout << "this is a test for receiving the serialized cab id&taxitype:"<< std::endl;
    std::cout << taxi->getCabId() << "," ;
    std::cout << taxi->getTaxiType() << std::endl;

    /**
     * TODO - first we will receive a vector of trip info's. we will need to match them
     * to the drivers we have according to the driver id that they contain.
     * we will then receive a vector of drivers id's and another vector of points.
     * there will be the same number of id's and points so we can have a double loop
     * telling first driver to move to first point, second driver to move to second point etc'.
     * right now we are receiving a flag (1 or 2) to show which action should be done but
     * in the next excercise we probably wont need the flags. ****notice  after we remove flags
     * the ride id will be equal to vec[0] not vec[1].
     */

    ///receiving tripinfo from server:
    udp.reciveData(buffer, sizeof(buffer));///receiving data from the client
    std::cout << "receiving tripinfo from server:" << std::endl;
    /// deserialize of trip info
    string str4(buffer, sizeof(buffer));
    std::string tripParts;
    boost::iostreams::basic_array_source<char> device(str4.c_str(), str4.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device);
    boost::archive::binary_iarchive ia4(s4);
    ia4 >> tripParts;

    ///spliting up trip info string and creating new trip info.
    std::vector<std::string> vec4 = beginningInfoReader.split(tripParts);
    ///splitting to cases acording to flags.
    if(stoi(vec4[0]) == 1){
        int rideId = stoi(vec4[1]);
        int startX = stoi(vec4[2]);
        int startY = stoi(vec4[3]);
        int endX = stoi(vec4[4]);
        int endY = stoi(vec4[5]);
        int numOfPassengers = stoi(vec4[6]);
        double tariff = stoi(vec4[7]);
        int time = stoi(vec4[8]);
        TripInformation* tripInfo = new TripInformation(rideId, startX, startY, endX, endY, numOfPassengers, tariff, time);
        tripInfo->setDriverId(stoi(vec4[9]));

        ///testing for receiving of serialized trip info .
        std::cout << "this is a test for receiving info trip:"<< std::endl;
        std::cout << tripInfo->getDriverId() << endl;
//    }
//    if(stoi(vec4[0]) == 2){
        udp.reciveData(buffer, sizeof(buffer));///receiving data from the client


        std::cout << "receiving tripinfo from server in case of flag 2:" << std::endl;
        /// deserialize of trip info
        string str9(buffer, sizeof(buffer));
        std::string tripParts9;
        boost::iostreams::basic_array_source<char> device9(str9.c_str(), str9.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s9(device9);
        boost::archive::binary_iarchive ia9(s9);
        ia9 >> tripParts9;

        ///spliting up trip info string and creating new trip info.
        std::vector<std::string> vec9 = beginningInfoReader.split(tripParts9);
        //why??
//        driverId = stoi(vec9[1]);
        // todo why was here this shit with int??
//        int driverId = stoi(vec4[1]);
        Point p = driver->getTaxiCab()->getLocation()->getPoint();
        std::cout << p << std::endl;
        driver->getTaxiCab()->move();
        Point p2 = driver->getTaxiCab()->getLocation()->getPoint();
        std::cout << p2 << std::endl;

    }

    return 0;
}