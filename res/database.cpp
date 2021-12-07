#include "database.h"

Database::Database() {
    stringstream ss;
    ss << "dbname = " << dbname << " user = " << user << " password = "
       << password << " hostaddr = " << host_address << " port = " << port;

    cout << ss.str() << endl;

    connection Connection(ss.str().c_str());

    if (Connection.is_open()) {
        cout << "OK" << endl;
    }

    create_table();
}

void Database::create_table() {
    stringstream ss;
    ss << "CREATE TABLE IF NOT EXISTS " << table_name << "(" << table_format << ");";

    work W(Connection);
    W.exec(ss.str().c_str());
    W.commit();
    Connection.disconnect();
}

void Database::insert_table(const string& values) {
    stringstream ss;
    ss << "INSERT INTO " << table_name << " VALUES (" << values << ");";

    work W(Connection);
    W.exec(ss.str().c_str());
    W.commit();
    Connection.disconnect();
}


void Database::read_table(vector<Neighbour>& data) {
    stringstream ss;
    ss << "SELECT * from " << table_name;

    work N(Connection);
    result R(N.exec(ss.str().c_str()));

    cout << "Rows num:" << R.size() << endl;
    data.reserve(R.size());

    for (auto const &row: R) {

        Neighbour buffer;
        cout << "ID: " << row[0].as<int>() << endl;
        buffer.id = row[0].as<int>();

        auto arr = row[1].as_array();
        pair<pqxx::array_parser::juncture, string> elem;
        elem = arr.get_next();

        while (elem.first != pqxx::array_parser::juncture::null_value && elem.first != pqxx::array_parser::juncture::done) {

            int neighbour, duration;

            if (elem.first == pqxx::array_parser::juncture::string_value) {
                neighbour = stoi(elem.second);
            } else {
                elem = arr.get_next();
                continue;
            }

            elem = arr.get_next();

            if (elem.first == pqxx::array_parser::juncture::string_value) {
                duration = stoi(elem.second);
                cout << neighbour << " " << duration << endl;
                buffer.edge.push_back(make_pair(neighbour, duration));
            }


            //elem = arr.get_next();
        }

        data.push_back(buffer);
    }
}

