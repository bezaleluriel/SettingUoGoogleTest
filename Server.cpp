#include <iostream>
#include "pthread.h"
#include "unistd.h"
#include "src/sockets/Socket.h"
#include "src/sockets/Tcp.h"
#include "src/ThreadInfo.h"
#include <netinet/in.h>
#include "src/TaxiCenter.h"

// DECLERATIONS:
void* getNewClients(void* threadInformation);
void* clientHandler(void* threadInformation);


int main(int argc,char* argv[]) {
    int numOfObstacles;
    int choice;
    MainFlow mainFlow;
    TaxiCenter* taxiCenter;
    std::vector<std::string> addObstacles;
    std::string obstacleLocation;
    std::string size;
    std::string numberOfDrivers;
    std::string choiceInput;
    pthread_t t1;

    //receiving the size of the grid from the user.
    std::getline(std::cin, size);
    //giving the size to main flow for parsing.
    mainFlow.parseSize(size);
    //creating a grid with the size that was parsed by mainflowvec.
    Grid grid(mainFlow.getMapX(),mainFlow.getMapY());
    //setting the grid as the map of main flow.
    mainFlow = MainFlow(&grid);
    mainFlow.parseSize(size);
    taxiCenter = mainFlow.getTaxiCenter();
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
        //in case choice equals 1: we need to receive a number of drivers.
        if(choice == 1){
            //receiving a string representing the number of drivers expected.
            std::cin >> numberOfDrivers;

            //TEST
             std::cout << "creating thread info class and creating main thread." <<std::endl;

            //creating a threadinfo class to send to the main thread we will create.
            ThreadInfo* threadInfo;
            threadInfo = new ThreadInfo(&mainFlow ,atoi(argv[1]), stoi(numberOfDrivers), addObstacles);

            //creating a main thread that will create all other threads.
            int status = pthread_create(&t1,NULL,getNewClients,(void*)threadInfo);
            if(status) {
                cout<<"ERROR! ";
            }

        }

        //IN CASE CHOICE IS A NUMBER FROM 2-5:
       else if((choice > 1) && (choice < 6)){
            std::cin >> choiceInput;
            mainFlow.choiceMenu(choice, choiceInput);
        }

        //IN CASE CHOICE EQUALS 9 :
       else if(choice == 9){
            //we increment the time by 1.
            mainFlow.changeTime();
            taxiCenter->assignDrivers();
            std::list<TripInformation*>::iterator tripIt = taxiCenter->getTripInfoList()->begin();
            while(tripIt != taxiCenter->getTripInfoList()->end()){
                if ((*(tripIt))->getStartTime() == taxiCenter->getTime()){
                    //std::cout << " the driver id in main server is: "<< (*(tripIt))->getDriverId() << std::endl;
                    if(taxiCenter->getTripInfoList()->empty()){std::cout << "eeempty" << std::endl;}
                    if(taxiCenter->getDriverList()->empty()){std::cout << "empty" << std::endl;}
                    instructionsMap.find((*tripIt)->getDriverId())->second.push(1);
                }
                if (((*(tripIt))->getStartTime() < taxiCenter->getTime()) && ((*(tripIt))->getHasDriver()) && !((*(tripIt))->getRideIsOver())){
                    instructionsMap.find((*tripIt)->getDriverId())->second.push(2);
                }
                tripIt++;
            }
        }
        std::cin >> choice;
    }

    pthread_join(t1,NULL);
    //in case the choice number is 7 we exit the program and notify client to exit as well.
    std::map<int,std::queue<int>>::iterator instructionsIt = instructionsMap.begin();
    //NOTIFYING ALL THREADS THAT PROGRAM SHOULD END.
    while(instructionsIt != instructionsMap.end()){
        (*(instructionsIt)).second.push(7);
        instructionsIt++;
    }

   // pthread_join(t1,NULL);
    // IF THE NUMBER RECEIVED IS 7 WE EXIT.;
    exit(0);

}



/**
 *
 * @param threadInfo
 * @return hhh
 */
