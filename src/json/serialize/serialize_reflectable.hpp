#pragma once
#include "json/serializable.hpp"
#include "reflectable.hpp"

namespace ASST {
    // JSONSerializable
    template<ReflectableType T>
    struct JSONSerializable<T> {
        // ToStringReflector
        class ToStringReflector {
        public:
            // record
            template<typename U>
            void record(const string& key, const U& value) {
                m_object[key] = indent(toJSONString<U>(value));
            }
            // toString
            string toString() const {
                return m_object.toString();
            }
        private:
            // json object
            JSONObject m_object;
        };
        // toString
        static string toString(const T& value) {
            ToStringReflector reflector;
            const_cast<T&>(value).reflect(reflector);
            return reflector.toString();
        }

        // FromStringReflector
        class FromStringReflector {
        public:
            // constructor
            FromStringReflector(const string& str)
                : m_object(str) {}
            // record
            template<typename U>
            void record(const string& key, U& value) {
                fromJSONString<U>(m_object.at(key), value);
            }
        private:
            // json object
            JSONObject m_object;
        };
        // fromString
        static void fromString(const string& str, T& value) {
            FromStringReflector reflector(str);
            value.reflect(reflector);
        }
    };
}