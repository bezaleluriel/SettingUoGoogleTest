#include <iostream>
#include "src/sockets/Socket.h"
#include "src/sockets/Tcp.h"

int main(int argc, char *argv[])  {
    Socket* client = new Tcp(0, atoi(argv[1]));
    client->initialize();

    //Receive the driver details .

    //create the driver(Object).

    //serialize and send  the driver to the server

    //receive taxi cab.

    //

}