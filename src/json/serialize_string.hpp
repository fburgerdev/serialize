#pragma once
#include "json_serializable.hpp"

namespace ASST {
    // JSONSerializable
    template<typename T> requires std::same_as<T, string>
    struct JSONSerializable<T> {
        // toString
        static string toString(const T& value) {
            string str(value);
            for (const auto& [from, to] : EscapeSequences) {
                str = stringReplace(str, from, to);
            }
            return "\"" + str + "\"";
        }
        // fromString
        static void fromString(const string& str, T& value) {
            value = str.substr(1, str.length() - 2);
            for (const auto& [to, from] : EscapeSequences) {
                value = stringReplace(value, from, to);
            }
        }
    };
}