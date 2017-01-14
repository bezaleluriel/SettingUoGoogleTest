#include <iostream>
#include "src/sockets/Socket.h"
#include "src/sockets/Tcp.h"
#include "src/Driver.h"
#include "src/BeginningInfoReader.h"
#include "src/StandardCab.h"
#include "src/LuxuryCab.h"

//DECLERATIONS
void* createRoute(void* driver1);

//MAIN
int main(int argc, char *argv[])  {
    std::list <Driver*> clientDriversList;
    std::list <BaseCab*> clientTaxiCabsList;
    std::list <TripInformation*> clientTripInformationList;
    BeginningInfoReader beginningInfoReader;
    Structure* map ;
    char buffer[1024];

    //RECEIVING INFO FOR DRIVER FROM TERMINAL AND CREATING A DRIVER.
    std::string info;
    cin >> info;
    std::vector<std::string> vec = beginningInfoReader.split(info);
    int driverId = atoi(vec[0].c_str());
    int age = atoi(vec[1].c_str());
    char status = (vec[2])[0];
    int experience = atoi(vec[3].c_str());
    int vehicleId = atoi(vec[4].c_str());
    Driver* driver = new Driver(driverId, age, status, experience, vehicleId);
    clientDriversList.push_back(driver);


    //TEST
     std::cout << "driver crated and pushed in list" <<std::endl;
    //todo replace the Socket with Tcp and setIp
    Socket* client = new Tcp(0, atoi(argv[1]));
    client->initialize();


///    ///open socket
///    Udp udp(0, atoi(argv[2]));
///    udp.initialize();
///    udp.setIp(argv[1]);


    //SERIALIZE AND SEND DRIVER INFO.
    std::string serial_str1;
    boost::iostreams::back_insert_device<std::string> inserter1(serial_str1);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter1);
    boost::archive::binary_oarchive oa1(s1);
    oa1 << info;
    s1.flush();
    client->sendData(serial_str1);

    //TEST
    std::cout << "send driver info: " << info <<std::endl;


    //RECEIVING SERIALIZE MAP INFO.
    client->reciveData(buffer, sizeof(buffer));
    string str2(buffer, sizeof(buffer));
    std::string mapInfo;
    boost::iostreams::basic_array_source<char> device2(str2.c_str(), str2.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device2);
    boost::archive::binary_iarchive ic2(s2);
    ic2 >> mapInfo;
    std::vector<std::string> mapInfoVec = beginningInfoReader.split(mapInfo);
    map = new Grid(atoi(mapInfoVec[0].c_str()), atoi(mapInfoVec[1].c_str()));

    //ADDING OBSTACLES TO GRID.
    for(int i = 2; i<mapInfoVec.size(); i+=2){
        map->markObstacle(Point(atoi(mapInfoVec[i].c_str()),atoi(mapInfoVec[i+1].c_str())));

        //TEST
        std::cout << " the current obstacle being marked is: "<< atoi(mapInfoVec[i].c_str()) <<","<<atoi(mapInfoVec[i+1].c_str())<< std::endl;
    }

    //TEST
    std::cout << "received the map info serialization: "<< mapInfo <<std::endl;

    //RECEIVING SERIALIZED TAXI CAB.
    client->reciveData(buffer, sizeof(buffer));

    string str3(buffer, sizeof(buffer));
    std::string taxiInfo;
    boost::iostreams::basic_array_source<char> device3(str3.c_str(), str3.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device3);
    boost::archive::binary_iarchive ic3(s3);
    ic3 >> taxiInfo;
    std::vector<std::string> vec2 = beginningInfoReader.split(taxiInfo);

    //TEST
    std::cout << "received a seriaized taxi cab"<< taxiInfo<< std::endl;

    int cabId = atoi(vec2[0].c_str());
    int taxiType = atoi(vec2[1].c_str());
    char manufacturer = (vec2[2])[0];
    char color = (vec2[3])[0];
    BaseCab* taxi;
    //in case the taxi type is standard cab:
    if(taxiType == 1){

        //TEST
        std::cout << "in case the taxi type is standard cab"<< std::endl;

        taxi = new StandardCab(cabId, taxiType, manufacturer, color, map);
        taxi->setLocation(map->getNode(Point(0,0)));
        clientTaxiCabsList.push_back(taxi);
    }
    //in case the taxi type is luxury cab:
    if(taxiType == 2){

        //TEST
        std::cout << "in case the taxi type is luxury cab"<< std::endl;

        taxi = new LuxuryCab(cabId, taxiType, manufacturer, color, map);
        taxi->setLocation(map->getNode(Point(0,0)));
        clientTaxiCabsList.push_back(taxi);
    }

    //CONNECTING DRIVER WITH TAXI.
    std::list<Driver*>::iterator driverIt = clientDriversList.begin();
    std::list<BaseCab*>::iterator taxiIt = clientTaxiCabsList.begin();
    while(driverIt != clientDriversList.end()){
        if((*(driverIt))->getVehicleId() == taxi->getCabId()){
            (*(driverIt))->setTaxiCab(taxi);

            //TEST
            std::cout << "taxi matched to driver" << std::endl;

            break;
        }
        else{
            taxiIt++;
        }
    }

    //TEST FOR RECEIVING CAB FROM SERVER:
    std::cout << "this is a test for receiving the serialized cab id&taxitype:"<< std::endl;
    std::cout << taxi->getCabId() << "," ;
    std::cout << taxi->getTaxiType() << std::endl;

    //RECEIVING A STRING FROM SERVER WE WILL NOW CHOOSE WHAT TO DO ACCORDING TO THE FLAG IN BEGINNING.
    std::string choice = "0";
    while( atoi(choice.c_str()) != 7){
        client->reciveData(buffer, sizeof(buffer));
        //DESERIALIZATION OF TRIP INFO.
        string str4(buffer, sizeof(buffer));
        boost::iostreams::basic_array_source<char> device4(str4.c_str(), str4.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device4);
        boost::archive::binary_iarchive ia4(s4);
        ia4 >> choice;

        //TEST
        std::cout << "choice string received from client: " <<choice << std::endl;

        //SPLITTING CHOICE STRING TO PARTS:
        std::vector<std::string> vec4 = beginningInfoReader.split(choice);

        //if the first number is 1 we need to receive a trip info and attach it to a driver.
        if(atoi(vec4[0].c_str()) == 1){

            //TEST
            std:: cout <<"we are now attaching a trip info to the driver" << std::endl;

            int rideId = atoi(vec4[1].c_str());
            int startX = atoi(vec4[2].c_str());
            int startY = atoi(vec4[3].c_str());
            int endX = atoi(vec4[4].c_str());
            int endY = atoi(vec4[5].c_str());
            int numOfPassengers = atoi(vec4[6].c_str());
            double tariff = atoi(vec4[7].c_str());
            int time = atoi(vec4[8].c_str());

            //creating a trip info from info received.
            TripInformation* tripInfo = new TripInformation(rideId, startX, startY, endX, endY, numOfPassengers, tariff, time);
            tripInfo->setDriverId(atoi(vec4[9].c_str()));

            //getting the driver responsible for this ride and setting this trip info as his member.
            driverIt = clientDriversList.begin();
            while(driverIt != clientDriversList.end()){
                if((*(driver)).getId() == tripInfo->getDriverId()){
                    (*(driverIt))->setTripInformation(tripInfo);
                    (*(driverIt))->setAvailable(false);
                    tripInfo->setHasDriver(true);
                    pthread_t myThread;
                    int status1 = pthread_create(&myThread,NULL,createRoute,(void*)(*(driverIt)));
                    if(status1) {
                        cout<<"ERROR! ";
                    }
                    pthread_join(myThread,NULL);
                    driverIt++;
                    break;
                }
                else{
                    driverIt++;
                }
            }
        }

        //IN THIS CASE WE NEED TO TELL THE CAB TO MOVE.
        if(atoi(vec4[0].c_str()) == 2){

            //TEST
            std:: cout <<"we are now giving driver the move order" << std::endl;

            //going through drivers list telling the unavailable ones to get to end point of their trip info.
            driverIt = clientDriversList.begin();
            while(driverIt != clientDriversList.end()){
                if(!((*(driverIt))->getAvailable())){

                    //TESTS
                    std:: cout <<"driver location before movement: ";
                    std:: cout <<(*(driverIt))->getLocation()->getPoint().getX()<<","<<(*(driverIt))->getLocation()->getPoint().getY()<<std::endl;

                    (*(driverIt))->getTaxiCab()->move();

                    //TESTS
                    std:: cout <<"driver location after movement: ";
                    std:: cout <<(*(driverIt))->getLocation()->getPoint().getX()<<","<<(*(driverIt))->getLocation()->getPoint().getY()<<std::endl;

                }
                driverIt++;
            }

            driverIt = clientDriversList.begin();
            std::list<TripInformation*>::iterator tripInfoIt = clientTripInformationList.begin();

            //CALLING GET TO FUNC.
            while(driverIt != clientDriversList.end()) {
                if (!((*(driverIt))->getAvailable()) &&
                    ((*(driverIt))->getTripInformation()->getEnd().compare((*(driverIt))->getLocation()->getPoint()))) {

                    //TEST
                    std:: cout <<"preforming get to function" << std::endl;

                    (*(driverIt))->getTripInformation()->setRideIsOver(true);
                    (*(driverIt))->setAvailable(true);
                    driverIt++;
                }
                else{
                    driverIt++;
                }
            }


            //COMPLETE THE TRIP FUNC
            tripInfoIt = clientTripInformationList.begin();
            while(clientTripInformationList.size()>0){
                if((clientTripInformationList.front()->getHasDriver()) && ((clientTripInformationList.front()->getRideIsOver()))){
                    delete clientTripInformationList.front();
                    clientTripInformationList.pop_front();
                }
                else{
                    break;
                }
            }
        }
    }

    //WE WILL GET TO THIS POINT WHEN WE RECEIVE THE 7 FLAG FROM SERVER.

    //TEST
    std:: cout << "this is the end" << std::endl;

    while(clientDriversList.size() > 0){
        delete clientDriversList.front();
        clientDriversList.pop_front();
    }
    while(clientTripInformationList.size() > 0){
        delete clientTripInformationList.front();
        clientTripInformationList.pop_front();
    }
    while(clientTaxiCabsList.size() > 0){
        delete clientTaxiCabsList.front();
        clientTaxiCabsList.pop_front();
    }

    delete  map;

    //TEST
    std:: cout << "after deleting everything" << std::endl;

    return 0;

}

void* createRoute(void* driver1){
    Driver* driver;
    driver = (Driver*) driver1;
    driver->getTaxiCab()->navigate(driver->getTripInformation()->getEnd());

}