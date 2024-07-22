#pragma once
#include "serializable.hpp"
#include "trace.hpp"

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
            try {
                T data = fromJSONString<T>(removeWS(source));
                return data;
            }
            catch (const SerializationTrace& trace) {
                LOG_FATAL(trace.toString());
                throw;
            }
        }
    };
}