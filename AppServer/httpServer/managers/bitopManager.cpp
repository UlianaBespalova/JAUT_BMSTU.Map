//
// Created by UlianaBespalova on 10.11.2021.
//
#include <fstream>
#include "bitopManager.h"

std::string getBitopToken() {
    std::ifstream ifs("../../../token.txt");
    std::string token ((std::istreambuf_iterator<char>(ifs)),
                         (std::istreambuf_iterator<char>()));
    return token;
}

ResponseString BitopManager::getSchedule(Request request) {
    ResponseString response;
    std::string mock = "mock mock";
    response.body() = R"({ "floorData": )" + mock + " }";
    response.set(boost::beast::http::field::content_type, "application/json");
    response.result(boost::beast::http::status::ok);
    return response;
}

std::string BitopManager::uploadData() {
    const std::string domain = "api.bitop.bmstu.ru";
    const std::string ip = "195.19.40.96";
    std::string uidExample = "ee6dd945-5ee2-4828-aed4-8aaf2a5af5d7";

    auto *client = new HttpsClient();

    Response result = client -> makeGetRequest(domain, ip, 443, "/schedule/"+uidExample);
    delete client;
    return HttpClient().parseResponse(result);
}

