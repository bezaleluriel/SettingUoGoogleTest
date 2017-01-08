#include <iostream>
#include "src/Bfs.h"
#include "src/BeginningInfoReader.h"
#include "src/MainFlow.h"
//#include <boost/thread.hpp>
#include <iostream>
#include <boost/serialization/export.hpp>
#include "src/sockets/Udp.h"
#include "src/Driver.h"
#include "src/StandardCab.h"
#include "src/LuxuryCab.h"
#include "src/Grid.h"
#include <unistd.h>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <boost/lexical_cast.hpp>
/**
 * main - this class gets input from user for size point start and end,
 * creates a reader to interperates the info.
 * then creates a grid and bfs and runs the algorithm that prints out
 * the b shortest way.
 * @return 0 in the end.
 */
BOOST_CLASS_EXPORT_GUID(StandardCab, "src/StandardCab")
BOOST_CLASS_EXPORT_GUID(LuxuryCab, "src/LuxuryCab")
BOOST_CLASS_EXPORT_GUID(Grid,"src/Grid")

int main(int argc, char *argv[]) {

    Udp udp(1, atoi(argv[1]));///opening port
    udp.initialize();///connecting to port
    char buffer[1024];
    int numOfObstacles;
    int choice;
    MainFlow mainFlow;
    std::vector<std::string> addObstacles;
    std::string obstacleLocation;
    std::string size;
    std::string numberOfDrivers;
    std::string choiceInput;

    //receiving the size of the grid from the user.
    std::getline(std::cin, size);
    //giving the size to main flow for parsing.
    mainFlow.parseSize(size);
    //creating a grid with the size that was parsed by mainflow.
    Grid grid(mainFlow.getMapX(),mainFlow.getMapY());
    //setting the grid as the map of main flow.
    mainFlow = MainFlow(&grid);
    //receiving the number of obstacles from the user.
    std::cin >> numOfObstacles;
    //setting the number of obstacles received from the user.
    mainFlow.setNumOfObstacles(numOfObstacles);
    //if there are obstacles we will get a string from the user representing their location.
    if(numOfObstacles>0){
        for(int i=0; i<numOfObstacles; i++){
            std:: cin >> obstacleLocation;
            mainFlow.setObstacle(obstacleLocation);
            addObstacles.push_back(obstacleLocation);
        }
    }

    //receiving first choice from option menu 1-6.
    std::cin >> choice;
    //we will now receive orders as an int continuously until we receive the number 7.
    while (choice!=7){
        ///in case choice equals 1: we need to receive a number of drivers.
        if(choice == 1){
            //receiving a string representing the number of drivers expected.
            std::cin >> numberOfDrivers;
            std::cout << "Server Is Running" <<std::endl;
            // receiving serialized drivers and adding them to the driver's list in taxi center.
            for(int i = 0; i<std::atoi(numberOfDrivers.c_str()); i++){
                udp.reciveData(buffer, sizeof(buffer));
                string str1(buffer, sizeof(buffer));
                std::string driverInfo;
                boost::iostreams::basic_array_source<char> device1(str1.c_str(), str1.size());
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s1(device1);
                boost::archive::binary_iarchive ia1(s1);
                ia1 >> driverInfo;
                std::cout << "this is a test for receiving driver: "<< std::endl;
                std::cout << "the driver info string is:" <<driverInfo << std::endl;
                //goes to option 5 in main flow menu - add a driver.
                mainFlow.choiceMenu(5,driverInfo);
                driverInfo.clear();
            }

            ///serializing and sending grid size, and obstacles location.
            std::string mapInfo;
            mapInfo += size;
            while(!(addObstacles.empty())){
                mapInfo += ',';
                mapInfo += addObstacles.back();
                addObstacles.pop_back();
            }
            std::string mapInfoSerialized;
            boost::iostreams::back_insert_device<std::string> inserter2(mapInfoSerialized);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s2(inserter2);
            boost::archive::binary_oarchive oa2(s2);
            oa2 << mapInfo;
            s2.flush();
            udp.sendData(mapInfoSerialized);
            std:: cout << "just sent map info data: "<< mapInfo << std::endl;

            ///serialize and send the drivers cab to the client.
            std::list<Driver*>::iterator driverIt = mainFlow.getTaxiCenter()->getDriverList()->begin();

            for(int i = 0; i<atoi(numberOfDrivers.c_str()); i++){
                BaseCab* cab= (*(driverIt))->getTaxiCab();
                char carType;
                char colorType;
                std::string taxiInfo;
                int cabId = cab->getCabId();
                int taxiType = cab->getTaxiType();
                Manufacturer manufacturer = cab->getManufacturer();
                if(manufacturer == Fiat){carType = 'F';}
                if(manufacturer == Honda){carType = 'H';}
                if(manufacturer == Subaro){carType = 'S';}
                if(manufacturer == Tesla){carType = 'T';}
                Color color = cab->getColor();
                if(color == Blue){colorType = 'B';}
                if(color == Green){colorType = 'G';}
                if(color == Pink){colorType = 'P';}
                if(color == Red){colorType = 'R';}
                if(color == White){colorType = 'W';}
                taxiInfo+=  boost::lexical_cast<std::string>(cabId);//to_string(cabId);
                taxiInfo+=',';
                taxiInfo+=boost::lexical_cast<std::string>(taxiType);//to_string(taxiType);
                taxiInfo+=',';
                taxiInfo+=carType;
                taxiInfo+=',';
                taxiInfo+=colorType;

                ///serialize and send taxi info string to client.
                std::string taxiInfoSerialized;
                boost::iostreams::back_insert_device<std::string> inserter3(taxiInfoSerialized);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s3(inserter3);
                boost::archive::binary_oarchive oa3(s3);
                oa3 << taxiInfo;
                s3.flush();
                udp.sendData(taxiInfoSerialized);
                std::cout << "just sent taxi info string : " << taxiInfo << std::endl;
                driverIt++;

            }
        }

        ///in case choice is a number from 2-5:
        if((choice > 1) && (choice < 6)){
            std::cin >> choiceInput;
            mainFlow.choiceMenu(choice, choiceInput);
        }

        ///in case choice equals 9: attach trip informartion\movecabs.
        if(choice == 9){

                TripInformation* tripInformation = mainFlow.changeTime();
                std::cout << "choice9 the time now is: " << mainFlow.getTaxiCenter()->getTime()<< std::endl;
                Point currLocation = mainFlow.getTaxiCenter()->getDriverList()->front()->getLocation()->getPoint();
                std::cout << " and the location now is: " << currLocation << std::endl;
                if((tripInformation != NULL  )){

                    mainFlow.getTaxiCenter()->assignDrivers();
                    ///in case we need to attach trip info to driver. represented by flag '1'.
                    if(tripInformation->getStartTime() == mainFlow.getTaxiCenter()->getTime()){
                        std::cout << "flag1" << std::endl;
                        std::string tripParts;
                        int tripId = tripInformation->getRideId();
                        int startX = tripInformation->getStart().getX();
                        int startY = tripInformation->getStart().getY();
                        int endX = tripInformation->getEnd().getX();
                        int endY = tripInformation->getEnd().getY();
                        int numOfPassengers = tripInformation->getNumberOfPassengers();
                        double tariff = tripInformation->getTariff();
                        int time = tripInformation->getStartTime();
                        tripParts += '1';
                        tripParts += ',';
                        tripParts += boost::lexical_cast<std::string>(tripId);//to_string(tripId);
                        tripParts += ',';
                        tripParts += boost::lexical_cast<std::string>(startX);//to_string(startX);
                        tripParts += ',';
                        tripParts += boost::lexical_cast<std::string>(startY);//to_string(startY);
                        tripParts += ',';
                        tripParts += boost::lexical_cast<std::string>(endX);//to_string(endX);
                        tripParts += ',';
                        tripParts += boost::lexical_cast<std::string>(endY);//to_string(endY);
                        tripParts += ',';
                        tripParts += boost::lexical_cast<std::string>(numOfPassengers);//to_string(numOfPassengers);
                        tripParts += ',';
                        tripParts += boost::lexical_cast<std::string>(tariff);//to_string(tariff);
                        tripParts += ',';
                        tripParts += boost::lexical_cast<std::string>(time);//to_string(time);
                        tripParts += ',';
                        tripParts += boost::lexical_cast<std::string>(tripInformation->getDriverId());//to_string(tripInformation->getDriverId());


                        ///sending trip info to client:
                        std::string serial_str4;
                        boost::iostreams::back_insert_device<std::string> inserter4(serial_str4);
                        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s4(inserter4);
                        boost::archive::binary_oarchive oa4(s4);
                        oa4 << tripParts;
                        s4.flush();
                        udp.sendData(serial_str4);
                        tripParts.clear();
                    }

                    ///in case we give 'go' order. represented by flag '2'.
                    if(tripInformation->getStartTime() < mainFlow.getTaxiCenter()->getTime()){

                        Point p = mainFlow.getTaxiCenter()->getTaxiList()->front()->getLocation()->getPoint();
                        std::cout << "before move" << p << std::endl;

                        mainFlow.getTaxiCenter()->getTo();
                        mainFlow.getTaxiCenter()->completeTrip();


                        Point p2 = mainFlow.getTaxiCenter()->getTaxiList()->front()->getLocation()->getPoint();
                        std::cout << "after move" << p2 << std::endl;

                        std::string tripParts2;
                        tripParts2 += '2';//flag
                        tripParts2 += ',';
                        tripParts2 += tripInformation->getDriverId();
                        std::string serial_str5;
                        boost::iostreams::back_insert_device<std::string> inserter5(serial_str5);
                        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s5(inserter5);
                        boost::archive::binary_oarchive oa5(s5);
                        oa5 << tripParts2;
                        s5.flush();
                        udp.sendData(serial_str5);
                        tripParts2.clear();
                    }
                }
        }
        std::cin >> choice;
    }

    //in case the choice number is 7 we exit the program and notify client to exit as well.
    std::string exitFlag;
    exitFlag += '7';//flag
    std::string serial_str6;
    boost::iostreams::back_insert_device<std::string> inserter6(serial_str6);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s6(inserter6);
    boost::archive::binary_oarchive oa6(s6);
    oa6 << exitFlag;
    s6.flush();
    udp.sendData(serial_str6);
    exitFlag.clear();
   // return 0;
   exit(0);
}