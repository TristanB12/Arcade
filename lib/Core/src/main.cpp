/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** main
*/

#include <iostream>
#include <memory>
#include "Core.hpp"
#include "Error.hpp"

int main(int ac, char **av) {
    std::unique_ptr<arc::Core> core = nullptr;

    if (ac != 2) {
        std::cerr << USAGE << std::endl;
        return MY_EXIT_FAILURE;
    } else if (ac == 2 && std::string(av[1]) == "-h") {
        std::cout << USAGE << std::endl << KEYS_USAGE << std::endl;
        return 0;
    }
    try {
        core = std::unique_ptr<arc::Core>(new arc::Core(av[1]));
        core->run();
    } catch (const arc::Error &err) {
        std::cerr << err.what() << std::endl;
        return MY_EXIT_FAILURE;
    }
    return 0;
}
