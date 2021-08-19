/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** LibCaca
*/

#ifndef LIB_DISPLAY_LIBCACA_LIBCACADISPLAY_HPP_
#define LIB_DISPLAY_LIBCACA_LIBCACADISPLAY_HPP_

#include <string>
#include <caca.h>
#include "Error.hpp"
#include "IDisplay.hpp"

namespace arc {
/** @class LibCacaDisplay
 * @brief LibCaca Display library
 */
class LibCacaDisplay : public IDisplay {
 public:
    public:
    /**
     * @brief Construct a new LibCacaDisplay object
     */
    LibCacaDisplay(void);

    /**
     * @brief Destroy the LibCacaDisplay object
     */
    virtual ~LibCacaDisplay(void) {}

    /**
     * @brief Creates a LibCaca window
     */
    void createWindow(void) override;

    /**
     * @brief Destroys the LibCaca window
     */
    void destroyWindow(void) override;

    /**
     * @brief Does nothing in LibCaca
     *
     * @param items A vector of items
     */
    void loadSprites(const itemVec items) override;

    /**
     * @brief Does nothing in LibCaca
     */
    void destroySprites(void) override;

    /**
     * @brief Display the LibCaca window
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
     * @brief Draws text to the LibCaca window
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
    Input getInput(void) override;

    /**
     * @brief Get the name of the library
     *
     * @return "libcaca"
     */
    std::string getName(void) const override {
        return "libcaca";
    }

 private:
    caca_display_t *_disp;
    caca_canvas_t *_canvas;
};

class LibCacaError : public DisplayError {
 public:
    explicit LibCacaError(std::string const &message)
        : DisplayError(std::string("libcaca: ") + message) {}
};
}  // namespace arc

#endif  // LIB_DISPLAY_LIBCACA_LIBCACADISPLAY_HPP_
