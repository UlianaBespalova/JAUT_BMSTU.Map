//
// Created by UlianaBespalova on 1.12.2021.
//
#include <iostream>

#include "httpClient.h"

int main() {

    Params params = {{"floor", "all"}, {"ivan", "example"}};
    auto *client = new HttpClient();

//    Get-запрос без параметров
    Response result = client -> makeGetRequest("152.70.54.11", 8000, "/data");
    std::cout << result << std::endl << std::endl << std::endl;

//    Get-запрос с параметрами
    result = client -> makeGetRequest("152.70.54.11", 8000, "/data", &params);

    ResponseStruct resultStruct = HttpClient::parseResponse(result);
    std::cout << resultStruct.status << std::endl;
    std::cout << resultStruct.body << std::endl;

    delete client;
    return 0;
}