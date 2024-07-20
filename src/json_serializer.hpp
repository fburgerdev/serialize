#pragma once
#include "json/json_serializable.hpp"

namespace ASST {
    // WriteReflector
    // toString
    // :: null
    // string toString(std::nullptr_t null, const string& indent = "") {
    //     return "null";
    // }
    // :: map with string key
    // template<typename T> requires isStringMap<T>
    // string toString(const T& map, const string& indent = "") {
    //     JSONObject obj;
    //     for (const auto& [key, value] : map) {
    //         obj[key] = toString<typename T::mapped_type>(value, indent + "    ");
    //     }
    //     return obj.toString(indent);
    // }

    // fromString
    // :: null
    // template<typename T> requires std::same_as<T, std::nullptr_t>
    // T fromString(const string& str) {
    //     return nullptr;
    // }
    // :: map with string key
    // template<typename T> requires isStringMap<T>
    // T fromString(const string& str) {
    //     T map;
    //     JSONObject obj(str);
    //     for (const auto& [key, value] : obj) {
    //         map.emplace(key, fromString<typename T::mapped_type>(value));
    //     }
    //     return map;
    // }

    // JSONSerializer
    class JSONSerializer {
    public:
        // serialize
        template<typename T>
        static void serialize(const string& filepath, const T& value) {
            ofstream(filepath) << toJSONString<T>(value);
        }
        // deserialize
        template<typename T>
        static T deserialize(const string& filepath) {
            string source = (strstream() << ifstream(filepath).rdbuf()).str();
            return fromJSONString<T>(removeWhitespaces(source));
        }
    };
}