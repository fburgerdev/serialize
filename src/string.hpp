#pragma once
#include "common.hpp"

namespace ASST {
    // stringReplace
    string stringReplace(string source, const string& from, const string& to);
    // split
    List<string> split(const string& source, Set<char> delimiters);
    // removeWhitespaces
    string removeWhitespaces(const string& source);
    // indent
    string indent(const string& source);

    // EscapeSequences
    inline const List<Pair<string, string>> EscapeSequences = {
        { "\\", "\\\\" },
        { "\'", "\\\'" },
        { "\"", "\\\"" },
        { "\?", "\\\?" },
        { "\a", "\\a" },
        { "\b", "\\b" },
        { "\f", "\\f" },
        { "\n", "\\n" },
        { "\r", "\\r" },
        { "\v", "\\v" },
    };
}