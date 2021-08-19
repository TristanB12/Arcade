/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** LibCacaDisplay
*/

#include <string.h>
#include <iostream>
#include "LibCacaDisplay.hpp"
#include "Error.hpp"

namespace arc {
int map(int x, int in_min, int in_max, int out_min, int out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

LibCacaDisplay::LibCacaDisplay(void) {
    _disp = NULL;
    _canvas = NULL;
}

void LibCacaDisplay::createWindow(void) {
    _canvas = caca_create_canvas(0, 0);
    if (_canvas == NULL)
        throw LibCacaError("couldn't create canvas");
    caca_set_canvas_boundaries(_canvas, 0, 0, 1920, 1080);
    _disp = caca_create_display(_canvas);
    if (_disp == NULL)
        throw LibCacaError("couldn't create window");
    caca_set_display_title(_disp, WIN_TITLE);
    caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLACK);
}

void LibCacaDisplay::destroyWindow(void) {
    caca_free_display(_disp);
    _disp = NULL;
    _canvas = NULL;
}

void LibCacaDisplay::loadSprites(const itemVec items) {
    (void)items;
}

void LibCacaDisplay::destroySprites(void) {}

void LibCacaDisplay::display(void)  {
    caca_refresh_display(_disp);
}

void LibCacaDisplay::clear(void) {
    caca_clear_canvas(_canvas);
}

void LibCacaDisplay::drawMap(map_t map) {
    for (size_t i = 0 ; map[i] ; i++)
        caca_put_str(_canvas, 0, i, map[i]);
}

void LibCacaDisplay::drawText(int x, int y, const char *text) {
    if (x < 0 || x > 100 || y < 0 || y > 100)
        throw LibCacaError("x or y percentage not in range [0, 100]");
    x = PERCENTAGE(x, caca_get_canvas_width(_canvas)) - strlen(text) / 2;
    y = PERCENTAGE(y, caca_get_canvas_height(_canvas));
    caca_put_str(_canvas, x, y, text);
}

void LibCacaDisplay::drawBox(int x, int y, int w, int h) {
    x = PERCENTAGE(x, caca_get_canvas_width(_canvas));
    y = PERCENTAGE(y, caca_get_canvas_height(_canvas));
    w = PERCENTAGE(w, caca_get_canvas_width(_canvas));
    h = PERCENTAGE(h, caca_get_canvas_height(_canvas));

    caca_draw_thin_box(_canvas, x, y, w, h);
}

Input LibCacaDisplay::getInput(void) {
    caca_event_t event;
    int key = 0;
    int type = CACA_EVENT_QUIT | CACA_EVENT_KEY_PRESS;

    if (!caca_get_event(_disp, type, &event, 100))
        return NONE;
    if (caca_get_event_type(&event) & CACA_EVENT_QUIT)
        return ESCAPE;
    if (caca_get_event_type(&event) & CACA_EVENT_KEY_PRESS) {
        key = caca_get_event_key_ch(&event);
        if (tolower(key) >= 'a' && tolower(key) <= 'z')
            return static_cast<Input>(A + (key - 'a'));
        switch (key) {
        case CACA_KEY_ESCAPE:
            return ESCAPE;
        case CACA_KEY_BACKSPACE:
            return BACKSPACE;
        case CACA_KEY_TAB:
            return TAB;
        case CACA_KEY_RETURN:
            return ENTER;
        case CACA_KEY_UP:
            return UP;
        case CACA_KEY_DOWN:
            return DOWN;
        case CACA_KEY_LEFT:
            return LEFT;
        case CACA_KEY_RIGHT:
            return RIGHT;
        default:
            break;
        }
    }
    return NONE;
}

extern "C" LibType getLibType(void) {
    return DISPLAY;
}

extern "C" IDisplay *create(void) {
    return new LibCacaDisplay;
}

extern "C" void destroy(IDisplay *display) {
    delete display;
}
}  // namespace arc
