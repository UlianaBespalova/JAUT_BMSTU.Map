#include <iostream>

#include "httpServer.h"

int main() {
    helloServer();
    helloServerConn();
    std::cout << "Hello httpServer!" << std::endl;
    return 0;
}
