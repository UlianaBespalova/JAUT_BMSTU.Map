//
// Created by UlianaBespalova on 1.12.2021.
//

#include <iostream>

#include "httpClient.h"

int main() {
    const std::string domainExample;
    const std::string ipExample = "152.70.54.11";
    const unsigned short portExample = 8000;
    const std::string targetExample = "/data";

    auto *client = new HttpsClient();

    //  Пример использования: Get-запрос без параметров
    Response result = client->makeGetRequest(
            HostAddress(domainExample, ipExample, portExample), targetExample);

    ResponseStruct resultStruct = client->parseResponse(result);
    std::cout << resultStruct.status << std::endl;
    std::cout << resultStruct.body << std::endl;

    delete client;
    return 0;
}
