/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** Core
*/

#ifndef LIB_CORE_INC_CORE_HPP_
#define LIB_CORE_INC_CORE_HPP_

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include "arcade.hpp"
#include "DLManager.hpp"
#include "IDisplay.hpp"
#include "IGame.hpp"
#include "Error.hpp"

namespace arc {
/** @class CoreError
 * @brief Errors related to arcade Core
 */
class CoreError : public Error {
 public:
    explicit CoreError(std::string const &message)
        : Error(std::string("core: ") + message) {}
};

/** @class Core
 * @brief Bridge between a game library and a display library
 */
class Core {
 public:
    /**
     * @brief Construct a new Core object with a selected display
     *
     * @param filename Path to the library to load
     */
    explicit Core(const std::string &filename);

    /**
     * @brief Destroy the Core object
     */
    virtual ~Core(void) {}

    /**
     * @brief Launches the arcade !
     */
    void run(void);

 private:
    typedef DLLoader<IDisplay> DispLoader;
    typedef DLLoader<IGame> GameLoader;
    typedef std::shared_ptr<DispLoader> DispLoaderPtr;
    typedef std::shared_ptr<GameLoader> GameLoaderPtr;
    typedef std::function<void(void)> handler;

    /**
     * @brief Get the high score of a game
     *
     * @param gameName The name of the game
     * @return size_t The high score of the game
     */
    size_t getHiScore(const std::string &gameName) const;

    /**
     * @brief Saves the high score of a game
     *
     * @param gameName The name of the game
     * @param score The score to store
     */
    void saveHiScore(const std::string &gameName, const size_t score) const;

    /**
     * @brief Handles the inputs related to arcade
     */
    void execKeys(const Input input);

    void dispLoop(void);

    void gameLoop(IDisplay *disp);

    /**
     * @brief Map the inputs to their corresponding action in a game
     */
    void mapInputsGame(void);

    class Menu {
     public:
        explicit Menu(Core &core);
        virtual ~Menu(void) {}

        void loop(IDisplay *disp);
        void draw(IDisplay *disp) const;
        void handleEnteredText(const Input input);
        void mapInputs(void);

     private:
        //* Reference to parent class Core to access its private members
        Core &_core;

        //* Game index
        size_t _gameIdx;

        //* Display index
        size_t _dispIdx;

        //* Player name limited to 3 uppercase characters
        std::string _playerName;

        //* Current section of the menu
        enum Section {
            YOUR_NAME,
            DISPLAY,
            GAME
        } _section;
    } _menu;

    //* Boolean checking if the arcade is currently running or not
    bool _isRunning;

    //* Display Manager
    DLManager<IDisplay> _dispM;

    //* Game Manager
    DLManager<IGame> _gameM;

    //* Current scene
    enum Scene {
        MENU,
        GAME
    } _scene;

    //* Events handlers
    std::unordered_map<Input, handler> _handlers;
};
}  // namespace arc


#endif  // LIB_CORE_INC_CORE_HPP_
