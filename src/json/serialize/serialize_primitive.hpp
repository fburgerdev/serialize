#pragma once
#include "json/serializable.hpp"
#include "trace.hpp"

namespace ASST {
    // bool
    template<>
    struct JSONSerializable<bool> {
        // toString
        static string toString(const bool& value) {
            return (value ? "true" : "false");
        }
        // fromString
        static void fromString(const string& str, bool& value) {
            value = (str == "true");
        }
    };
    // char
    template<typename T> requires std::same_as<T, char>
    struct JSONSerializable<T> {
        // toString
        static string toString(const T& value) {
            return toJSONString<string>(string({ value }));
        }
        // fromString
        static void fromString(const string& str, T& value) {
            value = fromJSONString<string>(str).front();
        }
    };
    // numeric
    template<typename T> requires ((std::integral<T> || std::floating_point<T>) && !std::same_as<T, char>)
    struct JSONSerializable<T> {
        // toString
        static string toString(const T& value) {
            if constexpr (std::is_same_v<T, schar>) {
                return (ostrstream() << static_cast<int>(value)).str();
            }
            else if constexpr (std::is_same_v<T, uchar>) {
                return (ostrstream() << static_cast<uint>(value)).str();
            }
            else {
                return (ostrstream() << value).str();
            }
        }
        // fromString
        static void fromString(const string& str, T& value) {
            if constexpr (std::is_floating_point_v<T>) {
                value = static_cast<T>(std::stold(str));
            }
            else if constexpr (std::is_unsigned_v<T>) {
                value = static_cast<T>(std::stoull(str));
            }
            else if constexpr (std::is_signed_v<T>) {
                value = static_cast<T>(std::stoll(str));
            }
        }
    };
}