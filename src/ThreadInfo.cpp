//
// Created by matan on 13/01/17.
//

#include "ThreadInfo.h"

ThreadInfo::ThreadInfo(MainFlow mainFlow, int port, Socket* socket) {
    ThreadInfo::mainflow = mainflow;
    ThreadInfo::port = port;
    ThreadInfo::socket = socket;
}

MainFlow &ThreadInfo::getMainFlow() {
    return mainflow;
}

int ThreadInfo::getPort() {
    return port;
}

Socket* ThreadInfo::getSocket() {
    return socket;
}
