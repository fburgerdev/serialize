#pragma once
#include "json/serializable.hpp"

namespace ASST {
    // JSONSerializable
    template<typename T>
    struct JSONSerializable<Optional<T>> {
        // toString
        static string toString(const Optional<T>& value) {
            if (value.has_value()) {
                return toJSONString(value.value());
            }
            else {
                return "null";
            }
        }
        // fromString
        static void fromString(const string& str, Optional<T>& value) {
            if (str == "null") {
                value.reset();
            }
            else {
                value = fromJSONString<T>(str);
            }
        }
    };
}