#pragma once
#include "json/serializable.hpp"

namespace ASST {
    // JSONSerializable
    template<typename... TArgs>
    struct JSONSerializable<Tuple<TArgs...>> {
        // toStringVariant
        template<address Index>
        static void toStringTuple(const Tuple<TArgs...>& tuple, JSONList& list) {
            using Type = std::tuple_element_t<Index, Tuple<TArgs...>>;
            list.push(toJSONString<Type>(std::get<Index>(tuple)));
            if constexpr (Index + 1 < sizeof...(TArgs)) {
                toStringTuple<Index + 1>(tuple, list);
            }
        }
        // toString
        static string toString(const Tuple<TArgs...>& value) {
            JSONList list;
            toStringTuple<0>(value, list);
            return list.toString();
        }

        // fromStringVariant
        template<address Index>
        static void fromStringTuple(const JSONList& list, Tuple<TArgs...>& value) {
            using Type = std::tuple_element_t<Index, Tuple<TArgs...>>;
            fromJSONString<Type>(list.at(Index), std::get<Index>(value));
            if constexpr (Index + 1 < sizeof...(TArgs)) {
                fromStringTuple<Index + 1>(list, value);
            }
        }
        // fromString
        static void fromString(const string& str, Tuple<TArgs...>& value) {
            fromStringTuple<0>(JSONList(str), value);
        }
    };
}