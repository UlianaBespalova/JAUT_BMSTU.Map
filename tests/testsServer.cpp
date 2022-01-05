//
// Created by UlianaBespalova on 11.11.2021.
//
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <boost/asio.hpp>

#include "httpServer.h"
#include "httpServerConnection.h"

using asio = boost::asio;

const std::string addressExample = "127.0.0.1";
const int portExample = 8000;


class MockHttpServer : public HttpServer {
public:
    explicit MockHttpServer(std::string& address, int port) :
            HttpServer(address, port) {};

    MOCK_METHOD(void, run, ());
    MOCK_METHOD(void, accept, ());
};

class MockHttpServerConnection : public HttpServerConnection {
public:
    explicit MockHttpServerConnection(ip::tcp::socket socket, Router *router) :
            HttpServerConnection(std::move(socket), router) {};

    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, doRead, (), (override));
    MOCK_METHOD(void, onRead, (), (override));
    MOCK_METHOD(void, doWrite, (), (override));
    MOCK_METHOD(void, onWrite, (), (override));
};

class MockRouter : public Router {
public:
    MockRouter(BitopManager *bitopManager, MapManager *mapManager) :
            Router(bitopManager, mapManager) {}

    MOCK_METHOD(Request, execute, ());
};

class MockBitopManager : public BitopManager {
public:
    MockBitopManager() : BitopManager() {}

    MOCK_METHOD(ResponseString, getSchedule, (Request));
    MOCK_METHOD(ResponseString, getSchedule_test, ());
    MOCK_METHOD(std::string, getScheduleForGroup, (const GroupParams &groupParams));
    MOCK_METHOD(std::string, getItemsByUuid, (const std::string &uid, const std::string &type));
    MOCK_METHOD(std::string, getScheduleByGroupUuid, (const std::string &uid));
};

class MockMapManager : public MapManager {
public:
    MockMapManager() = default;
    MOCK_METHOD(ResponseString, getMap, ());
};


TEST(serverTest, serverRunTest) {
    MockHttpServer server(addressExample, portExample);
    EXPECT_CALL(server, accept()).Times(testing::AtLeast(1));
    server.run();
}

TEST(serverTest, startServerConnectionTest) {
    io_service context(1);
    ip::tcp::socket socket(context);
    MockHttpServerConnection connection(std::move(socket));

    EXPECT_CALL(connection, start()).Times(testing::AtLeast(1));

    HttpServer server(addressExample, portExample);
    server.run();
}

TEST(serverTest, callRouterTest) {
    MockRouter router(nullptr, nullptr);
    EXPECT_CALL(router, execute()).Times(testing::AtLeast(1));

    io_service context(1);
    ip::tcp::socket socket(context);
    MockHttpServerConnection connection(std::move(socket));
    connection.onRead();
}

TEST(routerTest, callBitopManagerTest) {
    MockBitopManager bitopManager;
    Request request;
    EXPECT_CALL(bitopManager, getSchedule(map)).Times(testing::AtLeast(1));
    EXPECT_CALL(bitopManager, getScheduleForGroup(map)).Times(testing::AtLeast(1));

    MockBitopManager *pBitopManager = &bitopManager;
    Router router(pBitopManager, nullptr);
    router.execute(request);
}

TEST(routerTest, getScheduleTest) {
    MockBitopManager bitopManager;
    Request request;
    EXPECT_CALL(bitopManager, getSchedule_test(map)).Times(testing::AtLeast(1));

    MockBitopManager *pBitopManager = &bitopManager;
    Router router(pBitopManager, nullptr);
    router.execute(request);
}

TEST(routerTest, callMapManager) {
    MockMapManager mapManager;
    EXPECT_CALL(mapManager, getMap()).Times(testing::AtLeast(1));

    MockMapManager *pMapManager = &mapManager;
    Router router(nullptr, pMapManager);
    router.execute(request);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
