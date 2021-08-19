/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** SDLDisplay
*/

#include <iostream>
#include "SDL_image.h"
#include "SDLDisplay.hpp"
#include "Error.hpp"

namespace arc {
SDLDisplay::SDLDisplay(void) {
    _win = NULL;
    _ren = NULL;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
        throw SDLError();
    IMG_Init(IMG_INIT_PNG);
    if (TTF_Init() == -1)
        throw TTFError();
    _font = TTF_OpenFont(DEFAULT_FONT_PATH, 40);
    if (_font == NULL)
        throw TTFError();
}

SDLDisplay::~SDLDisplay(void) {
    TTF_CloseFont(_font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void SDLDisplay::createWindow(void) {
    // TODO(julien): make width and height not hardcoded
    if (SDL_CreateWindowAndRenderer(1920, 1080, SDL_WINDOW_FULLSCREEN_DESKTOP,
            &_win, &_ren) == -1)
        throw SDLError();
    if (SDL_SetRenderDrawColor(_ren, 0, 0, 0, SDL_ALPHA_OPAQUE) == -1)
        throw SDLError();
    SDL_RenderClear(_ren);
}

void SDLDisplay::destroyWindow(void) {
    SDL_DestroyRenderer(_ren);
    SDL_DestroyWindow(_win);
    _win = NULL;
    _ren = NULL;
}

void SDLDisplay::loadSprites(const itemVec items) {
    SDL_Surface *surface = NULL;
    SDL_Texture *sprite = NULL;

    for (auto item : items) {
        surface = IMG_Load(item.path.c_str());
        if (surface == NULL)
            throw IMGError();
        sprite = SDL_CreateTextureFromSurface(_ren, surface);
        if (sprite == NULL)
            throw SDLError();
        _spritesMap.emplace(item.sym, sprite);
        SDL_FreeSurface(surface);
    }
}

void SDLDisplay::destroySprites(void) {
    for (auto &[symbol, sprite] : _spritesMap)
        SDL_DestroyTexture(sprite);
    _spritesMap.clear();
}

void SDLDisplay::display(void) {
    SDL_RenderPresent(_ren);
}

void SDLDisplay::drawMap(map_t map) {
    SDL_Texture *sprite = NULL;
    SDL_Rect rect = {0, 0, SPRITE_SIZE, SPRITE_SIZE};
    char symbol = 0;

    for (size_t i = 0 ; map[i] ; i++) {
        rect.x = 0;
        for (size_t j = 0 ; map[i][j] ; j++) {
            symbol = map[i][j];
            try {
                sprite = _spritesMap.at(symbol);
            } catch (const std::out_of_range &_) {
                throw SDLError(std::string("No matching sprite for symbol \'")
                    + symbol);
            }
            rect.x += SPRITE_SIZE;
            SDL_RenderCopy(_ren, sprite, NULL, &rect);
        }
        rect.y += SPRITE_SIZE;
    }
}

void SDLDisplay::drawText(int x, int y, const char *text) {
    int winWidth = 0;
    int winHeight = 0;
    int textWidth = 0;
    int textHeight = 0;
    SDL_Rect rect = {0, 0, 0, 0};
    SDL_Texture *message = NULL;
    SDL_Surface *surface = NULL;

    if (text[0] == 0)
        return;
    surface = TTF_RenderText_Solid(_font, text, _WHITE);
    if (surface == NULL)
        throw TTFError();
    message = SDL_CreateTextureFromSurface(_ren, surface);
    if (message == NULL)
        throw SDLError();
    SDL_GetWindowSize(_win, &winWidth, &winHeight);
    if (TTF_SizeText(_font, text, &textWidth, &textHeight) == -1)
        throw TTFError();
    rect.x = (x * winWidth / 100) - textWidth / 2;
    rect.y = (y * winHeight / 100) - textHeight / 2;
    rect.w = textWidth;
    rect.h = textHeight;
    if (SDL_RenderCopy(_ren, message, NULL, &rect) == -1)
        throw SDLError();
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
}

void SDLDisplay::drawBox(int x, int y, int w, int h) {
    int width = 0;
    int height = 0;
    SDL_Rect rect = {0, 0, 0, 0};

    SDL_GetWindowSize(_win, &width, &height);
    rect.x = (x * width / 100);
    rect.y = (y * height / 100);
    rect.w = (w * width / 100);
    rect.h = (h * height / 100);
    if (SDL_SetRenderDrawColor(_ren, 255, 255, 255, SDL_ALPHA_OPAQUE) == -1)
        throw SDLError();
    if (SDL_RenderDrawRect(_ren, &rect) == -1)
        throw SDLError();
    if (SDL_SetRenderDrawColor(_ren, 0, 0, 0, SDL_ALPHA_OPAQUE) == -1)
        throw SDLError();
}

void SDLDisplay::clear() {
    if (SDL_RenderClear(_ren) == -1)
        throw SDLError();
}

Input SDLDisplay::getInput(void) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return ESCAPE;
            case SDL_KEYDOWN:
                return this->getInputKey(event);
            default:
                break;
        }
    }
    return NONE;
}

Input SDLDisplay::getInputKey(const SDL_Event &event) const {
    SDL_Scancode key = event.key.keysym.scancode;

    if (key >= SDL_SCANCODE_A && key <= SDL_SCANCODE_Z)
        return static_cast<Input>(A + (key - SDL_SCANCODE_A));
    switch (key) {
    case SDL_SCANCODE_ESCAPE:
        return ESCAPE;
    case SDL_SCANCODE_TAB:
        return TAB;
    case SDL_SCANCODE_RETURN:
        return ENTER;
    case SDL_SCANCODE_BACKSPACE:
        return BACKSPACE;
    case SDL_SCANCODE_UP:
        return UP;
    case SDL_SCANCODE_LEFT:
        return LEFT;
    case SDL_SCANCODE_DOWN:
        return DOWN;
    case SDL_SCANCODE_RIGHT:
        return RIGHT;
    default:
        break;
    }
    return NONE;
}

extern "C" LibType getLibType(void) {
    return DISPLAY;
}

extern "C" IDisplay *create(void) {
    return new SDLDisplay;
}

extern "C" void destroy(IDisplay *display) {
    delete display;
}
}  // namespace arc
