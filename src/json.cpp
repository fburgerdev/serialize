#include "json.hpp"

namespace ASST {
    //* JSONObject
    // constructor
    JSONObject::JSONObject(const string& str) {
        List<string> splitted = split(str.substr(1, str.length() - 2), { ':', ',' });
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
        throw std::out_of_range("Key not found");
    }
    const string& JSONObject::at(const string& key) const {
        for (const auto& [entryKey, entryValue] : m_list) {
            if (entryKey == key) {
                return entryValue;
            }
        }
        throw std::out_of_range("Key not found");
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
    string JSONObject::toString(const string& indent) const {
        strstream stream;
        stream << '{' << '\n';
        for (auto it = m_list.begin(); it != m_list.end(); ++it) {
            stream << indent << "    " << '"' << it->first << '"' << ':' << ' ' << it->second;
            if (std::next(it) != m_list.end()) {
                stream << ',';
            }
            stream << '\n';
        }
        stream << indent << '}';
        return stream.str();
    }

    //* JSONList
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
    string JSONList::toString(const string& indent) const {
        if (m_list.empty()) {
            return "[ ]";
        }
        string sep = isMultiline() ? "\n" + indent : " ";
        string longsep = isMultiline() ? sep + "    " : " ";
        strstream stream;
        stream << '[' << longsep;
        for (auto it = m_list.begin(); it != m_list.end(); ++it) {
            stream << *it;
            if (std::next(it) != m_list.end()) {
                stream << ',' << longsep;
            }
        }
        stream << sep << ']';
        return stream.str();
    }
}