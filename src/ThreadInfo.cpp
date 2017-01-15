//
// Created by matan on 13/01/17.
//

#include "ThreadInfo.h"

ThreadInfo::ThreadInfo() {}

ThreadInfo::ThreadInfo(MainFlow *mainFlow, int port, int numberOfDrivers, std::vector<std::string> addObstacles) {
    ThreadInfo::addObstacles = addObstacles;
    ThreadInfo::mainFlow = mainFlow;
    ThreadInfo::port = port;
    ThreadInfo::numberOfDrivers = numberOfDrivers;
}

MainFlow* ThreadInfo::getMainFlow() {
    return mainFlow;
}

int ThreadInfo::getPort() {
    return port;
}

Socket* ThreadInfo::getSocket() {
    return socket;
}

int ThreadInfo::getNumberOfDrivers()  {
    return numberOfDrivers;
}

void ThreadInfo::setMainflow( MainFlow* mainflow) {
    ThreadInfo::mainFlow = mainflow;
}

void ThreadInfo::setSocket(Socket *socket) {
    ThreadInfo::socket = socket;
}

void ThreadInfo::setPort(int port) {
    ThreadInfo::port = port;
}

void ThreadInfo::setNumberOfDrivers(int numberOfDrivers) {
    ThreadInfo::numberOfDrivers = numberOfDrivers;
}

vector<string> &ThreadInfo::getAddObstacles()  {
    return addObstacles;
}

void ThreadInfo::setAddObstacles(const vector<string> &addObstacles) {
    ThreadInfo::addObstacles = addObstacles;
}


