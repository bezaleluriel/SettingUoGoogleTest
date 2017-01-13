//
// Created by amir on 09/01/17.
//
#include <iostream>
#include "pthread.h"
#include "unistd.h"
#include "src/sockets/Socket.h"
#include "src/sockets/Tcp.h"
#include <netinet/in.h>
//declerations:

//declerations:

void* getNewClients(void* port);
void* printClientName(void *clientSocketID);


int main(int argc,char* argv[]) {
    pthread_t t1;

    int* port = new int(atoi(argv[1]));
    int status = pthread_create(&t1,NULL,getNewClients,(void*)port);
    pthread_join(t1,NULL);

    ////create global map

}


//Main thread for receiving new client connections.
void* getNewClients(void* port) {
    Socket *server = new Tcp(1, *(int*)port);
    server->initialize();
    int goodReception;
//    cout << "Connection with " << server->getSocketDescriptor() << " established!" << endl;
    for(int i=0;i<3;++i) {
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

void* clientHandler(void *clientSocketID) {
    //we need to acknowlede taxi center and the port and the socket.(create new class).

    //RECEIVE DRIVER

    //RECEIVE VEHICLE ID

    //CREATE DRIVER AND ADD IT TO TAXI CENTER

    //SEND TAXI CAB

    //inifinite loop checkswhat the map value of a specific id driver is and tells him what to do.

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