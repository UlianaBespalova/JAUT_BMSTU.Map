#include <gtest/gtest.h>

#include "core/database.h"
#include "core/core.hpp"


using namespace Core;

TEST(MapModel, load)
{
    json j = {
            { "rooms", {
                    {
                            { "type", 1 },
                            { "walls", {
                                    {{ "start", { 1, 2 }}, { "end", { 3, 4 }}},
                            }
                            }
                    }
            },
            }
    };
    EXPECT_NO_FATAL_FAILURE(Model::Map model(j));
}

TEST(MapModel, parse_empty)
{
    auto j = R"({})"_json;
    EXPECT_NO_FATAL_FAILURE(Model::Map model(j));
}

TEST(MapModel, parse_full)
{
    auto j = R"(
    {
      "floors": [
        {
          "floor": 5,
          "rooms": [
            {
              "type": 2,
              "walls": [
                { "start": [100, 100], "end": [100, 250] },
                { "start": [100, 250], "end": [700, 250] },
                { "start": [700, 250], "end": [700, 100] },
                { "start": [700, 100], "end": [100, 100] }
              ],
              "properties": {
                "description": "Main hallway"
              }
            },
            {
              "type": 1,
              "walls": [
                { "start": [100, 250], "end": [100, 350] },
                { "start": [100, 350], "end": [200, 350] },
                { "start": [200, 350], "end": [200, 250] },
                { "start": [200, 250], "end": [175, 250] },
                { "start": [175, 250], "end": [125, 250], "type": 2 },
                { "start": [125, 250], "end": [100, 250] }
              ],
              "properties": {
                "description": "W/C",
                "gender": "F"
              }
            }
          ]
        }
      ]
    }
    )"_json;
    Model::Map model(j);

    EXPECT_EQ(model.getRooms().size(), 2);

    Model::Map::Room hallway = model.getRooms()[0];
    EXPECT_EQ(hallway.floor, 5);
    EXPECT_EQ(hallway.type, Model::Map::Room::Type::Corridor);

    EXPECT_FALSE(hallway.properties.find("description") == hallway.properties.end());
    EXPECT_EQ(hallway.properties["description"], "Main hallway");


    Model::Map::Room bathroom = model.getRooms()[1];
    EXPECT_EQ(bathroom.floor, 5);
    EXPECT_EQ(bathroom.type, Model::Map::Room::Type::Cabinet);

    EXPECT_FALSE(bathroom.properties.find("description") == hallway.properties.end());
    EXPECT_EQ(bathroom.properties["description"], "W/C");

    EXPECT_FALSE(bathroom.properties.find("gender") == hallway.properties.end());
    EXPECT_EQ(bathroom.properties["gender"], "F");
}

TEST(insert_and_read_json_test, json_test) {
    auto j = R"(
        {"floors":[{"floor":8,"rooms":[{"type":2,"walls":[{"start":[557,510],"end":[557,733]},{"start":[2981,510],"end":[557,510]},{"start":[2981,733],"end":[2981,510]},{"start":[557,733],"end":[2981,733]}]}]}]}
    )"_json;

    Database json_db(JSON_TABLE_NAME, JSON_TABLE_FORMAT);
    json_db.insert_json(j.dump());
    auto read_json = json::parse(json_db.read_json());

    EXPECT_EQ(j, read_json);
}