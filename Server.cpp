/// the instructions map need to be from int to queue.
/// we will have a secondmap from int to tropinfo .
///









#include <iostream>
#include "pthread.h"
#include "unistd.h"
#include "src/sockets/Socket.h"
#include "src/sockets/Tcp.h"
#include "src/ThreadInfo.h"
#include <netinet/in.h>
#include "src/TaxiCenter.h"
//declerations:

//declerations:
void* getNewClients(void* port);
void* printClientName(void *clientSocketID);


int main(int argc,char* argv[]) {
    ///create map , obstacles
    ///receive 1 and number ofclients.
    ///use get new clients thread to create all threads.

    pthread_t t1;

    int* port = new int(atoi(argv[1]));
    int status = pthread_create(&t1,NULL,getNewClients,(void*)port);
    pthread_join(t1,NULL);

    ////create global map

}


//Main thread for receiving new client connections.
void* getNewClients(void* port) {
    ///only here the socket will be put in the threadinfo .
    Socket *server = new Tcp(1, *(int*)port);
    ///creates the actual socket , binds to a specific port and listens .....
    server->initialize();
    int goodReception;
//    cout << "Connection with " << server->getSocketDescriptor() << " established!" << endl;
    for(int i=0;i<3;++i) {
        ///only now we accept.
        goodReception= server->acceptClient();
        if (goodReception < 0) {
            //return an error represent error at this method
            cout << "Connection not established!" << endl;
        }else {
            pthread_t myThread;
            int *sockID = new int(server->getSocketDescriptor());
            int status = pthread_create(&myThread,NULL,printClientName,(void*)sockID);
            if(status) {
                cout<<"ERROR! ";
            }
            pthread_join(myThread,NULL);
            //cout << "Connection with " << server->getSocketDescriptor() << " established!" << endl;
        }
    }
}

void* clientHandler(void *threadInfo) {

    char buffer[1024];

    //we need to acknowlede taxi center and the port and the socket.(create new class).
    ThreadInfo* p;
    p = (ThreadInfo*) threadInfo;
    MainFlow mainflow = p->getMainFlow();
    Socket* socket = p->getSocket();
    int port = p->getPort();

    //RECEIVE DRIVER AND VEHICLE ID.
    socket->reciveData(buffer, sizeof(buffer));
    string str1(buffer, sizeof(buffer));
    std::string driverInfo;
    boost::iostreams::basic_array_source<char> device1(str1.c_str(), str1.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s1(device1);
    boost::archive::binary_iarchive ia1(s1);
    ia1 >> driverInfo;
    std::cout << "this is a test for receiving driver: "<< std::endl;
    std::cout << "the driver info string is:" <<driverInfo << std::endl;

    //CREATE DRIVER AND ADD IT TO TAXI CENTER - goes to option 5 in main flow menu - add a driver.
    p->getMainFlow().choiceMenu(5,driverInfo);
    driverInfo.clear();

    //SEND TAXI CAB
    BeginningInfoReader beginningInfoReader;
    std::vector<std::string> driverVec;
    driverVec = beginningInfoReader.split(driverInfo);
    BaseCab* cab;
    int driverId;
    std::list<Driver*>::iterator driverIt = p->getMainFlow().getTaxiCenter()->getDriverList()->begin();
    while(driverIt != p->getMainFlow().getTaxiCenter()->getDriverList()->end()){
        if((*(driverIt))->getId() == stoi(driverVec[0])){
            driverId = stoi(driverVec[0]);
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
    socket->sendData(taxiInfoSerialized);

    //INFINIT LOOP CHECKS WHAT THE MAP VALUE OF A SPECIFIC DRIVER ID IS AND TELLS HIM WHAT TO DO.

    int choice = instructionsMap.find(driverId)->second;

    //we will now receive orders as an int continuously until we receive the number 7.
    while (choice!=7){
        ///in case choice is a number from 2-5:
        if((choice > 1) && (choice < 6)){
            std::cin >> choiceInput;
            mainFlow.choiceMenu(choice, choiceInput);
        }

        ///in case choice equals 9: attach trip informartion\movecabs.
        if(choice == 9){

            TripInformation* tripInformation = mainFlow.changeTime();
            //   std::cout << "choice9 the time now is: " << mainFlow.getTaxiCenter()->getTime()<< std::endl;
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
                    //     std::cout << "before move" << p << std::endl;

                    mainFlow.getTaxiCenter()->getTo();
                    mainFlow.getTaxiCenter()->completeTrip();


                    Point p2 = mainFlow.getTaxiCenter()->getTaxiList()->front()->getLocation()->getPoint();
                    //   std::cout << "after move" << p2 << std::endl;

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




















    int sockID = *(int*)clientSocketID;
    cout << "The client " << sockID << " created fine! "<<endl;
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