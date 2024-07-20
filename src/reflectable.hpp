#pragma once
#include "common.hpp"

namespace ASST {
    // VoidReflector
    struct VoidReflector {
        // reflect
        template<typename T>
        void reflect(const string& str, const T& value) {
            // do nothing
        }
    };
    // ReflectableType
    template<typename T>
    concept ReflectableType = requires(T x, VoidReflector reflector) {
        { x.reflect(reflector) };
    };
}