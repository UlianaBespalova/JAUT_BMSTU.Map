// Copyright 2021 UlianaBespalova
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <boost/asio.hpp>

#include "httpClient.h"
#include "httpClientConnection.h"
#include "httpServer.h"
#include "httpServerConnection.h"

using namespace boost::asio;

class MockHttpConnection : public HttpServerConnection {
public:
    explicit MockHttpConnection(ip::tcp::socket socket) :
    HttpServerConnection(std::move(socket), nullptr) {};

    MOCK_METHOD(bool, isStart, (), (override));
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(void, doRead, (), (override));
    MOCK_METHOD(void, onRead, (), (override));
    MOCK_METHOD(void, doWrite, (), (override));
    MOCK_METHOD(void, onWrite, (), (override));
};

class MockBitopManager : public BitopManager {
public:
    MockBitopManager() : BitopManager(nullptr, nullptr) {}
    MOCK_METHOD(responseType, getSchedule, (mapType));
};

class MockMapManager : public MapManager {
public:
    MockMapManager() = default;

    MOCK_METHOD(mapType, getMap, ());
    MOCK_METHOD(mapType, getFloor, ());
    MOCK_METHOD(mapType, getShortestPath, (mapType));
};




TEST(serverTest, createConnection) {
    io_service context(1);
    ip::tcp::socket socket(context);
    MockHttpConnection connection(std::move(socket));

    EXPECT_CALL(connection, isStart()).Times(testing::AtLeast(1));
    EXPECT_CALL(connection, start()).Times(testing::AtLeast(1));
    EXPECT_CALL(connection, stop()).Times(testing::AtLeast(1));
    EXPECT_CALL(connection, doRead()).Times(testing::AtLeast(1));
    EXPECT_CALL(connection, doWrite()).Times(testing::AtLeast(1));
    EXPECT_CALL(connection, onRead()).Times(testing::AtLeast(1));
    EXPECT_CALL(connection, onWrite()).Times(testing::AtLeast(1));

    ip::address address;
    unsigned short port = 8000;
    HttpServer server(address, port);
    server.run();
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
