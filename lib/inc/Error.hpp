/*
** EPITECH PROJECT, 2021
** Arcade [WSL: Ubuntu-20.04]
** File description:
** ARCError
*/

#ifndef LIB_INC_ERROR_HPP_
#define LIB_INC_ERROR_HPP_

#include <exception>
#include <string>

namespace arc {
/** @class Error
 * @brief Standard arcade error
 */
class Error : public std::exception {
 public:
    explicit Error(std::string const &message)
        : _message(std::string("arcade: ") + message) {}

    inline virtual const char* what() const noexcept {
        return _message.c_str();
    }

 private:
    std::string _message;
};

/** @class DLError
 * @brief Errors related to dynamic libraries
 */
class DLError : public Error {
 protected:
    explicit DLError(std::string const &message)
        : Error(std::string("dynamic library ") + message) {}
};

/** @class DisplayError
 * @brief Errors related to display libraries
 */
class DisplayError : public Error {
 protected:
    explicit DisplayError(std::string const &message)
        : Error(std::string("display: ") + message) {}
};

/** @class GameError
 * @brief Errors related to game libraries
 */
class GameError : public Error {
 protected:
    explicit GameError(std::string const &message)
        : Error(std::string("game: ") + message) {}
};
}  // namespace arc

#endif  // LIB_INC_ERROR_HPP_
