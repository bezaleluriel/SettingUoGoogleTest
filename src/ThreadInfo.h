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
    MainFlow* mainFlow;
    Socket* socket;
    int port;
    int numberOfDrivers;
    std::vector<std::string> addObstacles;
    int socketNumber;

public:
    ThreadInfo();
    ThreadInfo(MainFlow* mainFlow, int port, int numberOfDrivers, std::vector<std::string> addObstacles);
    MainFlow* getMainFlow();
    int getPort();
    Socket* getSocket();
    int getNumberOfDrivers() ;
    void setMainflow( MainFlow* mainflow);
    void setSocket(Socket *socket);
    void setPort(int port);
    void setNumberOfDrivers(int numberOfDrivers);
    vector<string> &getAddObstacles();
    void setAddObstacles(const vector<string> &addObstacles);
    int getSocketNumber() ;
    void setSocketNumber(int socketNumber);
};


#endif //SETTINGUOGOOGLETEST_THREADINFO_H
