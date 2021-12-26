//
// Created by UlianaBespalova on 10.11.2021.
//
#include "mapManager.h"

ResponseString getBadMapRequest() {
    const std::string BAD_REQUEST_MSG = R"({ "error": "bad params" })";

    ResponseString response;
    response.body() = BAD_REQUEST_MSG;
    response.set(boost::beast::http::field::content_type, "application/json");
    response.result(boost::beast::http::status::bad_request);
    return response;
}

ResponseString MapManager::getMap() const {
    std::string mapData = database->read_json();
    if (mapData.empty()) return getBadMapRequest();

    ResponseString response;
    response.body() = mapData;
    response.set(boost::beast::http::field::content_type, "application/json");
    response.result(boost::beast::http::status::ok);
    return response;
}
