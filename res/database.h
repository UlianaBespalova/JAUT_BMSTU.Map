#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <pqxx/pqxx>

#include "neighbour.h"

using namespace std;
using namespace pqxx;

class Database {
public:
    Database();

    void create_table();

    void insert_table(const string& values);

    void read_table(vector<Neighbour>& data);

    void read_json(const string& json_str);

    void insert(string& json_str);
private:
    bool connect_db();

    string dbname = "ruslan16";
    string user = "ruslan16";
    string password = "ruslan16";
    string host_address = "127.0.0.1";
    string port = "5432";
    string table_name = "testdb";
    string table_format = "id integer PRIMARY KEY, neighbours integer[][]";

    bool is_connected = false;

    connection Connection;
};