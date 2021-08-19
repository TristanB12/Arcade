/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** SFMLDisplay
*/

#ifndef LIB_DISPLAY_SFML_SFMLDISPLAY_HPP_
#define LIB_DISPLAY_SFML_SFMLDISPLAY_HPP_

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "IDisplay.hpp"
#include "Error.hpp"

namespace arc {
/** @class SFMLDisplay
 * @brief SFML Display library
 */
class SFMLDisplay : public IDisplay {
 public:
    /**
     * @brief Construct a new SFMLDisplay object
     *
     * Initialize SFML with everything
     */
    SFMLDisplay(void);

    /**
     * @brief Destroy the SFMLDisplay object
     *
     * Calls SFML_Quit()
     */
    virtual ~SFMLDisplay(void);

    /**
     * @brief Create an SFML Window and renderer object
     */
    void createWindow(void) override;

    /**
     * @brief Destroys the SFML Window and renderer
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
     * @brief Displays the SFML window
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
     * @brief Draws text to the SFML window
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
     * @return "sfml"
     */
    std::string getName(void) const override {
        return "sfml";
    }

 private:
    /**
     * @brief Poll an input
     *
     * @return Input An enum of the one of the input if a recognized key is
     * pressed, NONE otherwise
     */
    Input getInputKey(const sf::Event &event) const;

    //* SFML Window
    sf::RenderWindow _win;

    //* Default font
    sf::Font _font;

    //* Mapping of symbols to sprites
    std::unordered_map<char, sf::Texture> _spritesMap;
};

/** @class SFMLError
 * @brief Errors related to SFML display library
 */
class SFMLError : public DisplayError {
 public:
    explicit SFMLError(std::string const &message)
        : DisplayError(std::string("SFML: ") + message) {}
};
}  // namespace arc

#endif  // LIB_DISPLAY_SFML_SFMLDISPLAY_HPP_
