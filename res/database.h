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

    Database(const string& t_name, const string& t_format);

    void create_table();

    void insert_table(const string& values);

    void read_table(vector<Neighbour>& data);

    void read_json(string& json_str);

    void insert_json(const string& json_str);

    const string JSON_TABLE_NAME = "json_table";
    const string JSON_TABLE_FORMAT = "doc jsonb NOT NULL";
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