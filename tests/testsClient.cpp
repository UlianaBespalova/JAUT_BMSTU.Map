// Copyright 2021 UlianaBespalova
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <boost/asio.hpp>

#include "httpClient.h"

const std::string domainExample;
const std::string ipExample = "152.70.54.11";
const unsigned short portExample = 8000;
const std::string targetExample = "/data";

const Params paramsExample = {{"param1", "p1"}, {"param2", "p2"}};
const Params bodyExample = {{"uid", "048383928392663664676127368764662736467"}};

TEST(clientTest, getUrlTest) {
    std::string url = HttpsClient::getUrl(targetExample, paramsExample);
    EXPECT_EQ(url, "data?param1=p1&param2=p2");
}

TEST(clientTest, makeHttpGetRequestTest) {
    HttpClient client;
    Response result = client.makeGetRequest(
            HostAddress(domainExample, ipExample, portExample), targetExample);
    EXPECT_EQ(result.result_int(), 200);
}

TEST(clientTest, makeHttpGetRequestNegativeTest) {
    const std::string ipWrong = "162.70.54.11";

    HttpClient client;
    Response result = client.makeGetRequest(
            HostAddress(domainExample, ipWrong, portExample), targetExample);
    EXPECT_EQ(result.result_int(), 404);
}

TEST(clientTest, makeHttpGetRequestWithParamsTest) {
    HttpClient client;
    Response result = client.makeGetRequest(
            HostAddress(domainExample, ipExample, portExample),
            targetExample, paramsExample);
    EXPECT_EQ(result.result_int(), 200);
}

TEST(clientTest, makeHttpPostRequestTest) {
    HttpClient client;
    Response result = client.makePostRequest(
            HostAddress(domainExample, ipExample, portExample), targetExample,
            nullptr, nullptr, bodyExample);
    EXPECT_EQ(result.result_int(), 200);
}

TEST(clientTest, parseResponseTest) {
    HttpClient client;
    Response result = client.makeGetRequest(
            HostAddress(domainExample, ipExample, portExample), targetExample);
    ResponseStruct resultStruct = client.parseResponse(result);

    const std::string trueResultBody = "{\n"
                                       "    \"floors\": [\n"
                                       "        {\n"
                                       "            \"floor\": 8,\n"
                                       "            \"rooms\": [\n"
                                       "                {\n"
                                       "                    \"type\": 2,\n"
                                       "                    \"walls\": [\n"
                                       "                        { \"start\": [ 557, 510], \"end\": [ 557, 733] },\n"
                                       "                        { \"start\": [ 2981, 510], \"end\": [ 557, 510] },\n"
                                       "                        { \"start\": [ 2981, 733], \"end\": [ 2981, 510] },\n"
                                       "                        { \"start\": [ 557, 733], \"end\": [ 2981, 733] }\n"
                                       "                    ]\n"
                                       "                },]}";
    EXPECT_EQ(resultStruct.status, 200);
    EXPECT_EQ(resultStruct.body, trueResultBody);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
