/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** testNibbler
*/

#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include "Error.hpp"
#include "Nibbler.hpp"

TEST(Nibbler, loose) {
    arc::Parser parser("./tests/nibbler_basic.ini");
    arc::Nibbler nibbler(parser.getMap(), parser.getItems());

    nibbler.tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    nibbler.tick();
    ASSERT_EQ(nibbler.getGameState(), arc::LOOSE);
}

TEST(Nibbler, change_direction) {
    arc::Parser parser("./tests/nibbler_basic.ini");
    arc::Nibbler nibbler(parser.getMap(), parser.getItems());

    char **map = nibbler.getMap();

    for (int i = 0; map[i]; i++) {
        printf("%s\n", map[i]);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    nibbler.tick();
    nibbler.execKey(arc::Input::UP);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    nibbler.tick();
    nibbler.execKey(arc::Input::LEFT);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    nibbler.tick();
    nibbler.execKey(arc::Input::DOWN);
    map = nibbler.getMap();
    for (int i = 0; map[i]; i++) {
        printf("%s\n", map[i]);
    }
}

TEST(Nibbler, test_reset) {
    arc::Parser parser("./tests/nibbler_basic.ini");
    arc::Nibbler nibbler(parser.getMap(), parser.getItems());

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    nibbler.tick();
    ASSERT_EQ(nibbler.getGameState(), arc::LOOSE);
    nibbler.reset();
    ASSERT_EQ(nibbler.getGameState(), arc::RUNNING);
}