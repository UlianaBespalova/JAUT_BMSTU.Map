//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef BASECLIENT_H
#define BASECLIENT_H

class BaseClient {
public:
    BaseClient() = default;
    virtual ~BaseClient() = default;

    virtual void request(std::map<std::string, std::string> data) = 0;

protected:
    virtual void connect(std::map<std::string, std::string> request) = 0;
};

#endif //BASECLIENT_H
