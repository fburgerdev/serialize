#pragma once
#include "json_serializable.hpp"

namespace ASST {
    // JSONSerializable
    template<typename T>
    struct JSONSerializable<Opt<T>> {
        // toString
        static string toString(const Opt<T>& value) {
            if (value.has_value()) {
                return toJSONString(value.value());
            }
            else {
                return "null";
            }
        }
        // fromString
        static void fromString(const string& str, Opt<T>& value) {
            if (str == "null") {
                value.reset();
            }
            else {
                value = fromJSONString<T>(str);
            }
        }
    };
}