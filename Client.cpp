
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
//#include "src/GETIP.h"
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
    char buffer[1024];
    ///receiving info for driver and creating one.
    std::string info;
    cin >> info;
    std::vector<std::string> vec = beginningInfoReader.split(info);
    int driverId = atoi(vec[0].c_str());//stoi(vec[0]);
    int age = atoi(vec[1].c_str());//stoi(vec[1]);
    char status = (vec[2])[0];
    int experience = atoi(vec[3].c_str());//stoi(vec[3]);
    int vehicleId = atoi(vec[4].c_str());//stoi(vec[4]);
    Driver* driver = new Driver(driverId, age, status, experience, vehicleId);
    clientDriversList.push_back(driver);
    std::cout << "driver crated and pushed in list" <<std::endl;

    ///open socket
    Udp udp(0, atoi(argv[2]));
    udp.initialize();
    udp.setIp(argv[1]);

    ///serialize and send driver info.
    for(int i = 0; i<clientDriversList.size(); i++){
        std::string serial_str1;
        boost::iostreams::back_insert_device<std::string> inserter1(serial_str1);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter1);
        boost::archive::binary_oarchive oa1(s1);
        oa1 << info;
        s1.flush();
        udp.sendData(serial_str1);
        //std::cout << "send driver info: " << info <<std::endl;
    }


    ///receiving serialized map info.
    udp.reciveData(buffer, sizeof(buffer));//receiving data from the client
    string str2(buffer, sizeof(buffer));
    std::string mapInfo;//creating a pointer to driver test
    boost::iostreams::basic_array_source<char> device2(str2.c_str(), str2.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device2);
    boost::archive::binary_iarchive ic2(s2);
    ic2 >> mapInfo;//serialized object will be put in this pointer to driversTest
    std::vector<std::string> mapInfoVec = beginningInfoReader.split(mapInfo);
    map = new Grid(atoi(mapInfoVec[0].c_str()), atoi(mapInfoVec[1].c_str()));//initiallizing size of grid.

    ///adding obstacles to grid.
    for(int i = 2; i<mapInfoVec.size(); i+=2){
        map->markObstacle(Point(atoi(mapInfoVec[i].c_str()),atoi(mapInfoVec[i+1].c_str())));
        //std::cout << " the current obstacle being marked is: "<< atoi(mapInfoVec[i].c_str()) <<","<<atoi(mapInfoVec[i+1].c_str())<< std::endl;
    }
    //std::cout << "received the map info serialization: "<< mapInfo <<std::endl;

    ///receiving seriaized taxi cab.
    udp.reciveData(buffer, sizeof(buffer));///receiving data from the client

    string str3(buffer, sizeof(buffer));
    std::string taxiInfo;///creating a pointer to driver test
    boost::iostreams::basic_array_source<char> device3(str3.c_str(), str3.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device3);
    boost::archive::binary_iarchive ic3(s3);
    ic3 >> taxiInfo;///serialized object will be put in this pointer to driversTest
    std::vector<std::string> vec2 = beginningInfoReader.split(taxiInfo);
    //std::cout << "received a seriaized taxi cab"<< taxiInfo<< std::endl;
    int cabId = atoi(vec2[0].c_str());
    int taxiType = atoi(vec2[1].c_str());
    char manufacturer = (vec2[2])[0];
    char color = (vec2[3])[0];
    BaseCab* taxi;
    //in case the taxi type is standard cab:
    if(taxiType == 1){
      //  std::cout << "in case the taxi type is standard cab"<< std::endl;
        taxi = new StandardCab(cabId, taxiType, manufacturer, color, map);
        taxi->setLocation(map->getNode(Point(0,0)));
        clientTaxiCabsList.push_back(taxi);
    }
    //in case the taxi type is luxury cab:
    if(taxiType == 2){
        //std::cout << "in case the taxi type is luxury cab"<< std::endl;
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
          //  std::cout << "taxi matched to driver" << std::endl;
            break;
        }
        else{
            taxiIt++;
        }
    }

    ///test for receiving cab from server:
    //std::cout << "this is a test for receiving the serialized cab id&taxitype:"<< std::endl;
    //std::cout << taxi->getCabId() << "," ;
    //std::cout << taxi->getTaxiType() << std::endl;

    ///receiving a string from server we will now what to do according to the first number:
    std::string choice = "0";
    while( atoi(choice.c_str()) != 7){
        udp.reciveData(buffer, sizeof(buffer));///receiving data from the client
        /// deserialize of trip info
        string str4(buffer, sizeof(buffer));
        boost::iostreams::basic_array_source<char> device4(str4.c_str(), str4.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device4);
        boost::archive::binary_iarchive ia4(s4);
        ia4 >> choice;
      //  std::cout << "choice string received from client: " <<choice << std::endl;

        ///splitting choice string to parts:
        std::vector<std::string> vec4 = beginningInfoReader.split(choice);

        ///if the first number is 1 we need to receive a trip info and attach it to a driver.
        if(atoi(vec4[0].c_str()) == 1){
        //    std:: cout <<"we are now attaching a trip info to the driver" << std::endl;
            int rideId = atoi(vec4[1].c_str());
            int startX = atoi(vec4[2].c_str());
            int startY = atoi(vec4[3].c_str());
            int endX = atoi(vec4[4].c_str());
            int endY = atoi(vec4[5].c_str());
            int numOfPassengers = atoi(vec4[6].c_str());
            double tariff = atoi(vec4[7].c_str());
            int time = atoi(vec4[8].c_str());
            ///creating a trip info from info received.
            TripInformation* tripInfo = new TripInformation(rideId, startX, startY, endX, endY, numOfPassengers, tariff, time);
            tripInfo->setDriverId(atoi(vec4[9].c_str()));
            ///getting the driver responsible for this ride and setteing this trip info as his member.
            driverIt = clientDriversList.begin();
            while(driverIt != clientDriversList.end()){
                if((*(driver)).getId() == tripInfo->getDriverId()){
                    (*(driverIt))->setTripInformation(tripInfo);
                    (*(driverIt))->setAvailable(false);
                    tripInfo->setHasDriver(true);
                    (*(driverIt))->getTaxiCab()->navigate((*(driverIt))->getTripInformation()->getEnd());
                    driverIt++;
                }
                else{
                    driverIt++;
                }
            }
        }
        ///in this case we need to tell the cab to move.
        if(atoi(vec4[0].c_str()) == 2){
          //  std:: cout <<"we are now giving driver the move order" << std::endl;
            //going through drivers list telling the unavailable ones to get to end point of their trip info.
            driverIt = clientDriversList.begin();
            while(driverIt != clientDriversList.end()){
                if(!((*(driverIt))->getAvailable())){
            //        std:: cout <<"driver location before movement: ";
              //      std:: cout <<(*(driverIt))->getLocation()->getPoint().getX()<<","<<(*(driverIt))->getLocation()->getPoint().getY()<<std::endl;
                    (*(driverIt))->getTaxiCab()->move();
                  //  std:: cout <<"driver location after movement: ";
                //    std:: cout <<(*(driverIt))->getLocation()->getPoint().getX()<<","<<(*(driverIt))->getLocation()->getPoint().getY()<<std::endl;

                }
                driverIt++;
            }

            driverIt = clientDriversList.begin();
            std::list<TripInformation*>::iterator tripInfoIt = clientTripInformationList.begin();

            ///get to func
            while(driverIt != clientDriversList.end()) {
                if (!((*(driverIt))->getAvailable()) &&
                    ((*(driverIt))->getTripInformation()->getEnd().compare((*(driverIt))->getLocation()->getPoint()))) {
                    //std:: cout <<"preforming get to function" << std::endl;
                    (*(driverIt))->getTripInformation()->setRideIsOver(true);
                    (*(driverIt))->setAvailable(true);
                    driverIt++;
                }
                else{
                    driverIt++;
                }
            }


            ///complete trip func
            tripInfoIt = clientTripInformationList.begin();
            while(clientTripInformationList.size()>0){
                if((clientTripInformationList.front()->getHasDriver()) && ((clientTripInformationList.front()->getRideIsOver()))){
                    delete[] clientTripInformationList.front();
                    clientTripInformationList.pop_front();
                }
                else{
                    break;
                }
            }
        }
    }

    ///we will ger to this point when we receive the 7 flag from server:
    //std:: cout << "this is the end" << std::endl;
    while(clientDriversList.size() > 0){
        delete[] clientDriversList.front();
        clientDriversList.pop_front();
    }
    while(clientTripInformationList.size() > 0){
        delete[] clientTripInformationList.front();
        clientTripInformationList.pop_front();
    }
//    while(clientTaxiCabsList.size() > 0){
//        delete[] clientTaxiCabsList.front();
//        clientTaxiCabsList.pop_front();
 //   }
    //std:: cout << "after deleting everything" << std::endl;

    return 0;
}