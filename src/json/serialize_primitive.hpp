#pragma once
#include "serialize_string.hpp"

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
    template<>
    struct JSONSerializable<char> {
        // toString
        static string toString(const char& value) {
            return toJSONString<string>(string({ value }));
        }
        // fromString
        static void fromString(const string& str, char& value) {
            value = fromJSONString<string>(str).front();
        }
    };
    // numeric
    template<typename T> requires (std::integral<T> || std::floating_point<T>)
    struct JSONSerializable<T> {
        // toString
        static string toString(const T& value) {
            return (ostrstream() << value).str();
        }
        // fromString
        static void fromString(const string& str, T& value) {
            istrstream(str) >> value;
        }
    };
}