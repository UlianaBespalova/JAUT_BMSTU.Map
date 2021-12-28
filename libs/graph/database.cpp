#include "database.h"

Database::Database() {
    get_config();
    std::string comand = "dbname = " + dbname + " user = " + user +
                         " password = " + password +
                         " hostaddr = " + host_address + " port = " + port;

    pqxx::connection Connection(comand.c_str());

    create_table();
}

Database::~Database() { Connection.disconnect(); }

Database::Database(const std::string &t_name, const std::string &t_format)
        : table_name(t_name), table_format(t_format) {
    get_config();
    std::string comand = "dbname = " + dbname + " user = " + user +
                         " password = " + password +
                         " hostaddr = " + host_address + " port = " + port;

    pqxx::connection Connection(comand.c_str());

    create_table();
}

void Database::create_table() {
    std::string comand =
            "CREATE TABLE IF NOT EXISTS " + table_name + "(" + table_format + ");";

    pqxx::work W(Connection);
    W.exec(comand.c_str());
    W.commit();
}

void Database::insert_table(const std::string &values) {
    std::string comand = "INSERT INTO " + table_name +
                         "(ID, neighbours) VALUES (" + values + ") " +
                         "ON CONFLICT (ID) DO UPDATE SET " +
                         "neighbours=EXCLUDED.neighbours;";

    pqxx::work W(Connection);
    W.exec(comand.c_str());
    W.commit();
}

void Database::read_table(std::vector<Neighbour> &data) {
    std::string comand = "SELECT * from " + table_name;

    pqxx::work N(Connection);
    pqxx::result R(N.exec(comand.c_str()));

    data.reserve(R.size());

    for (auto const &row : R) {
        Neighbour buffer;
        buffer.id = row[0].as<int>();

        auto arr = row[1].as_array();
        std::pair<pqxx::array_parser::juncture, std::string> elem;
        elem = arr.get_next();

        while (elem.first != pqxx::array_parser::juncture::null_value &&
               elem.first != pqxx::array_parser::juncture::done) {
            if (elem.first == pqxx::array_parser::juncture::string_value) {
                int neighbour = std::stoi(elem.second);
                elem = arr.get_next();
                if (elem.first == pqxx::array_parser::juncture::string_value) {
                    int duration = std::stoi(elem.second);
                    buffer.edge.push_back(std::make_pair(neighbour, duration));
                }
            }
            elem = arr.get_next();
        }
        data.push_back(buffer);
    }
}

void Database::insert_json(const std::string &json_str) {
    std::string comand = "INSERT INTO " + table_name + "(doc) VALUES ('" +
                         json_str + "') " + "ON CONFLICT (doc) DO UPDATE SET " +
                         "doc=EXCLUDED.doc;";

    pqxx::work W(Connection);
    W.exec(comand.c_str());
    W.commit();
}

std::string Database::read_json() {
    std::string comand = "SELECT * from " + table_name;

    pqxx::work N(Connection);
    pqxx::result R(N.exec(comand.c_str()));

    return R[0][0].c_str();
}

void Database::get_config() {
    std::ifstream config_file("config.txt");

    if (!config_file.is_open()) {
        std::cout << "ERROR" << std::endl;
        return;
    }

    std::string buffer;

    std::getline(config_file, buffer, '=');
    std::getline(config_file, dbname, '\n');
    std::getline(config_file, buffer, '=');
    std::getline(config_file, user, '\n');
    std::getline(config_file, buffer, '=');
    std::getline(config_file, password, '\n');
    std::getline(config_file, buffer, '=');
    std::getline(config_file, host_address, '\n');
    std::getline(config_file, buffer, '=');
    std::getline(config_file, port, '\n');

    config_file.close();
    return;
}
