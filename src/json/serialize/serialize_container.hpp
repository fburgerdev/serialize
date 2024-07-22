#pragma once
#include "json/serializable.hpp"

namespace ASST {
    // isArray
    template<typename T>
    constexpr bool isArray = false;
    template<typename T, address N>
    constexpr bool isArray<Array<T, N>> = true;
    // isList
    template<typename T>
    constexpr bool isList = false;
    template<typename T>
    constexpr bool isList<List<T>> = true;
    // isStack
    template<typename T>
    constexpr bool isStack = false;
    template<typename T>
    constexpr bool isStack<Stack<T>> = true;
    // isQueue
    template<typename T>
    constexpr bool isQueue = false;
    template<typename T>
    constexpr bool isQueue<Queue<T>> = true;
    // isDeque
    template<typename T>
    constexpr bool isDeque = false;
    template<typename T>
    constexpr bool isDeque<Deque<T>> = true;
    // isSet
    template<typename T>
    constexpr bool isSet = false;
    template<typename T>
    constexpr bool isSet<Set<T>> = true;
    // isMap
    template<typename T>
    constexpr bool isMap = false;
    template<typename K, typename V>
    constexpr bool isMap<Map<K, V>> = true;
    // isHashSet
    template<typename T>
    constexpr bool isHashSet = false;
    template<typename T>
    constexpr bool isHashSet<HashSet<T>> = true;
    // isHashMap
    template<typename T>
    constexpr bool isHashMap = false;
    template<typename K, typename V>
    constexpr bool isHashMap<HashMap<K, V>> = true;

    // isSequential
    template<typename T>
    constexpr bool isSequential = (isArray<T> || isList<T> || isStack<T> || isQueue<T> || isDeque<T>);
    // isAssociative
    template<typename T>
    constexpr bool isAssociative = (isSet<T> || isMap<T>);
    // isUnordered
    template<typename T>
    constexpr bool isUnordered = (isHashSet<T> || isHashMap<T>);
    // isContainer
    template<typename T>
    constexpr bool isContainer = (isSequential<T> || isAssociative<T> || isUnordered<T>);

    // JSONSerializable
    template<typename T> requires isContainer<T>
    struct JSONSerializable<T> {
        // toString
        static string toString(const T& value) {
            JSONList list;
            for (const auto& item : value) {
                if constexpr (isMap<T>) {
                    using Key = std::remove_const_t<typename T::value_type::first_type>;
                    using Value = typename T::value_type::second_type;
                    list.push(toJSONString<Pair<Key, Value>>(item));
                }
                else if constexpr (isHashMap<T>) {
                    using Key = std::remove_const_t<typename T::value_type::first_type>;
                    using Value = typename T::value_type::second_type;
                    list.push(toJSONString<Pair<Key, Value>>(item));
                }
                else {
                    list.push(toJSONString<typename T::value_type>(item));
                }
            }
            return list.toString();
        }

        // fromString
        static void fromString(const string& str, T& value) {
            // ASSERT_JSON_DESERIALIZE(str.length() >= 2 && (str.front() == '[' && str.back() == ']'), str, (TypeString<T>()()));
            List<string> splitted = split(str.substr(1, str.length() - 2), { ',' });
            for (address index = 0; index < splitted.size(); ++index) {
                if constexpr (isMap<T>) {
                    using Key = std::remove_const_t<typename T::value_type::first_type>;
                    using Value = typename T::value_type::second_type;
                    value.insert(fromJSONString<Pair<Key, Value>>(splitted[index]));
                }
                else if constexpr (isHashMap<T>) {
                    using Key = std::remove_const_t<typename T::value_type::first_type>;
                    using Value = typename T::value_type::second_type;
                    value.insert(fromJSONString<Pair<Key, Value>>(splitted[index]));
                }
                else {
                    auto item = fromJSONString<typename T::value_type>(splitted[index]);
                    if constexpr (isArray<T>) {
                        value[index] = item;
                    }
                    if constexpr (isList<T>) {
                        value.emplace_back(item);
                    }
                    if constexpr (isStack<T>) {
                        value.emplace(item);
                    }
                    if constexpr (isQueue<T>) {
                        value.emplace(item);
                    }
                    if constexpr (isDeque<T>) {
                        value.emplace_back(item);
                    }
                    if constexpr (isSet<T>) {
                        value.emplace(item);
                    }
                    if constexpr (isHashSet<T>) {
                        value.emplace(item);
                    }
                }
            }
        }
    };
}