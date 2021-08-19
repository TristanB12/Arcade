/*
** EPITECH PROJECT, 2021
** arcade [WSL: Ubuntu-20.04]
** File description:
** DLLoader
*/

#include "DLLoader.hpp"

namespace arc {
template <typename T>
bool DLLoader<T>::libTypeIsCorrect(void) {
    return true;
}

template <>
bool DLLoader<IDisplay>::libTypeIsCorrect(void) {
    libTypeFunc func = nullptr;

    func = reinterpret_cast<libTypeFunc>(dlsym(_handle, libTypeName));
    if (func == NULL)
        throw DLLoaderError();
    return func() == DISPLAY;
}

template <>
bool DLLoader<IGame>::libTypeIsCorrect(void) {
    libTypeFunc func = nullptr;

    func = reinterpret_cast<libTypeFunc>(dlsym(_handle, libTypeName));
    if (func == NULL)
        throw DLLoaderError();
    return func() == GAME;
}
}  // namespace arc
