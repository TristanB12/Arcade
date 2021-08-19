/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** testDLManager
*/

#include <gtest/gtest.h>
#include "DLManager.hpp"
#include "IDisplay.hpp"
#include "Error.hpp"

TEST(DLManager, ctor) {
    std::vector<std::string> libNames = { "sdl2" };
    arc::DLManager<arc::IDisplay> dlManager(libNames);

    dlManager.get();
}
