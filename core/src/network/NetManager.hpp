#ifndef BMSTU_MAP_CORE_NETMANAGER_HPP
#define BMSTU_MAP_CORE_NETMANAGER_HPP


namespace Core {
    namespace Network {
        enum RequestMethod { Get, Post, Put, Delete };

        class NetManager {
            public:
                NetManager(std::string url) { }
                ~NetManager() { }

                json bitop_request(RequestMethod method, const std::string &path) { return request(method, path); };
                json map_request() { return request(Get, "/data"); };

            protected:
                json request(RequestMethod method, const std::string &path) { };
        };
    }
}

#endif //BMSTU_MAP_CORE_NETMANAGER_HPP
