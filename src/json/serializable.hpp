#pragma once
#include "json.hpp"
#include "logging.hpp"
#include "type_string.hpp"
#include "trace.hpp"

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

    #define ASSERT_JSON_DESERIALIZE(COND, STR, TYPE) ASSERT_MSG(COND, "JSON deserialization failed: expected '{}' to be of type '{}'", STR, TYPE); 
}