/*
** EPITECH PROJECT, 202|
** arcade
** File description:
** testParser
*/

#include <gtest/gtest.h>
#include "Parser.hpp"
#include "Error.hpp"

TEST(Parser, parsed_items) {
    arc::Parser parser("./tests/pacman_basic.ini");
    std::vector<arc::item> items = parser.getItems();

    ASSERT_EQ(items.at(0).type, std::string("wall"));
    ASSERT_EQ(items.at(0).sym, '|');
    ASSERT_EQ(items.at(0).path, std::string("wall_file.png"));

    ASSERT_EQ(items.at(1).type, std::string("pacman"));
    ASSERT_EQ(items.at(1).sym, 'P');
    ASSERT_EQ(items.at(1).path, std::string("pacman_file.png"));

    ASSERT_EQ(items.at(2).type, std::string("ghost"));
    ASSERT_EQ(items.at(2).sym, 'M');
    ASSERT_EQ(items.at(2).path, std::string("ghost_file.png"));

    ASSERT_EQ(items.at(3).type, std::string("background"));
    ASSERT_EQ(items.at(3).sym, '.');
    ASSERT_EQ(items.at(3).path, std::string("bg_file.png"));
}

TEST(Parser, parsed_map) {
    arc::Parser parser("./tests/pacman_basic.ini");

    char **map = parser.getMap();
    ASSERT_STREQ(map[0],  (char *)"|||||||||||||||||||||||||");
    ASSERT_STREQ(map[1],  (char *)"|.......................|");
    ASSERT_STREQ(map[2],  (char *)"|.|||||||||||||||||||||.|");
    ASSERT_STREQ(map[3],  (char *)"|.|...................|.|");
    ASSERT_STREQ(map[4],  (char *)"|......|.........|......|");
    ASSERT_STREQ(map[5],  (char *)"|.|....|...MMM...|....|.|");
    ASSERT_STREQ(map[6],  (char *)"|.||||||.........||||||.|");
    ASSERT_STREQ(map[7],  (char *)"|......|.........|......|");
    ASSERT_STREQ(map[8],  (char *)"|.|...................|.|");
    ASSERT_STREQ(map[9],  (char *)"|.|||||||||||||||||||||.|");
    ASSERT_STREQ(map[10], (char *)"|...........P...........|");
    ASSERT_STREQ(map[11], (char *)"|||||||||||||||||||||||||");
}
