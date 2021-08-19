/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** CoreGame
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "Core.hpp"

namespace arc {
void Core::gameLoop(IDisplay *disp) {
    IGame *game = _gameM.get();
    Input input = NONE;
    auto gameIsRunning = [this, disp, game](void) {
        return (this->_isRunning
            && disp == _dispM.get()
            && _scene == GAME
            && game == _gameM.get());
    };

    disp->loadSprites(game->getItems());
    this->mapInputsGame();
    while (gameIsRunning()) {
        input = disp->getInput();
        this->execKeys(input);
        disp->clear();
        if (game->getState() == RUNNING) {
            game->execKey(input);
            game->tick();
            disp->drawMap(game->getMap());
        } else {
            disp->drawText(50, 30, game->getName().c_str());
            disp->drawText(50, 45, game->getState() == WIN ?
                            "You won !" : "You lost !");
            disp->drawText(50, 60, "Press 'R' to reload the game");
            disp->drawText(50, 70, "Press 'T' to return to the menu");
        }
        disp->display();
    }
    if (game->getScore() > this->getHiScore(game->getName()))
        this->saveHiScore(game->getName(), game->getScore());
    disp->destroySprites();
}

size_t Core::getHiScore(const std::string &gameName) const {
    std::string filename = std::string(SCORES_DIR) + gameName + ".score";
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open() || !getline(file, line)) {
        this->saveHiScore(gameName, 0);
        return 0;
    }
    file.close();
    return atoi(line.c_str());
}

void Core::saveHiScore(const std::string &gameName, const size_t score) const {
    std::string filename = std::string(SCORES_DIR) + gameName + ".score";
    std::ofstream file(filename);

    if (!file.is_open())
        throw CoreError("Cannot write to '" + filename + "'");
    file << score;
    file.close();
}

void Core::mapInputsGame(void) {
    _handlers.clear();
    _handlers.emplace(ESCAPE, [this]() { this->_isRunning = false; });
    _handlers.emplace(O, [this]() { _dispM.prev(); });
    _handlers.emplace(P, [this]() { _dispM.next(); });
    _handlers.emplace(L, [this]() { _gameM.prev(); });
    _handlers.emplace(M, [this]() { _gameM.next(); });
    _handlers.emplace(R, [this]() { _gameM.get()->reset();});
    _handlers.emplace(T, [this]() { _scene = MENU; });
}
}  // namespace arc
