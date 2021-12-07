#include <iostream>

#include "httpServer.h"
#include "httpServerConnection.h"

int main() {

    helloServer();
    helloServerConn();
    std::cout << "Hello httpServer!" << std::endl;
    return 0;
}
