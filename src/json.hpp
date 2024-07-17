#pragma once
#include "string.hpp"

namespace ASST {
    // JSONObject
    class JSONObject {
    public:
        // constructor
        JSONObject() = default;
        JSONObject(const string& str);
        
        // access
        // :: at
        string& at(const string& key);
        const string& at(const string& key) const;
        // :: operator[]
        string& operator[](const string& key);
        // :: contains
        bool contains(const string& key) const;
        // :: size
        auto size() const;

        // toString
        string toString(const string& indent = "") const;
    private:
        // list and indent
        List<std::pair<string, string>> m_list;
    };
    // JSONList
    class JSONList {
    public:
        // access
        // :: at
        string& at(address index);
        const string& at(address index) const;
        // :: operator[]
        string& operator[](address index);
        // :: push
        void push(const string& value);
        auto size() const;
        
        // isMultiline
        bool isMultiline() const;
        // toString
        string toString(const string& indent = "") const;
    private:
        // list
        List<string> m_list;
    };
}