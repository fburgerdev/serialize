#pragma once
#include "json.hpp"
#include "string_utils.hpp"

namespace ASST {
    // JSONSerializable
    template<typename T>
    struct JSONSerializable;

    // toJSONString
    template<typename T>
    string toJSONString(const T& value) {
        return JSONSerializable<T>::toString(value);
    }
    // fromJSONString
    template<typename T>
    void fromJSONString(const string& str, T& value) {
        JSONSerializable<T>::fromString(str, value);
    }
    template<typename T>
    T fromJSONString(const string& str) {
        T value;
        fromJSONString<T>(str, value);
        return value;
    }
}