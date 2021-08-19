/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** SDLDisplay
*/

#ifndef LIB_DISPLAY_SDL2_SDLDISPLAY_HPP_
#define LIB_DISPLAY_SDL2_SDLDISPLAY_HPP_

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include "IDisplay.hpp"
#include "Error.hpp"
#include "SDL_ttf.h"

namespace arc {
/** @class SDLDisplay
 * @brief SDL2 Display library
 */
class SDLDisplay : public IDisplay {
 public:
    /**
     * @brief Construct a new SDLDisplay object
     *
     * Initialize SDL with everything
     */
    SDLDisplay(void);

    /**
     * @brief Destroy the SDLDisplay object
     *
     * Calls SDL_Quit()
     */
    virtual ~SDLDisplay(void);

    /**
     * @brief Create an SDL Window and renderer object
     */
    void createWindow(void) override;

    /**
     * @brief Destroys the SDL Window and renderer
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
     * @brief Displays the SDL window
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
     * @brief Draws text to the SDL window
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
     * @return "sdl2"
     */
    std::string getName(void) const override {
        return "sdl2";
    }

 private:
    /**
     * @brief Poll an input
     *
     * @return Input An enum of the one of the input if a recognized key is
     * pressed, NONE otherwise
     */
    Input getInputKey(const SDL_Event &event) const;

    const SDL_Color _WHITE = {255, 255, 255, 0};
    const SDL_Color _BLACK = {0, 0, 0, 0};

    //* SDL Window
    SDL_Window *_win;

    //* SDL Renderer
    SDL_Renderer *_ren;

    //* Default font
    TTF_Font *_font;

    //* Mapping of symbols to sprites
    std::unordered_map<char, SDL_Texture *> _spritesMap;
};

/** @class SDLError
 * @brief Errors related to SDL2 display library
 */
class SDLError : public DisplayError {
 public:
    SDLError(void)
        : DisplayError(std::string("SDL2: ") + SDL_GetError()) {}
    explicit SDLError(std::string const &message)
        : DisplayError(std::string("SDL2: ") + message) {}
};

/** @class TTFError
 * @brief Errors related to SDL2 TTF module
 */
class TTFError : public SDLError {
 public:
    TTFError(void)
        : SDLError(std::string("TTF: ") + TTF_GetError()) {}
    explicit TTFError(std::string const &message)
        : SDLError(std::string("TTF: ") + message) {}
};

/** @class IMGError
 * @brief Errors related to SDL2 Image module
 */
class IMGError : public SDLError {
 public:
    IMGError(void)
        : SDLError(std::string("IMG: ") + IMG_GetError()) {}
    explicit IMGError(std::string const &message)
        : SDLError(std::string("IMG: ") + message) {}
};
}  // namespace arc

#endif  // LIB_DISPLAY_SDL2_SDLDISPLAY_HPP_
