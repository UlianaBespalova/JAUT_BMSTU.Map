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

const string JSON_TABLE_NAME = "json_table";
const string JSON_TABLE_FORMAT = "doc jsonb NOT NULL";

class Database {
public:
    Database();

    Database(const string& t_name, const string& t_format);

    ~Database();

    void create_table();

    void insert_table(const string& values);

    void read_table(vector<Neighbour>& data);

    string read_json();

    void insert_json(const string& json_str);
private:

    string dbname = "ruslan16";
    string user = "ruslan16";
    string password = "ruslan16";
    string host_address = "127.0.0.1";
    string port = "5432";
    string table_name = "testdb";
    string table_format = "id integer PRIMARY KEY, neighbours integer[][]";

    connection Connection;
};