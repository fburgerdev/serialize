#pragma once
#include "common.hpp"

namespace ASST {
    template<typename T>
    static inline string TypeString = typeid(T).name();

    // primitive
    template<>
    string TypeString<void> = "void";
    template<>
    string TypeString<bool> = "bool";
    template<>
    string TypeString<char> = "char";
    template<>
    string TypeString<int> = "int";
    template<>
    string TypeString<uint> = "uint";
    template<>
    string TypeString<float> = "float";
    template<>
    string TypeString<double> = "double";
    // std
    template<>
    string TypeString<string> = "string";
    template<typename T>
    string TypeString<List<T>> = "List<" + TypeString<T> + ">";
    template<typename K, typename V>
    string TypeString<Map<K, V>> = "Map<" + TypeString<K> + "," + TypeString<V> + ">";
}