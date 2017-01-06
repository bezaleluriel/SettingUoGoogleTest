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

int main() {

    Udp udp(1, 5555);///opening port
    udp.initialize();///connecting to port
    char buffer[1024];
    MainFlow mainFlow;
    std::vector<std::string> addObstacles;
    std::string size;
    int numOfObstacles;
    std::string obstacleLocation;
    int choice;
    std::string s;
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
        ///in case choice equals 1:
        if(choice == 1){
           // std::cout << "choice1" << std::endl;

            //TODO - next time we will need to receive more then 1 driver (loop)
            ///receiving and desrializing driver.
            std::string a;
            std::cin >> a;///receiving number of drivers expected
            //std::cout << "Server Is Running" <<std::endl;
            udp.reciveData(buffer, sizeof(buffer));///receiving data from the client
            string str(buffer, sizeof(buffer));
            std::string driverInfo;
            boost::iostreams::basic_array_source<char> device(str.c_str(), str.size());
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
            boost::archive::binary_iarchive ia(s2);
            ia >> driverInfo;
            //std::cout << "this is a test for receiving driver:"<< std::endl;
            //std::cout << driverInfo << std::endl;
            mainFlow.choiceMenu(5,driverInfo);


            ///serializing and sending grid size, and obstacles location.
            std::string mapInfo;
            mapInfo += size;
            while(!(addObstacles.empty())){
                mapInfo += ',';
                mapInfo += addObstacles.back();
                addObstacles.pop_back();
            }
            std::string serial_str6;
            boost::iostreams::back_insert_device<std::string> inserter6(serial_str6);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s6(inserter6);
            boost::archive::binary_oarchive oa6(s6);
            oa6 << mapInfo;
            s6.flush();
            udp.sendData(serial_str6);

            //TODO - next time we will need to send more then 1 taxi (loop)
            ///serialize and send the drivers cab to the client.
            ///for next time - BaseCab* cab= driver->get taxi
            BaseCab* cab= mainFlow.getTaxiCenter()->getDriverList()->front()->getTaxiCab();
            char b;
            char c;
            std::string g1;
            std::string g2;
            std::string addChars;
            int cabId = cab->getCabId();
            int taxiType = cab->getTaxiType();
            Manufacturer manufacturer = cab->getManufacturer();
            if(manufacturer == Manufacturer::Fiat){b = 'F';}
            if(manufacturer == Manufacturer::Honda){b = 'H';}
            if(manufacturer == Manufacturer::Subaro){b = 'S';}
            if(manufacturer == Manufacturer::Tesla){b = 'T';}
            Color color = cab->getColor();
            if(color == Color::Blue){c = 'B';}
            if(color == Color::Green){c = 'G';}
            if(color == Color::Pink){c = 'P';}
            if(color == Color::Red){c = 'R';}
            if(color == Color::White){c = 'W';}
            g1 = std::to_string(cabId);
            g2 = std::to_string(taxiType);
            addChars+=g1;
            addChars+=',';
            addChars+=g2;
            addChars+=',';
            addChars+=b;
            addChars+=',';
            addChars+=c;

            ///serialize and send taxi info string to client.
            std::string serial_str;
            boost::iostreams::back_insert_device<std::string> inserter(serial_str);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s5(inserter);
            boost::archive::binary_oarchive oa(s5);
            oa << addChars;
            s5.flush();
            udp.sendData(serial_str);
        }


        ///in case choice is a number from 2-5:
        if((choice > 1) && (choice < 6)){
            std::cin >> s;
            mainFlow.choiceMenu(choice, s);
        }

//        ///in case choice equals 6:
//        if (choice == 6){
//            mainFlow.choiceMenu(choice);
//        }

        ///in case choice equals 9:
        if(choice == 9){
                /**
             * TODO - every time the command 9 is given we will srialize and send
             * 3 vectors to the other side.
             * first one - with all of the trip infos we need to attach to drivers.
             * second one -  id's of all drivers that need to move.
             * third one - destination points accordingley.
             * we are now sending a flag 1 if we need to attach a trip info to a driver.
             * 2- if we want to give the 'go' order.
             * next time we won't need this because client will know which vector has
             * drivers that need to move or to attach trip info.
             */
                TripInformation* tripInformation = mainFlow.changeTime();
              //  std::cout << "choice9 the time now is: " << mainFlow.getTaxiCenter()->getTime();
                Point currLocation = mainFlow.getTaxiCenter()->getDriverList()->front()->getLocation()->getPoint();
               // std::cout << " and the location now is: " << currLocation << std::endl;
                if((tripInformation != NULL  )){

                    mainFlow.getTaxiCenter()->assignDrivers();
                    ///in case we need to attach trip info to driver. represented by flag '1'.
                    if(tripInformation->getStartTime() == mainFlow.getTaxiCenter()->getTime()){
                 //       std::cout << "flag1" << std::endl;
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
                        tripParts += std::to_string(tripId);
                        tripParts += ',';
                        tripParts += std::to_string(startX);
                        tripParts += ',';
                        tripParts += std::to_string(startY);
                        tripParts += ',';
                        tripParts += std::to_string(endX);
                        tripParts += ',';
                        tripParts += std::to_string(endY);
                        tripParts += ',';
                        tripParts += std::to_string(numOfPassengers);
                        tripParts += ',';
                        tripParts += std::to_string(tariff);
                        tripParts += ',';
                        tripParts += std::to_string(time);
                        tripParts += ',';
                        tripParts += std::to_string(tripInformation->getDriverId());


                        ///sending trip info to client:
                        std::string serial_str3;
                        boost::iostreams::back_insert_device<std::string> inserter3(serial_str3);
                        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s3(inserter3);
                        boost::archive::binary_oarchive oa(s3);
                        oa << tripParts;
                        s3.flush();
                        udp.sendData(serial_str3);
                        tripParts.clear();
                    }

                    ///in case we give 'go' order. represented by flag '2'.
                    //if(tripInformation->getStartTime() == mainFlow.getTaxiCenter()->getTime() - 1){
                    if(tripInformation->getStartTime() < mainFlow.getTaxiCenter()->getTime()){
                   //     std::cout << "flag2" << std::endl;
                        //TODO make a func in taxi center that finds a driver by id and tell him and his cab to move.
                        Point p = mainFlow.getTaxiCenter()->getTaxiList()->front()->getLocation()->getPoint();
                     //   std::cout << "before move" << p << std::endl;

                        mainFlow.getTaxiCenter()->getTo();
                        Driver* uriel = mainFlow.getTaxiCenter()->getDriverList()->front();
                        mainFlow.getTaxiCenter()->completeTrip();


                        Point p2 = mainFlow.getTaxiCenter()->getTaxiList()->front()->getLocation()->getPoint();
                      //  std::cout << "after move" << p2 << std::endl;

                        std::string tripParts2;
                        tripParts2 += '2';///flag
                        tripParts2 += tripInformation->getDriverId();
                        std::string serial_str8;
                        boost::iostreams::back_insert_device<std::string> inserter8(serial_str8);
                        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s8(inserter8);
                        boost::archive::binary_oarchive oa8(s8);
                        oa8 << tripParts2;
                        s8.flush();
                        udp.sendData(serial_str8);
                        tripParts2.clear();
                    }
                }
        }
        std::cin >> choice;
    }
    //in case the choice number is 7 we exit the program.
   // return 0;
   exit(0);
}