#pragma once
#include "common.hpp"

namespace ASST {
    // TypeString
    template<typename T>
    struct TypeString {
        string operator()() const {
            return typeid(T).name();
        }
    };

    // JoinedTypeString
    template<typename TFirst, typename... TRest>
    inline string JoinedTypeString() {
        if constexpr (sizeof...(TRest) > 0) {
            return TypeString<TFirst>()() + "," + JoinedTypeString<TRest...>();
        }
        else {
            return TypeString<TFirst>()();
        }
    }

    // primitive
    template<>
    struct TypeString<void> {
        string operator()() const {
            return "void";
        }
    };
    template<>
    struct TypeString<bool> {
        string operator()() const {
            return "bool";
        }
    };
    template<>
    struct TypeString<char> {
        string operator()() const {
            return "char";
        }
    };
    template<>
    struct TypeString<int> {
        string operator()() const {
            return "int";
        }
    };
    template<>
    struct TypeString<uint> {
        string operator()() const {
            return "uint";
        }
    };
    template<>
    struct TypeString<float> {
        string operator()() const {
            return "float";
        }
    };
    template<>
    struct TypeString<double> {
        string operator()() const {
            return "double";
        }
    };
    // std
    template<>
    struct TypeString<string> {
        string operator()() const {
            return "string";
        }
    };
    // :: container
    template<typename T, address N>
    struct TypeString<Array<T, N>> {
        string operator()() const {
            return "Array<" + TypeString<T>()() + "," + std::to_string(N) + ">";
        }
    };
    template<typename T>
    struct TypeString<List<T>> {
        string operator()() const {
            return "List<" + TypeString<T>()() + ">";
        }
    };
    template<typename T>
    struct TypeString<Stack<T>> {
        string operator()() const {
            return "Stack<" + TypeString<T>()() + ">";
        }
    };
    template<typename T>
    struct TypeString<Queue<T>> {
        string operator()() const {
            return "Queue<" + TypeString<T>()() + ">";
        }
    };
    template<typename T>
    struct TypeString<Deque<T>> {
        string operator()() const {
            return "Deque<" + TypeString<T>()() + ">";
        }
    };
    template<typename T>
    struct TypeString<Set<T>> {
        string operator()() const {
            return "Set<" + TypeString<T>()() + ">";
        }
    };
    template<typename K, typename V>
    struct TypeString<Map<K, V>> {
        string operator()() const {
            return "Map<" + TypeString<K>()() + "," + TypeString<V>()() + ">";
        }
    };
    template<typename T>
    struct TypeString<HashSet<T>> {
        string operator()() const {
            return "HashSet<" + TypeString<T>()() + ">";
        }
    };
    template<typename K, typename V>
    struct TypeString<HashMap<K, V>> {
        string operator()() const {
            return "HashMap<" + TypeString<K>()() + "," + TypeString<V>()() + ">";
        }
    };
    // utility
    template<typename T>
    struct TypeString<Optional<T>> {
        string operator()() const {
            return "Optional<" + TypeString<T>()() + ">";
        }
    };
    template<typename T1, typename T2>
    struct TypeString<Pair<T1, T2>> {
        string operator()() const {
            return "Pair<" + TypeString<T1>()() + "," + TypeString<T2>()() + ">";
        }
    };
    template<typename... TArgs>
    struct TypeString<Tuple<TArgs...>> {
        string operator()() const {
            return "Tuple<" + JoinedTypeString<TArgs...>() + ">";
        }
    };
    template<typename... TArgs>
    struct TypeString<Variant<TArgs...>> {
        string operator()() const {
            return "Variant<" + JoinedTypeString<TArgs...>() + ">";
        }
    };
}