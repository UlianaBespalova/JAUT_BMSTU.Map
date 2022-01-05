//
// Created by UlianaBespalova on 10.11.2021.
//
#include "router.h"

Router::Router(BitopManager *bitopManager, MapManager *mapManager)
        : bitopManager(bitopManager), mapManager(mapManager) {
    std::cout << "router started" << std::endl;
}

ResponseString Router::execute(Request &request) {
    ResponseString response;
    response.result(boost::beast::http::status::not_found);

    std::cout << "target = " << request.target() << std::endl;
    switch (request.method()) {
        case boost::beast::http::verb::post: {
            if (request.target().rfind(schedulePath, 0) == 0) {
                std::cout << "Router: /schedule" << std::endl;
                response = bitopManager->getSchedule(request);
            }
            break;
        }
        case boost::beast::http::verb::get: {
            if (request.target() == mapPath) {
                std::cout << "Router: /map" << std::endl;
                response = mapManager->getMap();

            }
                // Get-версия запроса для удобной проверки
            else if (request.target() == scheduleTestPath) {
                std::cout << "Router: /schedule_test" << std::endl;
                response = bitopManager->getSchedule_test();
            }
            break;
        }
        default:
            break;
    }
    return response;
}
