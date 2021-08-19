/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Paman
*/


#include <chrono>
#include <iostream>
#include <cstring>
#include "Pacman.hpp"
#include "Parser.hpp"

namespace arc {
Pacman::Pacman(void) {
    Parser parser("./conf/pacman.ini");

    this->init(parser.getMap(), parser.getItems());
}

Pacman::Pacman(char **map, std::vector<item> items) {
    this->init(map, items);
}

void Pacman::init(char **map, std::vector<item> items) {
    int sizeofmap = 0;
    int i = 0;

    this->_map = map;
    this->_tempItems = items;
    this->_tempMap = map;
    for (sizeofmap = 0; map[sizeofmap]; sizeofmap++);
    _tempMap = reinterpret_cast<char**>(malloc(sizeof(char *) * (sizeofmap + 1)));
    for (i = 0; map[i]; i++)
        _tempMap[i] = strdup(map[i]);
    _tempMap[i++] = NULL;
    this->_direction = RIGHT;
    this->_state = RUNNING;
    this->_score = 0;
    for (auto item : items) {
        if (item.type == std::string("wall"))
            _wallSym = item.sym;
        if (item.type == std::string("pacman"))
            _pacmanSym = item.sym;
        if (item.type == std::string("background"))
            _bgSym = item.sym;
        if (item.type == std::string("ghost"))
            _ghostSym = item.sym;
        if (item.type == std::string("egg"))
            _eggSym = item.sym;
    }
    for (int y = 0; map[y]; y++) {
        for (int x = 0; map[y][x]; x++) {
            if (map[y][x] == this->_pacmanSym)
                this->_pacman = {x, y};
            if (map[y][x] ==  this->_ghostSym)
                this->_ghosts.push_back({{x, y}, LEFT, _eggSym});
        }
    }
    _ghosts[1].direction =  DOWN;
    _ghosts[2].direction = RIGHT;
}

Pacman::pos Pacman::getVectFromDirection(Input direction) {
    if (direction == LEFT)
        return {-1, 0};
    if (direction == RIGHT)
        return {1, 0};
    if (direction == UP)
        return {0, -1};
    return {0, 1};
}

void Pacman::execKey(Input key) {
    pos vect;

    if (key != DOWN && key != UP && key != LEFT && key != RIGHT)
        return;
    if (key == this->_direction)
        return;
    vect = this->getVectFromDirection(key);
    if (_map[_pacman.y + vect.y][_pacman.x + vect.x] == _wallSym)
        return;
    this->_direction = key;
}

void Pacman::tick(void) {
    static auto lastCall = std::chrono::high_resolution_clock::now();
    auto  now = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCall);

    if (duration <= std::chrono::milliseconds{500} || _state == LOOSE)
        return;
    this->movePacman();
    this->moveGhosts();
    lastCall = std::chrono::high_resolution_clock::now();
}

void Pacman::movePacman(void) {
    Pacman::pos vect = this->getVectFromDirection(this->_direction);

    if (_map[_pacman.y + vect.y][_pacman.x + vect.x] == _ghostSym) {
        _state = LOOSE;
        return;
    }
    if (_map[_pacman.y + vect.y][_pacman.x + vect.x] == _eggSym)
        _score += 200;
    if (_map[_pacman.y + vect.y][_pacman.x + vect.x] != _wallSym) {
        _map[_pacman.y][_pacman.x] = _bgSym;
        _map[_pacman.y + vect.y][_pacman.x + vect.x] = _pacmanSym;
        _pacman.y += vect.y;
        _pacman.x += vect.x;
    }
}

void Pacman::moveGhosts(void) {
    pos vect;
    pos position;

    for (size_t i = 0; i < _ghosts.size(); i++) {
        vect = getVectFromDirection(_ghosts[i].direction);
        position = _ghosts[i].position;
        if (_map[position.y + vect.y][position.x + vect.x] == _wallSym ||
            _map[position.y + vect.y][position.x + vect.x] == _ghostSym)
            vect = this->changeGhostDirection(_ghosts[i]);
        _map[position.y][position.x] = _ghosts[i].prevTile;
        _ghosts[i].prevTile = _map[position.y + vect.y][position.x + vect.x];
        _map[position.y + vect.y][position.x + vect.x] = _ghostSym;
        _ghosts[i].position.y += vect.y;
        _ghosts[i].position.x += vect.x;
    }
}

Pacman::pos Pacman::changeGhostDirection(ghost ghost) {
    pos vect = getVectFromRand((rand() % 4) + 1);
    pos position = ghost.position;

    while (_map[position.y + vect.y][position.x + vect.x] == _wallSym ||
            _map[position.y + vect.y][position.x + vect.x] == _ghostSym) {
        vect = getVectFromRand((rand() % 4) + 1);
    }
    return vect;
}

Pacman::pos Pacman::getVectFromRand(int rand) {
    switch (rand) {
        case 1:
            return {-1, 0};
        case 2:
            return {1, 0};
        case 3:
            return {0, -1};
        case 4:
            return {0, 1};
    }
    return {0, 0};
}

extern "C" LibType getLibType(void) {
    return GAME;
}

extern "C" IGame *create(void) {
    return new Pacman;
}

extern "C" void destroy(IGame *game) {
    delete game;
}
}  // namespace arc
