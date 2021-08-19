/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** IDisplay
*/

#ifndef LIB_INC_IDISPLAY_HPP_
#define LIB_INC_IDISPLAY_HPP_

#include <string>
#include "arcade.hpp"

#define PERCENTAGE(coord, size) ((coord * size) / 100)

namespace arc {
const char WIN_TITLE[] = "Arcade";
const char DEFAULT_FONT_PATH[] = "./assets/karmaticarcade.ttf";
const size_t DEFAULT_WIN_WIDTH = 1920;
const size_t DEFAULT_WIN_HEIGHT = 1080;
const size_t DEFAULT_FONT_SIZE = 40;
const size_t SPRITE_SIZE = 32;

/** @class IDisplay
 * @brief Interface for a display library
 */
class IDisplay {
 public:
    virtual ~IDisplay() = default;

    virtual void createWindow(void) = 0;
    virtual void destroyWindow(void) = 0;
    virtual void loadSprites(const itemVec items) = 0;
    virtual void destroySprites(void) = 0;
    virtual void display(void) = 0;
    virtual void clear(void) = 0;
    virtual void drawMap(map_t map) = 0;
    virtual void drawText(int x, int y, const char *text) = 0;
    virtual void drawBox(int x, int y, int w, int h) = 0;
    virtual Input getInput(void) = 0;
    virtual std::string getName(void) const = 0;
};
}  // namespace arc

#endif  // LIB_INC_IDISPLAY_HPP_
