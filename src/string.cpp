#include "string.hpp"

namespace ASST {
    // stringReplace
    string stringReplace(string source, const string& from, const string& to) {
        address index = 0;
        while (true) {
            index = source.find(from, index);
            if (index == string::npos) {
                break;
            }
            source.replace(index, from.length(), to);
            index += to.length();
        }
        return source;
    }
    // split
    List<string> split(const string& source, Set<char> delimiters) {
        List<string> result = {""};
        int scope = 0;
        bool inString = false;
        for (address i = 0; i < source.length(); ++i) {
            char ch = source[i];
            if (!inString) {

                if (ch == '[' || ch == '{') {
                    ++scope;
                }
                if (ch == ']' || ch == '}') {
                    --scope;
                }
            }
            if (ch == '"' && (i == 0 || source[i - 1] != '\\')) {
                inString = !inString;
            }
            if (scope == 0 && !inString && delimiters.contains(ch)) {
                result.emplace_back();
            }
            else {
                result.back().push_back(ch);
            }
        }
        if (result.back().empty()) {
            result.pop_back();
        }
        return result;
    }
    // removeWhitespaces
    string removeWhitespaces(const string& source) {
        string result;
        bool inString = false;
        for (address i = 0; i < source.length(); ++i) {
            char ch = source[i];
            if (ch == '"' && (i == 0 || source[i - 1] != '\\')) {
                inString = !inString;
            }
            if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\f') {
                continue;
            }
            else {
                result.push_back(ch);
            }
        }
        return result;
    }
    // indent
    string indent(const string& source) {
        return stringReplace(source, "\n", "\n    ");
    }
}