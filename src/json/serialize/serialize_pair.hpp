#pragma once
#include "json/serializable.hpp"

namespace ASST {
    // JSONSerializable
    template<typename T1, typename T2>
    struct JSONSerializable<Pair<T1, T2>> {
        // toString
        static string toString(const Pair<T1, T2>& value) {
            JSONList list;
            list.push(indent(toJSONString<T1>(value.first)));
            list.push(indent(toJSONString<T2>(value.second)));
            return list.toString();
        }
        // fromString
        static void fromString(const string& str, Pair<T1, T2>& value) {
            List<string> splitted = split(str.substr(1, str.length() - 2), { ',' });
            fromJSONString<T1>(splitted[0], value.first);
            fromJSONString<T2>(splitted[1], value.second);
        }
    };
}