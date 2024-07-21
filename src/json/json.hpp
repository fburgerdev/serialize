#pragma once
#include "string_utils.hpp"

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
        string toString() const;

        // iterate
        auto begin() { return m_list.begin(); }
        auto begin() const { return m_list.begin(); }
        auto end() { return m_list.end(); }
        auto end() const { return m_list.end(); }
    private:
        // list and indent
        List<Pair<string, string>> m_list;
    };
    // JSONList
    class JSONList {
    public:
        // constructor
        JSONList() = default;
        JSONList(const string& str);

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
        string toString() const;
    private:
        // list
        List<string> m_list;
    };
}