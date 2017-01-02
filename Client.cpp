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
    BeginningInfoReader beginningInfoReader;
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

    ///receiving seriaized taxi cab.
    udp.reciveData(buffer, sizeof(buffer));///receiving data from the client
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
    Structure* map = new Grid(11,11);
    BaseCab* standardCab;
    BaseCab* luxuryCab;
    //in case the taxi type is standard cab:
    if(taxiType == 1){
        standardCab = new StandardCab(cabId, taxiType, manufacturer, color, map);
        standardCab->setLocation(map->getNode(Point(0,0)));
    }
    //in case the taxi type is luxury cab:
    if(taxiType == 2){
        luxuryCab = new LuxuryCab(cabId, taxiType, manufacturer, color, map);
        luxuryCab->setLocation(map->getNode(Point(0,0)));
    }

    ///test for receiving cab from server:
    std::cout << "this is a test for receiving the serialized cab:";
    std::cout << standardCab->getCabId() << "," ;
    std::cout << standardCab->getTaxiType() << std::endl;

    ///receiving tripinfo from server:
    udp.reciveData(buffer, sizeof(buffer));///receiving data from the client
    /// deserialize of trip info
    string str4(buffer, sizeof(buffer));
    std::string tripParts;
    boost::iostreams::basic_array_source<char> device(str4.c_str(), str4.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device);
    boost::archive::binary_iarchive ia4(s4);
    ia4 >> tripParts;
    ///spliting up trip info string and creating new trip info.
    std::vector<std::string> vec4 = beginningInfoReader.split(tripParts);
    int rideId = stoi(vec4[0]);
    int startX = stoi(vec4[1]);
    char startY = (vec4[2])[0];
    int endX = stoi(vec4[3]);
    int endY = stoi(vec4[4]);
    int numOfPassengers = stoi(vec4[5]);
    double tariff = stoi(vec4[6]);
    int time = stoi(vec4[7]);
    TripInformation* tripInfo = new TripInformation(rideId, startX, startY, endX, endY, numOfPassengers, tariff, time);
    tripInfo->setDriverId(stoi(vec4[8]));

    ///testing for receiving of serialized trip info .
    std::cout << "this is a test for receiving info trip:";
    std::cout << tripInfo->getDriverId() << endl;

    ///connecting trip info with correct driver:



    return 0;
}