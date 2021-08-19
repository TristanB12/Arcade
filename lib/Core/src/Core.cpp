/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** Core
*/

#include <thread>
#include <chrono>
#include "Core.hpp"

namespace arc {
Core::Core(const std::string &filename) : _menu(*this) {
    std::unique_ptr<DispLoader> selectedDisplay =
        std::unique_ptr<DispLoader>(new DispLoader(filename));

    _isRunning = false;
    _scene = MENU;
    _dispM.loadLibs();
    _gameM.loadLibs();
    _dispM.set(selectedDisplay.get()->get()->getName());
}

void Core::run(void) {
    _isRunning = true;
    while (this->_isRunning)
        dispLoop();
}

void Core::dispLoop(void) {
    IDisplay *disp = _dispM.get();
    auto dispIsRunning = [this, disp] (void) {
        return (this->_isRunning && disp == _dispM.get());
    };

    disp->createWindow();
    while (dispIsRunning()) {
        if (_scene == MENU)
            _menu.loop(disp);
        else if (_scene == GAME)
            gameLoop(disp);
    }
    disp->destroyWindow();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Core::execKeys(const Input input) {
    try {
        _handlers[input]();
    } catch (const std::bad_function_call &_) {}
}
}  // namespace arc
