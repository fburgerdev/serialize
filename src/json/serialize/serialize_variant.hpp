#pragma once
#include "json/serializable.hpp"
#include "type_string.hpp"

namespace ASST {
    // JSONSerializable
    template<typename... TArgs>
    struct JSONSerializable<std::variant<TArgs...>> {
        // toStringVariant
        template<address Index>
        static string toStringVariant(const std::variant<TArgs...>& variant) {
            using Type = std::variant_alternative_t<Index, std::variant<TArgs...>>;
            if (std::holds_alternative<Type>(variant)) {
                return toJSONString<Pair<string, Type>>({ TypeString<Type>()(), std::get<Type>(variant) });
            }
            else {
                if constexpr (Index + 1 < sizeof...(TArgs)) {
                    return toStringVariant<Index + 1>(variant);
                }
                else {
                    throw std::exception();
                }
            }
        }
        // toString
        static string toString(const std::variant<TArgs...>& value) {
            return toStringVariant<0>(value);
        }

        // fromStringVariant
        template<address Index>
        static std::variant<TArgs...> fromStringVariant(const string& type, const string& value) {
            using Type = std::variant_alternative_t<Index, std::variant<TArgs...>>;
            if (type == TypeString<Type>()()) {
                return fromJSONString<Type>(value);
            }
            else {
                if constexpr (Index + 1 < sizeof...(TArgs)) {
                    return fromStringVariant<Index + 1>(type, value);
                }
                else {
                    throw std::exception();
                }
            }
        }
        // fromString
        static void fromString(const string& str, std::variant<TArgs...>& data) {
            List<string> splitted = split(str.substr(1, str.length() - 2), { ',' });
            data = fromStringVariant<0>(fromJSONString<string>(splitted[0]), splitted[1]);
        }
    };
}