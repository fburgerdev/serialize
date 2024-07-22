#include "json.hpp"
#include "serializable.hpp"
#include "string_utils.hpp"

namespace ASST {
    //* JSONObject
    // constructor
    JSONObject::JSONObject(const string& str) {
        // ASSERT_MSG(str.length() >= 2 && (str.front() == '{' && str.back() == '}'), "JSON deserialization failed: expected '{}' to be a json object", str);
        List<string> splitted = split(str.substr(1, str.length() - 2), { ':', ',' });
        // ASSERT_MSG(splitted.size() % 2 == 0, "JSON deserialization failed: expected '{}' to be a json object", str);
        for (address i = 0; i < splitted.size(); i += 2) {
            m_list.emplace_back(splitted[i].substr(1, splitted[i].length() - 2), splitted[i + 1]);
        }
    }
    
    // access
    // :: at
    string& JSONObject::at(const string& key) {
        for (auto& [entryKey, entryValue] : m_list) {
            if (entryKey == key) {
                return entryValue;
            }
        }
        // ASSERT_MSG(false, "JSON deserialization failed: expected json object '{}' to have key '{}'", toString(), key);
    }
    const string& JSONObject::at(const string& key) const {
        for (const auto& [entryKey, entryValue] : m_list) {
            if (entryKey == key) {
                return entryValue;
            }
        }
        // ASSERT_MSG(false, "JSON deserialization failed: expected json object '{}' to have key '{}'", toString(), key);
    }
    // :: operator[]
    string& JSONObject::operator[](const string& key) {
        if (contains(key)) {
            return at(key);
        }
        else {
            m_list.emplace_back(key, "");
            return m_list.back().second;
        }
    }
    // :: contains
    bool JSONObject::contains(const string& key) const {
        for (auto& [entryKey, entryValue] : m_list) {
            if (entryKey == key) {
                return true;
            }
        }
        return false;
    }
    // :: size
    auto JSONObject::size() const {
        return m_list.size();
    }

    // toString
    string JSONObject::toString() const {
        strstream stream;
        stream << '{' << '\n';
        for (auto it = m_list.begin(); it != m_list.end(); ++it) {
            stream << "    " << '"' << it->first << '"' << ':' << ' ' << it->second;
            if (std::next(it) != m_list.end()) {
                stream << ',';
            }
            stream << '\n';
        }
        stream << '}';
        return stream.str();
    }

    //* JSONList
    // constructor
    JSONList::JSONList(const string& str) {
        // ASSERT_MSG(str.length() >= 2 && (str.front() == '[' && str.back() == ']'), "JSON deserialization failed: expected {} to be a json list", str);
        m_list = split(str.substr(1, str.length() - 2), { ',' });
    }
    // access
    // :: at
    string& JSONList::at(address index) {
        return m_list.at(index);
    }
    const string& JSONList::at(address index) const {
        return m_list.at(index);
    }
    // :: operator[]
    string& JSONList::operator[](address index) {
        return m_list[index];
    }
    // :: push
    void JSONList::push(const string& value) {
        m_list.push_back(value);
    }
    // :: size
    auto JSONList::size() const {
        return m_list.size();
    }
    // :: length
    address JSONList::length() const {
        return m_list.size();
    }

    // isMultiline
    bool JSONList::isMultiline() const {
        for (const string& item : m_list) {
            if (item.find('\n') != string::npos) {
                return true;
            }
        }
        return false;
    }
    // toString
    string JSONList::toString() const {
        if (m_list.empty()) {
            return "[ ]";
        }
        string sep = isMultiline() ? "\n" : " ";
        string longsep = isMultiline() ? "\n    " : " ";
        strstream stream;
        stream << '[' << longsep;
        for (auto it = m_list.begin(); it != m_list.end(); ++it) {
            stream << indent(*it);
            if (std::next(it) != m_list.end()) {
                stream << ',' << longsep;
            }
        }
        stream << sep << ']';
        return stream.str();
    }
}