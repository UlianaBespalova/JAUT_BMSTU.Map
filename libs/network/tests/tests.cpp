// Copyright 2021 UlianaBespalova
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <boost/asio.hpp>

#include "network/httpClient.h"
#include "network/httpServer.h"
#include "network/httpServerConnection.h"

using namespace boost::asio;

class MockHttpClientConnection : public HttpClientConnection {
public:
    explicit MockHttpClientConnection(ip::tcp::socket socket, mapType map) :
            HttpClientConnection(std::move(socket), map) {};

    MOCK_METHOD(bool, isStart, (), (override));
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, doRead, (), (override));
    MOCK_METHOD(void, onRead, (), (override));
    MOCK_METHOD(void, doWrite, (), (override));
    MOCK_METHOD(void, onWrite, (), (override));
};

class MockHttpClient : public HttpClient {
public:
    explicit MockHttpClient(std::string &address, unsigned short port) :
            HttpClient(address, port) {};

    MOCK_METHOD(void, request, (mapType));
    MOCK_METHOD(void, connect, (mapType));
    MOCK_METHOD(Response, getResponse, ());
};

class MockHttpServerConnection : public HttpServerConnection {
public:
    explicit MockHttpServerConnection(ip::tcp::socket socket) :
            HttpServerConnection(std::move(socket), nullptr) {};

    MOCK_METHOD(bool, isStart, (), (override));
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, doRead, (), (override));
    MOCK_METHOD(void, onRead, (), (override));
    MOCK_METHOD(void, doWrite, (), (override));
    MOCK_METHOD(void, onWrite, (), (override));
};

class MockHttpServer : public HttpServer {
public:
    explicit MockHttpServer(ip::address &address, unsigned short port) :
            HttpServer(address, port) {};

    MOCK_METHOD(void, run, ());
    MOCK_METHOD(void, accept, ());
};

class MockRouter : public Router {
public:
    MockRouter(BitopManager *bitopManager, MapManager *mapManager) :
    Router(bitopManager, mapManager) {}

    MOCK_METHOD(Request, execute, ());
};

class MockBitopManager : public BitopManager {
public:
    MockBitopManager() : BitopManager(nullptr, nullptr) {}
    MOCK_METHOD(Response, getSchedule, (mapType));
};

class MockMapManager : public MapManager {
public:
    MockMapManager() = default;

    MOCK_METHOD(mapType, getMap, ());
    MOCK_METHOD(mapType, getFloor, ());
    MOCK_METHOD(mapType, getShortestPath, (mapType));
};


TEST(clientTest, startClientConnection) {
    io_service context(1);
    ip::tcp::socket socket(context);
    mapType map;
    MockHttpClientConnection connection(std::move(socket), map);

    std::string address = "http://152.70.54.11";
    unsigned short port = 8000;
    MockHttpClient client(address, port);

    EXPECT_CALL(connection, isStart()).Times(testing::AtLeast(1));
    EXPECT_CALL(connection, start()).Times(testing::AtLeast(1));

    mapType req;
    client.connect(req);
}

TEST(clientTest, clientRequest) {
    io_service context(1);
    std::string address = "http://152.70.54.11";
    unsigned short port = 8000;
    MockHttpClient client(address, port);
    mapType map;

    EXPECT_CALL(client, connect(map)).Times(testing::AtLeast(1));
    client.request(map);
}

TEST(clientTest, getResponse) {
    io_service context(1);
    ip::tcp::socket socket(context);
    mapType map;
    MockHttpClientConnection connection(std::move(socket), map);

    std::string address = "http://152.70.54.11";
    unsigned short port = 8000;
    MockHttpClient client(address, port);

    EXPECT_CALL(connection, onRead()).Times(testing::AtLeast(1));
    client.getResponse();
}

TEST(serverTest, startServerConnection) {
    io_service context(1);
    ip::tcp::socket socket(context);
    MockHttpServerConnection connection(std::move(socket));

    EXPECT_CALL(connection, isStart()).Times(testing::AtLeast(1));
    EXPECT_CALL(connection, start()).Times(testing::AtLeast(1));

    ip::address address;
    unsigned short port = 8000;
    HttpServer server(address, port);
    server.run();
}

TEST(serverTest, serverRun) {
    ip::address address;
    unsigned short port = 8000;
    MockHttpServer server(address, port);

    EXPECT_CALL(server, accept()).Times(testing::AtLeast(1));
    server.run();
}

TEST(serverTest, callRouter) {
    MockRouter router(nullptr, nullptr);
    EXPECT_CALL(router, execute()).Times(testing::AtLeast(1));

    io_service context(1);
    ip::tcp::socket socket(context);
    MockHttpServerConnection connection(std::move(socket));
    connection.onRead();
}

TEST(routerTest, callBitopManager) {
    MockBitopManager bitopManager;
    mapType map;

    EXPECT_CALL(bitopManager, getSchedule(map)).Times(testing::AtLeast(1));

    MockBitopManager *pBitopManager = &bitopManager;
    Router router(pBitopManager, nullptr);
    Request request; //request: /getSchedule
    router.execute(request);
}

TEST(routerTest, callMapManager) {
    MockMapManager mapManager;
    EXPECT_CALL(mapManager, getMap()).Times(testing::AtLeast(1));

    MockMapManager *pMapManager = &mapManager;
    Router router(nullptr, pMapManager);
Request request; //request: /getMap
    router.execute(request);
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
