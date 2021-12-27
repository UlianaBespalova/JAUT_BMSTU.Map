#pragma once
#include <fstream>
#include <iostream>
#include <pqxx/pqxx>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "neighbour.h"

const std::string JSON_TABLE_NAME = "json_table";
const std::string JSON_TABLE_FORMAT = "id integer PRIMARY KEY NOT NULL, doc jsonb";

const std::string GRAPH_TABLE_NAME = "testdb";
const std::string GRAPH_TABLE_FORMAT =
        "id integer PRIMARY KEY, neighbours integer[][]";

class Database {
public:
    Database();

    Database(const std::string& t_name, const std::string& t_format);

    ~Database();

    void create_table();

    void insert_table(const std::string& values);

    void read_table(std::vector<Neighbour>& data);

    std::string read_json();

    void insert_json(const std::string& json_str);

private:
    void get_config();

    std::string dbname;
    std::string user;
    std::string password;
    std::string host_address;
    std::string port;
    std::string table_name;
    std::string table_format;

    pqxx::connection Connection;
};