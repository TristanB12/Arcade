/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** NcursesDisplay
*/

#ifndef LIB_DISPLAY_NCURSES_NCURSESDISPLAY_HPP_
#define LIB_DISPLAY_NCURSES_NCURSESDISPLAY_HPP_

#include <ncurses.h>
#include <string>
#include "IDisplay.hpp"
#include "Error.hpp"

namespace arc {
/** @class NcursesDisplay
 * @brief Ncurses Display library
 */
class NcursesDisplay : public IDisplay {
 public:
    /**
     * @brief Construct a new NcursesDisplay object
     */
    NcursesDisplay(void) {}

    /**
     * @brief Destroy the NcursesDisplay object
     */
    virtual ~NcursesDisplay(void) {}

    /**
     * @brief Create an Ncurses window
     */
    void createWindow(void) override;

    /**
     * @brief Destroys the ncurses window
     */
    void destroyWindow(void) override;

    /**
     * @brief Does nothing in ncurses
     *
     * @param items A vector of items
     */
    void loadSprites(const itemVec items) override;

    /**
     * @brief Does nothing in ncurses
     */
    void destroySprites(void) override;

    /**
     * @brief Display the Ncurses window
     */
    void display(void) override;

    /**
     * @brief Clears the content of the window
     */
    void clear(void) override;

    /**
     * @brief Draw a game's map
     */
    void drawMap(map_t map) override;

    /**
     * @brief Draws text to the Ncurses window
     *
     * @param x Percentage of the width
     * @param y Percentage of the height
     * @param text The text to be drawn
     */
    void drawText(int x, int y, const char *text) override;

    /**
     * @brief Draws a transparent-filled box with white border
     *
     * @param x Start position of the box on the X-axis
     * @param y Start position of the box on the Y-axis
     * @param w Width of the box
     * @param h Height of the box
     */
    void drawBox(int x, int y, int w, int h) override;

    /**
     * @brief Poll an input
     *
     * @return Input An enum of the one of the input if a recognized key is
     * pressed, NONE otherwise
     */
    Input getInput(void)override;

    /**
     * @brief Get the name of the library
     *
     * @return "ncurses"
     */
    std::string getName(void) const override {
        return "ncurses";
    }
};

/** @class NcursesError
 * @brief Errors related to Ncurses display library
 */
class NcursesError : public DisplayError {
 public:
    explicit NcursesError(std::string const &message)
        : DisplayError(std::string("ncurses: ") + message) {}
};
}  // namespace arc

#endif  // LIB_DISPLAY_NCURSES_NCURSESDISPLAY_HPP_
