/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** ALLEGRO5Display
*/

#ifndef LIB_DISPLAY_ALLEGRO5_ALLEGRO5DISPLAY_HPP_
#define LIB_DISPLAY_ALLEGRO5_ALLEGRO5DISPLAY_HPP_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <unordered_map>
#include "IDisplay.hpp"
#include "Error.hpp"

namespace arc {
/** @class Allegro5Display
 * @brief Allegro5 Display library
 */
class Allegro5Display : public IDisplay {
 public:
    /**
     * @brief Construct a new Allegro5Display object
     *
     * Initialize Allegro5 with everything
     */
    Allegro5Display(void);

    /**
     * @brief Destroy the Allegro5Display object
     *
     * Calls Allegro5_Quit()
     */
    virtual ~Allegro5Display(void);

    /**
     * @brief Create an Allegro5 Window and renderer object
     */
    void createWindow(void) override;

    /**
     * @brief Destroys the Allegro5 Window and renderer
     */
    void destroyWindow(void) override;

    /**
     * @brief Loads the textures of the game
     *
     * @param items A vector of items
     */
    void loadSprites(const itemVec items) override;

    /**
     * @brief Destroys the stored textures
     */
    void destroySprites(void) override;

    /**
     * @brief Displays the Allegro5 window
     */
    void display(void) override;

    /**
     * @brief Clears the content of the window
     */
    void clear(void) override;

    /**
     * @brief Draw the game map
     */
    void drawMap(map_t map) override;

    /**
     * @brief Draws text to the Allegro5 window
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
     * @return "allegro5"
     */
    std::string getName(void) const override {
        return "allegro5";
    }

 private:
    /**
     * @brief Poll an input
     *
     * @return Input An enum of the one of the input if a recognized key is
     * pressed, NONE otherwise
     */
    Input getInputKey(const ALLEGRO_EVENT &event) const;

    const ALLEGRO_COLOR WHITE = al_map_rgb(255, 255, 255);

    //* Allegro5 display
    ALLEGRO_DISPLAY *_disp;

    //* Default font
    ALLEGRO_FONT *_font;

    //* Event Queue
    ALLEGRO_EVENT_QUEUE *_eventQueue;

    //* Mapping of symbols to sprites
    std::unordered_map<char, ALLEGRO_BITMAP *> _spritesMap;
};

/** @class Allegro5Error
 * @brief Errors related to Allegro5 display library
 */
class Allegro5Error : public DisplayError {
 public:
    explicit Allegro5Error(std::string const &message)
        : DisplayError(std::string("Allegro5: ") + message) {}
};
}  // namespace arc

#endif  // LIB_DISPLAY_ALLEGRO5_ALLEGRO5DISPLAY_HPP_
