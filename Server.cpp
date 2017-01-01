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

/**
 * main - this class gets input from user for size point start and end,
 * creates a reader to interperates the info.
 * then creates a grid and bfs and runs the algorithm that prints out
 * the b shortest way.
 * @return 0 in the end.
 */
//BOOST_CLASS_EXPORT_GUID(StandardCab, "StandardCab")
//BOOST_CLASS_EXPORT_GUID(LuxuryCab, "LuxuryCab")

int main() {
//    std::cout << "Server Is Running" <<std::endl;
//    Udp udp(1, 5555);///opening port
//    udp.initialize();///connecting to port
//    char buffer[1024];
//    udp.reciveData(buffer, sizeof(buffer));///receiving data from the client
//    string str(buffer, sizeof(buffer));
//    Driver *driver;///creating a pointer to driver test
//    boost::iostreams::basic_array_source<char> device(str.c_str(), str.size());
//    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
//    boost::archive::binary_iarchive ia(s2);
//    ia >> driver;///serialized object will be put in this pointer to driversTest
//    std::cout << driver->getId() << endl;
//
//  //  cout << buffer << endl;
//    udp.reciveData(buffer, sizeof(buffer));


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
        //if choice equals 6 then there is no string to be sent to it .
        if (choice == 6){
           mainFlow.choiceMenu();
        }
        if(choice == 1){
            std::string a;
            std::cin >> a;
            std::cout << "Server Is Running" <<std::endl;
            Udp udp(1, 5555);///opening port
            udp.initialize();///connecting to port
            char buffer[1024];
            udp.reciveData(buffer, sizeof(buffer));///receiving data from the client
            string str(buffer, sizeof(buffer));
            Driver *driver;///creating a pointer to driver test
            boost::iostreams::basic_array_source<char> device(str.c_str(), str.size());
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
            boost::archive::binary_iarchive ia(s2);
            ia >> driver;///serialized object will be put in this pointer to driversTest
            std::cout << driver->getId() << endl;

            mainFlow.choiceMenu(3,"0,1,H,R");
            mainFlow.addDriver(driver);
            BaseCab* taxi= driver->getTaxiCab();



            std::string serial_str;
            boost::iostreams::back_insert_device<std::string> inserter(serial_str);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
            boost::archive::binary_oarchive oa(s);
            oa << taxi;
            s.flush();
            char buffer2[1024];
            udp.sendData(serial_str);


            //  cout << buffer << endl;
            udp.reciveData(buffer, sizeof(buffer));
        }
        else{
            std::cin >> s;
            mainFlow.choiceMenu(choice, s);
        }
        std::cin >> choice;
    }
    //in case the choice number is 7 we exit the program.
    return 0;
}