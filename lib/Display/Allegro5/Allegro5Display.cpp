/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** Allegro5Display
*/

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "Allegro5Display.hpp"

namespace arc {
Allegro5Display::Allegro5Display(void) {
    if (!al_init())
        throw Allegro5Error("Couldn't initialize Allegro");
    if (!al_install_keyboard())
        throw Allegro5Error("Couldn't initialize keyboard");
    if (!al_init_image_addon())
        throw Allegro5Error("Couldn't initialize image addon");
    if (!al_init_primitives_addon())
        throw Allegro5Error("Couldn't initialize primitives addon");
    _font = al_create_builtin_font();
    if (!_font)
        throw Allegro5Error("Couldn't create builtin font");
    _disp = NULL;
    _eventQueue = NULL;
}

Allegro5Display::~Allegro5Display(void) {
    al_destroy_font(_font);
}

void Allegro5Display::createWindow(void) {
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    _disp = al_create_display(DEFAULT_WIN_WIDTH, DEFAULT_WIN_HEIGHT);
    if (!_disp)
        throw Allegro5Error("Couldn't create display");
    _eventQueue = al_create_event_queue();
    if (!_eventQueue)
        throw Allegro5Error("Couldn't create event queue");
    al_register_event_source(_eventQueue, al_get_keyboard_event_source());
    al_register_event_source(_eventQueue, al_get_display_event_source(_disp));
}

void Allegro5Display::destroyWindow(void) {
    al_destroy_display(_disp);
    al_destroy_event_queue(_eventQueue);
}

void Allegro5Display::loadSprites(const itemVec items) {
    ALLEGRO_BITMAP *sprite = NULL;

    for (auto item : items) {
        sprite = al_load_bitmap(item.path.c_str());
        if (!sprite)
            throw Allegro5Error("failed to load texture from path" + item.path);
        _spritesMap.emplace(item.sym, sprite);
    }
}

void Allegro5Display::destroySprites(void) {
    for (auto &[symbol, sprite] : _spritesMap)
        al_destroy_bitmap(sprite);
    _spritesMap.clear();
}

void Allegro5Display::display(void) {
    al_flip_display();
}

void Allegro5Display::clear() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void Allegro5Display::drawMap(map_t map) {
    ALLEGRO_BITMAP *sprite = NULL;
    float dx = 0.0f;
    float dy = 0.0f;
    char symbol = 0;

    for (size_t i = 0 ; map[i] ; i++) {
        dx = 0.0f;
        for (size_t j = 0 ; map[i][j] ; j++) {
            symbol = map[i][j];
            try {
                sprite = _spritesMap.at(symbol);
            } catch (const std::out_of_range &_) {
                throw Allegro5Error("No matching sprite for symbol " + symbol);
            }
            al_draw_bitmap(sprite, dx, dy, 0);
            dx += SPRITE_SIZE;
        }
        dy += SPRITE_SIZE;
    }
}

void Allegro5Display::drawText(int x, int y, const char *msg) {
    int width = al_get_text_width(_font, msg);

    x = PERCENTAGE(x, al_get_display_width(_disp)) - width / 2;
    y = PERCENTAGE(y, al_get_display_height(_disp));
    al_draw_text(_font, WHITE, x, y, 0, msg);
}

void Allegro5Display::drawBox(int x, int y, int w, int h) {
    float x1 = PERCENTAGE(x, al_get_display_width(_disp));
    float x2 = x1 + PERCENTAGE(w, al_get_display_width(_disp));
    float y1 = PERCENTAGE(y, al_get_display_height(_disp));
    float y2 = y1 + PERCENTAGE(h, al_get_display_height(_disp));

    al_draw_rectangle(x1, y1, x2, y2, WHITE, 2.0f);
}

Input Allegro5Display::getInput(void) {
    ALLEGRO_EVENT event;
    ALLEGRO_TIMEOUT timeout;

    al_init_timeout(&timeout, 0.1);
    if (!al_wait_for_event_until(_eventQueue, &event, &timeout))
        return NONE;
    switch (event.type) {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        return ESCAPE;
    case ALLEGRO_EVENT_KEY_DOWN:
        return this->getInputKey(event);
    default:
        break;
    }
    return NONE;
}

Input Allegro5Display::getInputKey(const ALLEGRO_EVENT &event) const {
    int key = event.keyboard.keycode;

    if (key >= ALLEGRO_KEY_A && key <= ALLEGRO_KEY_Z)
        return static_cast<Input>(A + (key - ALLEGRO_KEY_A));
    switch (key) {
    case ALLEGRO_KEY_ESCAPE:
        return ESCAPE;
    case ALLEGRO_KEY_TAB:
        return TAB;
    case ALLEGRO_KEY_ENTER:
        return ENTER;
    case ALLEGRO_KEY_BACKSPACE:
        return BACKSPACE;
    case ALLEGRO_KEY_UP:
        return UP;
    case ALLEGRO_KEY_LEFT:
        return LEFT;
    case ALLEGRO_KEY_DOWN:
        return DOWN;
    case ALLEGRO_KEY_RIGHT:
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
    return new Allegro5Display;
}

extern "C" void destroy(IDisplay *display) {
    delete display;
}
}  // namespace arc
