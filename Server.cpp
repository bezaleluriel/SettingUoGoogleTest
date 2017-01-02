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
        }
    }

    //receiving first choice from option menu 1-6.
    std::cin >> choice;
    //we will now receive orders as an int continuously until we receive the number 7.
    while (choice!=7){
        ///in case choice equals 1:
        if(choice == 1){

            ///receiving and desrializing driver.
            std::string a;
            std::cin >> a;///receiving number of drivers expected
            std::cout << "Server Is Running" <<std::endl;
            udp.reciveData(buffer, sizeof(buffer));///receiving data from the client
            string str(buffer, sizeof(buffer));
            std::string driverInfo;
            boost::iostreams::basic_array_source<char> device(str.c_str(), str.size());
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
            boost::archive::binary_iarchive ia(s2);
            ia >> driverInfo;
            std::cout << "this is a test for receiving driver:";
            std::cout << driverInfo << endl;
            mainFlow.choiceMenu(5,driverInfo);

            ///serialize and send the drivers cab to the client.
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

        ///in case choice equals 6:
        if (choice == 6){
            mainFlow.choiceMenu(choice);
        }

        ///in case choice equals 9:
        if(choice == 9){
            TripInformation* tripInformation = mainFlow.changeTime();
            if(tripInformation != NULL){
                mainFlow.getTaxiCenter()->assignDrivers();
                std::string tripParts;
                int tripId = tripInformation->getRideId();
                int startX = tripInformation->getStart().getX();
                int startY = tripInformation->getStart().getY();
                int endX = tripInformation->getEnd().getX();
                int endY = tripInformation->getEnd().getY();
                int numOfPassengers = tripInformation->getNumberOfPassengers();
                double tariff = tripInformation->getTariff();
                int time = tripInformation->getStartTime();
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

            }
        }
        std::cin >> choice;
    }
    //in case the choice number is 7 we exit the program.
    return 0;
}