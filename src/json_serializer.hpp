#pragma once
#include "json.hpp"
#include "concept.hpp"

namespace ASST {
    // JSONSerializer
    class JSONSerializer {
    public:
        //* serialize
        // WriteReflector
        class WriteReflector {
        public:
            // constructor
            WriteReflector(const string& indent = "")
                : indent(indent) {}
            // record
            template<typename T>
            void record(const string& key, const T& value) {
                m_object[key] = JSONSerializer::toString<T>(value, indent + "    ");
            }
            // toString
            string toString() const {
                return m_object.toString(indent);
            }
        private:
            // json object
            JSONObject m_object;
            string indent;
        };

        // toString
        // :: numeric
        template<NumericType T>
        static string toString(T value, const string& indent = "") {
            string str = std::to_string(value);
            str.erase(str.find_last_not_of('0') + 1, string::npos);
            str.erase(str.find_last_not_of('.') + 1, string::npos);
            return str;
        }
        // :: string
        template<StringType T>
        static string toString(const T& str, const string& indent = "") {
            return "\"" + str + "\"";
        }
        // :: null
        static string toString(std::nullptr_t null, const string& indent = "") {
            return "null";
        }
        // :: pair
        template<typename T1, typename T2>
        static string toString(const std::pair<T1, T2>& pair, const string& indent = "") {
            JSONList list;
            list.push(toString(pair.first, indent + "    "));
            list.push(toString(pair.second, indent + "    "));
            return list.toString(indent);
        }
        // :: iterable
        template<IterableType T> requires (IterableType<T> && !StringType<T>)
        static string toString(const T& range, const string& indent = "") {
            JSONList list;
            for (const auto& item : range) {
                list.push(toString(item, indent + "    "));
            }
            return list.toString(indent);
        }
        // :: custom
        template<typename T> requires ReflectableType<T>
        static string toString(const T& value, const string& indent = "") {
            WriteReflector reflector(indent);
            const_cast<T&>(value).reflect(reflector);
            return reflector.toString();
        }

        // serialize
        template<typename T>
        static void serialize(const string& filepath, const T& value) {
            ofstream(filepath) << toString(value);
        }

        //* deserialize
        // ReadReflector
        class ReadReflector {
        public:
            // constructor
            ReadReflector(const string& str)
                : m_object(str) {}
            // record
            template<typename T>
            void record(const string& key, T& value) {
                value = JSONSerializer::fromString<T>(m_object.at(key));
            }
        private:
            // json object
            JSONObject m_object;
        };
        // fromString
        // :: numeric
        template<typename T> requires NumericType<T>
        static T fromString(const string& str) {
            T data;
            std::istringstream(str) >> data;
            return data;
        }
        // :: string
        template<typename T> requires std::same_as<T, string>
        static T fromString(const string& str) {
            return str.substr(1, str.length() - 2);
        }
        // :: null
        template<typename T> requires std::same_as<T, std::nullptr_t>
        static T fromString(const string& str) {
            return nullptr;
        }
        // :: pair
        template<typename T> requires isPair<T>
        static std::pair<typename T::first_type, typename T::second_type> fromString(const string& str) {
            List<string> splitted = split(str.substr(1, str.length() - 2), { ',' });
            return { fromString<typename T::first_type>(splitted[0]), fromString<typename T::second_type>(splitted[1]) };
        }
        // :: iterable
        template<typename T, address N>
        static void appendValue(Array<T, N>& array, const string& str, address index) {
            array[index] = fromString<T>(str);
        }
        template<typename T>
        static void appendValue(List<T>& list, const string& str, address index) {
            list.emplace_back(fromString<T>(str));
        }
        template<typename T>
        static void appendValue(Stack<T>& stack, const string& str, address index) {
            stack.emplace(fromString<T>(str));
        }
        template<typename T>
        static void appendValue(Queue<T>& queue, const string& str, address index) {
            queue.emplace(fromString<T>(str));
        }
        template<typename T>
        static void appendValue(Deque<T>& deque, const string& str, address index) {
            deque.emplace_back(fromString<T>(str));
        }
        template<typename T>
        static void appendValue(Set<T>& set, const string& str, address index) {
            set.emplace(fromString<T>(str));
        }
        template<typename K, typename V>
        static void appendValue(Map<K, V>& map, const string& str, address index) {
            map.insert(fromString<std::pair<K, V>>(str));
        }
        template<typename T>
        static void appendValue(HashSet<T>& hashset, const string& str, address index) {
            hashset.emplace(fromString<T>(str));
        }
        template<typename K, typename V>
        static void appendValue(HashMap<K, V>& hashmap, const string& str, address index) {
            hashmap.insert(fromString<std::pair<K, V>>(str));
        }
        template<typename T> requires (IterableType<T> && !StringType<T>)
        static T fromString(const string& str) {
            T out;
            List<string> splitted = split(str.substr(1, str.length() - 2), { ',' });
            for (address i = 0; i < splitted.size(); ++i) {
                appendValue(out, splitted[i], i);
            }
            return out;
        }
        // :: custom
        template<typename T> requires ReflectableType<T>
        static T fromString(const string& str) {
            ReadReflector reflector(str);
            T value;
            value.reflect(reflector);
            return value;
        }

        // deserialize
        template<typename T>
        static T deserialize(const string& filepath) {
            string source = (strstream() << ifstream(filepath).rdbuf()).str();
            return fromString<T>(removeWhitespaces(source));
        }
    };
}