#include <iostream>

#include "httpServer/httpServer.h"
#include "httpServer/httpServerConnection.h"

int main() {
    helloServer();
    helloServerConn();
    std::cout << "Hello httpServer!" << std::endl;
    return 0;
}
