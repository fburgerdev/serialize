#pragma once
#include "type_string.hpp"

namespace ASST {
    // SerializationTrace
    class SerializationTrace {
    public:
        // constructor
        SerializationTrace(const string& str, const string& type) {
            m_error = "JSON deserialization failed: expected '" + str + "' to be of type '" + type +  "'";
        }
        // pushTrace
        void pushTrace(const string& str, const string& type) {
            m_list.emplace_back("in '" + str + "' of type '" + type + "'");
        }
        // toString
        string toString() const {
            ostrstream sstream;
            sstream << m_error << endl;
            sstream << "Stack trace:" << endl;  // TODO: Add stack trace
            sstream << "---" << endl;
            for (const string& str : m_list) {
                sstream << str << endl;
            }
            return sstream.str();
        }
        // // what
        // virtual const char* what() const noexcept override {
        //     string str = toString();
        //     char* cStr = new char[str.length() + 1];
        //     return strcpy(cStr, str.c_str());
        // }
    private:
        // list
        string m_error;
        List<string> m_list;
    };
}