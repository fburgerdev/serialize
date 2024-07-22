#pragma once
#include "json/serializable.hpp"

namespace ASST {
    // JSONSerializable
    template<typename T1, typename T2>
    struct JSONSerializable<Pair<T1, T2>> {
        // toString
        static string toString(const Pair<T1, T2>& value) {
            JSONList list;
            list.push(toJSONString<T1>(value.first));
            list.push(toJSONString<T2>(value.second));
            return list.toString();
        }
        // fromString
        static void fromString(const string& str, Pair<T1, T2>& value) {
            // ASSERT_JSON_DESERIALIZE(str.length() >= 2 && (str.front() == '[' && str.back() == ']'), str, (TypeString<Pair<T1, T2>>()()));
            List<string> splitted = split(str.substr(1, str.length() - 2), { ',' });
            // ASSERT_JSON_DESERIALIZE(splitted.size() == 2, str, (TypeString<Pair<T1, T2>>()()));
            fromJSONString<T1>(splitted[0], value.first);
            fromJSONString<T2>(splitted[1], value.second);
        }
    };
}