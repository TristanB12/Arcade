/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** DLManager
*/

#ifndef LIB_CORE_INC_DLMANAGER_HPP_
#define LIB_CORE_INC_DLMANAGER_HPP_

#include <memory>
#include <filesystem>
#include <vector>
#include <string>
#include "DLLoader.hpp"
#include "Error.hpp"

namespace arc {
/** @class DLManagerError
 * @brief Errors related to managing dynamic libraries
 */
class DLManagerError : public DLError {
 public:
    explicit DLManagerError(std::string const &message)
        : DLError(std::string("manager: ") + message) {}
};

/** @class DLManager
 * @brief Container of dynamic libraries
 */
template <typename T>
class DLManager {
 public:
    /**
     * @brief Create a DLManager object with no library loaded
     *
     * Call loadLibs next to load libraries
     */
    DLManager(void) : _i(0) {}

    /**
     * @brief Loads matching dynamic libraries from the lib directory
     *
     * @param libNames Vector containing the name of the libraries to load
     * @example DLManager("OpenGL", "SDL2", "Ncurses")
     */
    explicit DLManager(const std::vector<std::string> &libNames) : _i(0) {
        this->loadLibs(libNames);
    }

    /**
     * @brief Destroy the Display Manager object
     */
    virtual ~DLManager(void) {}

    /**
     * @brief Loads the previous dynamic library
     */
    void prev(void) {
        if (_i == 0)
            _i = _libs.size() - 1;
        else
            _i--;
    }

    /**
     * @brief Loads the next dynamic library
     */
    void next(void) {
        _i++;
        if (_i >= _libs.size())
            _i = 0;
    }

    /**
     * @brief Sets the current dynamic library
     *
     * @param libName Name of the library to set, always in lowercase
     * @example set("sdl2")
     */
    void set(const std::string &libName) {
        _i = 0;
        for (const DLPtr lib : _libs) {
            if (lib.get()->get()->getName() == libName)
                return;
            _i++;
        }
        if (_i == _libs.size())
            throw DLManagerError("Couldn't find library named " + libName);
    }

    /**
     * @brief Get the current instance of the loaded dynamic library
     *
     * @return A pointer to the instance of the loaded dynamic library
     */
    T *get(void) {
        return _libs[_i].get()->get();
    }

    std::vector<std::string> getLibNames(void) const {
        std::vector<std::string> libNames;

        libNames.reserve(_libs.size());
        for (const DLPtr lib : _libs)
            libNames.push_back(lib.get()->get()->getName());
        return libNames;
    }

    /**
     * @brief Get the number of loaded libraries
     *
     * @return size_t Number of loaded libraries
     */
    size_t size(void) const {
        return _libs.size();
    }

    /**
     * @brief Loads matching dynamic libraries from the lib directory
     *
     * @param libNames Vector containing the name of the libraries to load
     */
    void loadLibs(void) {
        DLPtr lib = nullptr;

        for (auto &file : std::filesystem::directory_iterator(LIBDIR)) {
            if (file.is_regular_file() && libMatches(file.path())) {
                try {
                    lib = DLPtr(new DLLoader<T>(file.path()));
                    _libs.push_back(lib);
                } catch (const DLLoaderError &_) {}
            }
        }
    }

    typedef std::shared_ptr<DLLoader<T>> DLPtr;
    typedef std::vector<DLPtr> DLPtrVec;

 private:
    /**
     * @brief Checks if the format of a filename matches one of an arcade
     * dynamic library filename
     *
     * A filename is considered compliant if it starts with "arcade_" and has
     * the extension ".so".
     *
     * @param filename Name of the file to check
     * @return True if the filename is compliant
     * @return False if the filename is not compliant
     */
    bool libMatches(const std::string &filename) {
        auto startsWith = [](const std::string &str, const std::string &toFind){
            if (str.rfind(toFind, 0) == 0)
                return true;
            return false;
        };
        auto endsWith = [](const std::string &str, const std::string &toFind) {
            if (str.length() < toFind.length())
                return false;
            return (str.compare(str.length() - toFind.length(), toFind.length(),
                    toFind) == 0);
        };
        return (
            startsWith(filename, std::string(LIBDIR) + "arcade_")
            && endsWith(filename, ".so"));
    }

    //* Index poiting to the current dynamic library
    size_t _i;

    //* Vector containing the loaded dynamic libraries
    DLPtrVec _libs;
};
}  // namespace arc

#endif  // LIB_CORE_INC_DLMANAGER_HPP_