//Main thread for receiving new client connections.
void* getNewClients(void* threadInformation) {
    ThreadInfo* threadInfo;
    threadInfo = (ThreadInfo*) threadInformation;
    int port = threadInfo->getPort();
    int numberOfDrivers = threadInfo->getNumberOfDrivers();

    //only here the socket will be put in the thread info .
    Socket *server = new Tcp(1, port);
    //SETTING SOCKET IN PTHREAD FOR ALL SUB THREADS TO USE.
    threadInfo->setSocket(server);
    //creates the actual socket , binds to a specific port and listens .....
    server->initialize();
    int goodReception;

    //TEST
    std::cout << "Connection with " << server->getSocketDescriptor() << " established!" << std::endl;

    for(int i=0;i<numberOfDrivers;++i) {
        //only now we accept.
        goodReception= server->acceptClient();
        if (goodReception < 0) {
            //return an error represent error at this method
            cout << "Connection not established!" << endl;
        }else {
            pthread_t myThread;
            //int *sockID = new int(server->getSocketDescriptor());
            int status = pthread_create(&myThread,NULL,clientHandler,(void*)threadInfo);
            if(status) {
                cout<<"ERROR! ";
            }
            pthread_join(myThread,NULL);

            //TEST
            std::cout << "Connection with " << server->getSocketDescriptor() << " established!" << std::endl;
        }
    }
}


/**
 *
 * @param threadInfo
 * @return
 */
