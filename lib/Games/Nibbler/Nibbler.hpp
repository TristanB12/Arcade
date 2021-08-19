/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Nibbler
*/

#ifndef LIB_GAMES_NIBBLER_INC_NIBBLER_HPP_
#define LIB_GAMES_NIBBLER_INC_NIBBLER_HPP_

#include <vector>
#include <string>
#include "IGame.hpp"
#include "Parser.hpp"
#include "arcade.hpp"

namespace arc {
class Nibbler : public IGame {
 public:
    Nibbler(void);
    Nibbler(char **map, std::vector<arc::item> items);
    virtual ~Nibbler(void) {}

    void execKey(arc::Input key) override;
    inline char **getMap(void) const override {return _map;};
    void tick(void) override;
    inline void reset(void) override {init(_tempMap, _tempItems);};
    inline GAMESTATE getState() const override {return _state;};
    inline size_t getScore(void) const {return _score;};
    inline std::string getName(void) const override {return "nibbler";};
    inline std::vector<item> getItems(void) const override {return _tempItems;};
 private:
    void init(char **map, std::vector<arc::item> items);
    struct pos {
        int x;
        int y;
    };
    void moveSnake(void);
    pos getVectFromDirection(Input direction);
    void updateSnakePos(void);
    void clearMap(void);
    void spawnEgg(void);
    pos getMapSize(void);

    GAMESTATE _state;
    char **_tempMap;
    std::vector<item> _tempItems;
    char **_map;
    arc::Input _direction;
    char _wallSym;
    char _snakeSym;
    char _bgSym;
    char _eggSym;
    std::vector<pos> _snake;
    size_t _score;
};
}  // namespace arc

#endif  // LIB_GAMES_NIBBLER_INC_NIBBLER_HPP_
