//
// Created by UlianaBespalova on 10.11.2021.
//
#include "router.h"


Router::Router(BitopManager *bitopManager, MapManager *mapManager) :
        bitopManager(bitopManager),
        mapManager(mapManager)
{
    std::cout << "router started" << std::endl;
}

ResponseString Router::execute(Request& request) {

    ResponseString response;
    response.result(boost::beast::http::status::not_found);

    if (request.method() == boost::beast::http::verb::get) {
        std::cout << "target = " << request.target() << std::endl;
        if (request.target().rfind("/schedule", 0) == 0) {
            std::cout << "Router: /schedule" << std::endl;
            bitopManager->ivan();
//            response = bitopManager->getSchedule(request);

        } else if (request.target() == "/map") {
            std::cout << "Router: /map" << std::endl;
            response = mapManager->getMap();

        } else if (request.target().rfind("/floor?", 0) == 0) {
            std::cout << "Router: /floor" << std::endl;

            response = mapManager->getFloor(request);
        }
    }
    return response;
}

