//
// Created by matan on 13/01/17.
//

#ifndef SETTINGUOGOOGLETEST_THREADINFO_H
#define SETTINGUOGOOGLETEST_THREADINFO_H


#include "TaxiCenter.h"
#include "sockets/Socket.h"
#include "MainFlow.h"

class ThreadInfo {
private:
    MainFlow mainflow;
    int port;
    Socket* socket;

public:
    ThreadInfo(MainFlow mainflow, int port, Socket* socket);
    MainFlow &getMainFlow();
    int getPort();
    Socket* getSocket();
};


#endif //SETTINGUOGOOGLETEST_THREADINFO_H
