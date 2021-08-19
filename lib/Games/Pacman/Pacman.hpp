/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Pacman
*/

#ifndef LIB_GAMES_NIBBLER_INC_NIBBLER_HPP_
#define LIB_GAMES_NIBBLER_INC_NIBBLER_HPP_

#include <vector>
#include <string>
#include "IGame.hpp"
#include "Parser.hpp"
#include "arcade.hpp"

namespace arc {
class Pacman : public IGame {
 public:
    Pacman(void);
    Pacman(char **map, std::vector<arc::item> items);
    virtual ~Pacman(void) {}

    void execKey(arc::Input key) override;
    inline char **getMap(void) const override {return _map;};
    void tick(void) override;
    inline void reset(void) override {init(_tempMap, _tempItems);};
    inline GAMESTATE getState() const {return _state;};
    inline size_t getScore(void) const {return _score;};
    inline std::string getName(void) const override {return "pacman";};
    inline std::vector<item> getItems(void) const override {return _tempItems;};
 private:
    void init(char **map, std::vector<arc::item> items);
    struct pos {
        int x;
        int y;
    };
    struct ghost {
        pos position;
        arc::Input direction;
        char prevTile;
    };
    void movePacman(void);
    void moveGhosts(void);
    pos changeGhostDirection(ghost ghost);
    pos getVectFromDirection(Input direction);
    pos getVectFromRand(int rand);
    void updateSnakePos(void);
    void clearMap(void);

    GAMESTATE _state;
    char **_tempMap;
    char **_map;
    std::vector<item> _tempItems;
    arc::Input _direction;
    char _wallSym;
    char _pacmanSym;
    char _bgSym;
    char _eggSym;
    char _ghostSym;
    pos _pacman;
    std::vector<ghost> _ghosts;
    size_t _score;
};
}  // namespace arc

#endif  // LIB_GAMES_NIBBLER_INC_NIBBLER_HPP_
