#pragma once
#include "common.hpp"
#include <concepts>
#include <variant>

namespace ASST {

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
    constexpr bool isStringMap = false;
    template<typename T>
    constexpr bool isStringMap<Map<string, T>> = true;
    template<typename T>
    constexpr bool isStringMap<HashMap<string, T>> = true;

    template<typename T>
    constexpr bool isPair = false;
    template<typename T, typename U>
    constexpr bool isPair<std::pair<T, U>> = true;
    
    template<typename... TArgs>
    constexpr bool isVariant = false;
    template<typename... TArgs>
    constexpr bool isVariant<std::variant<TArgs...>> = true;
}