void* clientHandler(void *threadInformation) {
    char buffer[1024];

    ThreadInfo* threadInfo;
    threadInfo = (ThreadInfo*) threadInformation;
    MainFlow* mainFlow = threadInfo->getMainFlow();
    TaxiCenter* taxiCenter = mainFlow->getTaxiCenter();
    Socket* socket = threadInfo->getSocket();
    int port = threadInfo->getPort();
    std::vector<std::string> addObstacles = threadInfo->getAddObstacles();

    //RECEIVING SERIALIZED DRIVER AND ADDING HIM TO TAXI CENTER.
    socket->reciveData(buffer, sizeof(buffer));
    usleep(1);
    string str1(buffer, sizeof(buffer));
    std::string driverInfo;
    boost::iostreams::basic_array_source<char> device1(str1.c_str(), str1.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s1(device1);
    boost::archive::binary_iarchive ia1(s1);
    ia1 >> driverInfo;
    std::cout << "this is a test for receiving driver: "<< std::endl;
    std::cout << "the driver info string is:" <<driverInfo << std::endl;

    //CREATE DRIVER AND ADD IT TO TAXI CENTER - goes to option 5 in main flow menu - add a driver.
    mainFlow->choiceMenu(5,driverInfo);

    //SERIALIZING AND SENDING GRID SIZE AND OBSTACLES LOCATIONS.
    std::string mapInfo;
    mapInfo += std::to_string(mainFlow->getMapX());
    mapInfo += ',';
    mapInfo += std::to_string(mainFlow->getMapY());
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
    socket->sendData(mapInfoSerialized);
    usleep(1);

    //TEST
    std:: cout << "just sent map info data: "<< mapInfo << std::endl;

    //SERIALIZE AND SEND THE DRIVERS TAXI CAB.
    BeginningInfoReader beginningInfoReader;
    std::vector<std::string> driverVec;
    std::cout << "splitting driver info: " << driverInfo << std::endl;
    driverVec = beginningInfoReader.split(driverInfo);
    BaseCab* cab;
    int driverId = stoi(driverVec[0]);
    std::list<Driver*>::iterator driverIt = taxiCenter->getDriverList()->begin();
    while(driverIt != taxiCenter->getDriverList()->end()){
        if((*(driverIt))->getId() == driverId){
            cab= (*(driverIt))->getTaxiCab();
            break;
        }
        else{
            driverIt++;
        }
    }

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
    std::cout << "sending taxi info: " << taxiInfo << std::endl;
    socket->sendData(taxiInfoSerialized);
    usleep(1);

    //INFINITE LOOP CHECKS WHAT THE MAP VALUE OF A SPECIFIC DRIVER ID IS AND TELLS HIM WHAT TO DO.
    int blabla2 = instructionsMap.find(driverId)->second.front();
    std:cout << "the driver id in the inifinite loop is: " << taxiCenter->getDriverList()->front()->getId() << std::endl;
    std::cout << blabla2 << std::endl;


    while(instructionsMap.find(driverId)->second.front() != 7){

//        if (instructionsMap.find(driverId)->second.front() == 0){
//            mainFlow.choiceMenu(5,driverInfo);
//        };


        //IF FLAG IN MAP FOR THIS SPECIFIC DRIVER IS 1 - ATTACH TRIP INFO
        if(instructionsMap.find(driverId)->second.front() == 1){
            instructionsMap.find(driverId)->second.pop();
            //FINDING THIS DRIVER'S TRIP INFO IN THE LIST IN TAXI CENTER.
            TripInformation* tripInformation;
            driverIt = taxiCenter->getDriverList()->begin();
            while(driverIt != taxiCenter->getDriverList()->end()){
                if((*(driverIt))->getId() == driverId){
                    tripInformation = (*(driverIt))->getTripInformation();
                    break;
                }
                else{
                    driverIt++;
                }
            }

            //SEND THE TRIP INFO TO THE CLIENT.

            //TEST
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
            socket->sendData(serial_str4);
            sleep(1);
            tripParts.clear();
        }

        //IN THIS CASE WE NEED TO TELL THE DRIVER TO MOVE.
        if(instructionsMap.find(driverId)->second.front() == 2){

            instructionsMap.find(driverId)->second.pop();

            //TEST
            Point location = taxiCenter->getTaxiList()->front()->getLocation()->getPoint();
                 std::cout << "before move" << location << std::endl;

            taxiCenter->getTo();
            taxiCenter->completeTrip();

            //TEST
            Point location2 = threadInfo->getMainFlow()->getTaxiCenter()->getTaxiList()->front()->getLocation()->getPoint();
               std::cout << "after move" << location2 << std::endl;

            TripInformation* tripInformation;
            driverIt = taxiCenter->getDriverList()->begin();
            while(driverIt != taxiCenter->getDriverList()->end()){
                if((*(driverIt))->getId() == driverId){
                    tripInformation = (*(driverIt))->getTripInformation();
                    break;
                }
                else{
                    driverIt++;
                }
            }

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
            socket->sendData(serial_str5);
            sleep(1);
            tripParts2.clear();
        }
    }

    //IF THE NUMBER IN THE MAP FOR THIS DRIVER IS 7 WE NOTIFY THE CLIENT AND THE THREAD DIES.
    std::string exitFlag;
    exitFlag += '7';//flag
    std::string serial_str6;
    boost::iostreams::back_insert_device<std::string> inserter6(serial_str6);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s6(inserter6);
    boost::archive::binary_oarchive oa6(s6);
    oa6 << exitFlag;
    s6.flush();
    socket->sendData(serial_str6);
    sleep(1);

}









//void* getNewClients(void* port);
//
//
//int main(int argc,char* argv[]) {
//    pthread_t t1;
//    int* port = new int(atoi(argv[0]));
//    for(int i=0; i<3 ; ++i){
//        int status = pthread_create(&t1,NULL,getNewClients,(void*)port);
//    }
//    pthread_join(t1,NULL);
//
//}
//
////Main thread for receiving new client connections.
//void* getNewClients(void* port) {
//
//        client->initialize();
//        cout << "Connection with "<< client->getSocketDescriptor() << " established!" <<endl ;
//}

//void *print1(void *ptr) {
//    int message = *((int*)ptr);
//    cout << "i:"<<message<<"\n";
//}
//
//class Multi {
//    public:
//    int i;
//    char c;
//    Multi(int arg1,char arg2):i(arg1),c(arg2){}
//
//};
//
//void *print2(void *ptr) {
//    Multi *m;
//    m= (Multi*)ptr;
//    sleep(5);
//    cout<<m->i <<" "<< m->c <<"\n";
//}
//
//int main() {
//    //defining a server.
//    Socket* server = new Tcp(0, 5555);
//    server->initialize();
//
//
//
//
//    pthread_t t1,t2;
//    int *data = new int;
//    *data = 2;
//    int status = pthread_create(&t1,NULL,print1,(void*)data);
//    if(status) {
//        cout<<"ERROR!"<<endl;
//    }
//    Multi *m = new Multi(1,'a');
//    status = pthread_create(&t2,NULL,print2,(void*)m);
//    if(status) {
//        cout<<"ERROR!"<<endl;
//    }
////    sleep(4);
//
//    pthread_join(t1,NULL);
//    pthread_join(t2,NULL);
//
//}