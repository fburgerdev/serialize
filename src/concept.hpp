#pragma once
#include "common.hpp"
#include <concepts>

namespace ASST {
    // VoidReflector
    struct VoidReflector {
        // reflect
        template<typename T>
        void reflect(const string& str, const T& value) {
            // do nothing
        }
    };

    // concepts and type traits
    template<typename T>
    concept NumericType= std::integral<T> || std::floating_point<T>;
    template<class T>
    concept StringType = std::is_convertible_v<T, strview>;
    template<typename T>
    concept IterableType = requires(T x, const T y) {
        { x.begin() };
        { x.end() };
        { y.begin() };
        { y.end() };
    };
    template<typename T>
    concept ReflectableType = requires(T x, VoidReflector reflector) {
        { x.reflect(reflector) };
    };
    template<typename T>
    constexpr bool isPair = false;
    template<typename T, typename U>
    constexpr bool isPair<std::pair<T, U>> = true;
}