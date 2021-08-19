/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** SFMLDisplay
*/

#include "SFMLDisplay.hpp"

namespace arc {
SFMLDisplay::SFMLDisplay(void) {
    if (!_font.loadFromFile(DEFAULT_FONT_PATH))
        throw SFMLError("failed to load default font");
}

SFMLDisplay::~SFMLDisplay(void) {}

void SFMLDisplay::createWindow(void) {
    _win.create(sf::VideoMode::getDesktopMode(), WIN_TITLE, sf::Style::Close);
    _win.setPosition(sf::Vector2i(0, 0));
    _win.setFramerateLimit(60);
}

void SFMLDisplay::destroyWindow(void) {
    _win.close();
}

void SFMLDisplay::loadSprites(const itemVec items) {
    sf::Texture texture;

    for (auto item : items) {
        if (!texture.loadFromFile(item.path))
            throw SFMLError("failed to load texture from path" + item.path);
        _spritesMap.emplace(item.sym, texture);
    }
}

void SFMLDisplay::destroySprites(void) {
    _spritesMap.clear();
}

void SFMLDisplay::display(void) {
    _win.display();
}

void SFMLDisplay::clear() {
    _win.clear();
}

void SFMLDisplay::drawMap(map_t map) {
    sf::Sprite sprite;
    sf::Vector2f pos(0, 0);
    char symbol = 0;

    for (size_t i = 0 ; map[i] ; i++) {
        pos.x = 0;
        for (size_t j = 0 ; map[i][j] ; j++) {
            symbol = map[i][j];
            try {
                sprite.setTexture(_spritesMap.at(symbol));
            } catch (const std::out_of_range &_) {
                throw SFMLError("No matching sprite for symbol " + symbol);
            }
            pos.x += SPRITE_SIZE;
            sprite.setPosition(pos);
            _win.draw(sprite);
        }
        pos.y += SPRITE_SIZE;
    }
}

void SFMLDisplay::drawText(int x, int y, const char *msg) {
    sf::Text text(msg, _font, DEFAULT_FONT_SIZE);
    sf::FloatRect textRect = text.getGlobalBounds();
    sf::Vector2f pos;

    pos.x = PERCENTAGE(x, _win.getSize().x) - textRect.width / 2;
    pos.y = PERCENTAGE(y, _win.getSize().y) - textRect.height / 2;
    text.setPosition(pos);
    _win.draw(text);
}

void SFMLDisplay::drawBox(int x, int y, int w, int h) {
    sf::Vector2f pos;
    sf::Vector2f size;
    sf::RectangleShape box;

    pos.x  = PERCENTAGE(x, _win.getSize().x);
    pos.y  = PERCENTAGE(y, _win.getSize().y);
    size.x = PERCENTAGE(w, _win.getSize().x);
    size.y = PERCENTAGE(h, _win.getSize().y);
    box.setFillColor(sf::Color::Transparent);
    box.setPosition(pos);
    box.setSize(size);
    box.setOutlineThickness(1.0);
    _win.draw(box);
}

Input SFMLDisplay::getInput(void) {
    sf::Event event;

    while (_win.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                return ESCAPE;
            case sf::Event::KeyPressed:
                return this->getInputKey(event);
            default:
                break;
        }
    }
    return NONE;
}

Input SFMLDisplay::getInputKey(const sf::Event &event) const {
    sf::Keyboard::Key key = event.key.code;

    if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z)
        return static_cast<Input>(A + (key - sf::Keyboard::A));
    switch (key) {
    case sf::Keyboard::Escape:
        return ESCAPE;
    case sf::Keyboard::Tab:
        return TAB;
    case sf::Keyboard::Enter:
        return ENTER;
    case sf::Keyboard::BackSpace:
        return BACKSPACE;
    case sf::Keyboard::Up:
        return UP;
    case sf::Keyboard::Left:
        return LEFT;
    case sf::Keyboard::Down:
        return DOWN;
    case sf::Keyboard::Right:
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
    return new SFMLDisplay;
}

extern "C" void destroy(IDisplay *display) {
    delete display;
}
}  // namespace arc
