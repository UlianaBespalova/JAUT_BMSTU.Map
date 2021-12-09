//
// Created by UlianaBespalova on 10.11.2021.
//
#include "mapManager.h"

std::string mockGetMapFromDB(int floorNum = -1) {

    std::cout <<  "floorNum = " << floorNum << std::endl;
    if (floorNum != 8 && floorNum != -1) return "";

    std::ifstream ifs("mockData/8floor.json");
    std::string content ((std::istreambuf_iterator<char>(ifs)),
                         (std::istreambuf_iterator<char>()));
    return content;
}

ResponseString badRequest() {
    const std::string BAD_REQUEST_MSG = R"({ "err": "bad params" })";

    ResponseString response;
    response.body() = BAD_REQUEST_MSG;
    response.set(boost::beast::http::field::content_type, "application/json");
    response.result(boost::beast::http::status::bad_request);
    return response;
}


Params getParams(std::string requestUrl) {
    std::cout << "get = " << requestUrl << std::endl;

    const std::string paramsListDelimiter = "?";
    const std::string paramsDelimiter = "&";
    const std::string valDelimiter = "=";

    Params params = {};
    return params;
}

std::vector<int> getFloorNums(const std::string& floorNumsStr) {
    std::stringstream iss(floorNumsStr);
    int number;
    std::vector<int> floorNums;
    while ( iss >> number )
        floorNums.push_back( number );
    return floorNums;
}

ResponseString MapManager::getMap() {
    std::string mapData = mockGetMapFromDB();
    ResponseString response;
    response.body() = R"({ "mapData": )" + mapData + " }";
    response.set(boost::beast::http::field::content_type, "application/json");
    response.result(boost::beast::http::status::ok);
    return response;
}

ResponseString MapManager::getFloor(Request request) {

    //mock
    if (request.target() != "/floor?floor=8") return badRequest();
    // -> getParams();
    //    std::vector<int> floorNums = getFloorNums(floorReq.floor);

    std::vector<int> floorNums = {8};
    std::string floorData = mockGetMapFromDB(floorNums[0]);

    ResponseString response;
    response.body() = R"({ "floorData": )" + floorData + " }";
    response.set(boost::beast::http::field::content_type, "application/json");
    response.result(boost::beast::http::status::ok);
    return response;
}

