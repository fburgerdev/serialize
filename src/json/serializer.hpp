#pragma once
#include "serializable.hpp"

namespace ASST {
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
            return fromJSONString<T>(removeWhitespace(source));
        }
    };
}