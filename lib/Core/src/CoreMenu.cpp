/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** CoreMenu
*/

#include <iostream>
#include "Core.hpp"

namespace arc {
Core::Menu::Menu(Core &core) : _core(core) {
    _section = GAME;
    _gameIdx = 0;
    _dispIdx = 0;
}

void Core::Menu::loop(IDisplay *disp) {
    Input input = NONE;
    auto menuIsRunning = [this, disp] (void) {
        return (_core._isRunning
            && disp == _core._dispM.get()
            && _core._scene == MENU);
    };

    while (menuIsRunning()) {
        this->mapInputs();
        input = disp->getInput();
        if (_section == YOUR_NAME)
            this->handleEnteredText(input);
        _core.execKeys(input);
        disp->clear();
        this->draw(disp);
        disp->display();
    }
}

void Core::Menu::handleEnteredText(const Input input) {
    if (input == BACKSPACE && _playerName.size() != 0)
        _playerName = _playerName.substr(0, _playerName.size() - 1);
    else if (input >= 'A' && input <= 'Z' && _playerName.size() < 3)
        _playerName.push_back(static_cast<char>(input));
}

void Core::Menu::draw(IDisplay *disp) const {
    std::vector<std::string> dispLibNames = _core._dispM.getLibNames();
    std::vector<std::string> gameLibNames = _core._gameM.getLibNames();

    // Your name box
    disp->drawBox(10, 25, 80, 10);
    // Displays box
    disp->drawBox(10, 45, 30, 50);
    // Scores box
    disp->drawBox(70, 45, 20, 50);
    // Games Box
    disp->drawBox(40, 45, 30, 50);
    disp->drawText(50, 10, "Arcade");
    disp->drawText(50, 20, "Your name");
    disp->drawText(25, 40, "Displays");
    disp->drawText(55, 40, "Games");
    disp->drawText(80, 40, "Scores");

    disp->drawText(50, 29, _playerName.c_str());

    for (size_t i = 0 ; i < dispLibNames.size() ; i++) {
        if (_section == DISPLAY && _dispIdx == i)
            disp->drawBox(10, 45 + i * 10, 30, 10);
        disp->drawText(25, 50 + i * 10, dispLibNames[i].c_str());
    }
    for (size_t i = 0 ; i < gameLibNames.size() ; i++) {
        if (_section == GAME && _gameIdx == i)
            disp->drawBox(40, 45 + i * 10, 30, 10);
        disp->drawText(55, 50 + i * 10, gameLibNames[i].c_str());
        disp->drawText(80, 50 + i * 10,
            std::to_string(_core.getHiScore(gameLibNames[i])).c_str());
    }
}

void Core::Menu::mapInputs(void) {
    _core._handlers.clear();
    _core._handlers.emplace(ESCAPE, [this]() {
        _core._isRunning = false;
    });
    _core._handlers.emplace(TAB, [this] {
        if (_section == GAME)
            _section = YOUR_NAME;
        else
            _section = static_cast<Section>(_section + 1);
    });
    if (_section != YOUR_NAME) {
        _core._handlers.emplace(ENTER, [this]() {
            if (_section == GAME) {
                _core._gameM.set(_core._gameM.getLibNames()[_gameIdx]);
                _core._scene = Core::Scene::GAME;
            } else if (_section == DISPLAY) {
                _core._dispM.set(_core._dispM.getLibNames()[_dispIdx]);
            }
        });
        _core._handlers.emplace(UP, [this]() {
            if (_section == GAME) {
                if (_gameIdx == 0)
                    _gameIdx = _core._gameM.size() - 1;
                else
                    _gameIdx--;
            } else if (_section == DISPLAY) {
                if (_dispIdx == 0)
                    _dispIdx = _core._dispM.size() - 1;
                else
                    _dispIdx--;
            }
        });
        _core._handlers.emplace(DOWN, [this]() {
            if (_section == GAME) {
                _gameIdx++;
                if (_gameIdx >= _core._gameM.size())
                    _gameIdx = 0;
            } else if (_section == DISPLAY) {
                _dispIdx++;
                if (_dispIdx >= _core._dispM.size())
                    _dispIdx = 0;
            }
        });
    }
}
}  // namespace arc
