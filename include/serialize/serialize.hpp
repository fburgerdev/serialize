#pragma once
// #include "common.hpp" (HPPMERGE)
#include <ranges> 
#include <memory> 
#include <string> 
#include <string_view> 
#include <array> 
#include <vector> 
#include <stack> 
#include <queue> 
#include <deque> 
#include <unordered_set> 
#include <map> 
#include <set> 
#include <unordered_map> 
#include <functional> 
#include <optional> 
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <mutex> 
#include <shared_mutex> 
#include <atomic> 
namespace ASST {
    namespace stdr = std::ranges;
    using address = std::size_t;
    using uchar = unsigned char;
    using int8 = std::int8_t;
    using int16 = std::int16_t;
    using int32 = std::int32_t;
    using int64 = std::int64_t;
    using uint = unsigned int;
    using uint8 = std::uint8_t;
    using uint16 = std::uint16_t;
    using uint32 = std::uint32_t;
    using uint64 = std::uint64_t;
    using string = std::string;
    using strview = std::string_view;
    template<typename T, address N>
    using Array = std::array<T, N>;
    template<typename T>
    using List = std::vector<T>;
    template<typename T>
    using Stack = std::stack<T>;
    template<typename T>
    using Queue = std::queue<T>;
    template<typename T>
    using Deque = std::deque<T>;
    template<typename T>
    using Set = std::set<T>;
    template<typename Key, typename Value>
    using Map = std::map<Key, Value>;
    template<typename T>
    using HashSet = std::unordered_set<T>;
    template<typename Key, typename Value>
    using HashMap = std::unordered_map<Key, Value>;
    using std::forward;
    using std::move;
    template<class T, class... Args>
    auto makeUniquePtr(Args&&... args) {
        return std::make_unique<T>(forward(args)...);
    }
    template<class T, class... Args>
    auto makeSharedPtr(Args&&... args) {
        return std::make_shared<T>(forward(args)...);
    }
    template<typename T>
    using UniquePtr = std::unique_ptr<T>;
    template<typename T>
    using SharedPtr = std::shared_ptr<T>;
    template<typename T>
    using WeakPtr = std::weak_ptr<T>;
    using std::function;
    template<typename T>
    using Opt = std::optional<T>;
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::fstream;
    using std::ifstream;
    using std::ofstream;
    using strstream = std::stringstream;
    using std::mutex;
    using std::recursive_mutex;
    using std::shared_mutex;
    template<typename Mutex>
    using UniqueLock = std::unique_lock<Mutex>;
    template<typename Mutex>
    using SharedLock = std::shared_lock<Mutex>;
    using atomic_address = std::atomic_size_t;
    using atomic_int = std::atomic_int;
    using atomic_int8 = std::atomic_int8_t;
    using atomic_int16 = std::atomic_int16_t;
    using atomic_int32 = std::atomic_int32_t;
    using atomic_int64 = std::atomic_int64_t;
    using atomic_uint = std::atomic_uint;
    using atomic_uint8 = std::atomic_uint8_t;
    using atomic_uint16 = std::atomic_uint16_t;
    using atomic_uint32 = std::atomic_uint32_t;
    using atomic_uint64 = std::atomic_uint64_t;
}
// #include "concept.hpp" (HPPMERGE)
#include <concepts>
namespace ASST {
    struct VoidReflector {
        template<typename T>
        void reflect(const string& str, const T& value) {
        }
    };
    template<typename T>
    concept NumericType= std::integral<T> || std::floating_point<T>;
    template<class T>
    concept StringType = std::is_convertible_v<T, strview>;
    template<typename T>
    concept IterableType = requires(T x, const T y) {
        { x.begin() };
        { x.end() };
        { y.begin() };
        { y.end() };
    };
    template<typename T>
    concept ReflectableType = requires(T x, VoidReflector reflector) {
        { x.reflect(reflector) };
    };
    template<typename T>
    constexpr bool isPair = false;
    template<typename T, typename U>
    constexpr bool isPair<std::pair<T, U>> = true;
}
// #include "string.hpp" (HPPMERGE)
namespace ASST {
    string stringReplace(string source, const string& from, const string& to);
    List<string> split(const string& source, Set<char> delimiters);
    string removeWhitespaces(const string& source);
}
// #include "json.hpp" (HPPMERGE)
namespace ASST {
    class JSONObject {
    public:
        JSONObject() = default;
        JSONObject(const string& str);
        string& at(const string& key);
        const string& at(const string& key) const;
        string& operator[](const string& key);
        bool contains(const string& key) const;
        auto size() const;
        string toString(const string& indent = "") const;
    private:
        List<std::pair<string, string>> m_list;
    };
    class JSONList {
    public:
        string& at(address index);
        const string& at(address index) const;
        string& operator[](address index);
        void push(const string& value);
        auto size() const;
        bool isMultiline() const;
        string toString(const string& indent = "") const;
    private:
        List<string> m_list;
    };
}
// #include "json_serializer.hpp" (HPPMERGE)
namespace ASST {
    class JSONSerializer {
    public:
        class WriteReflector {
        public:
            WriteReflector(const string& indent = "")
                : indent(indent) {}
            template<typename T>
            void record(const string& key, const T& value) {
                m_object[key] = JSONSerializer::toString<T>(value, indent + "    ");
            }
            string toString() const {
                return m_object.toString(indent);
            }
        private:
            JSONObject m_object;
            string indent;
        };
        template<NumericType T>
        static string toString(T value, const string& indent = "") {
            string str = std::to_string(value);
            str.erase(str.find_last_not_of('0') + 1, string::npos);
            str.erase(str.find_last_not_of('.') + 1, string::npos);
            return str;
        }
        template<StringType T>
        static string toString(const T& str, const string& indent = "") {
            return "\"" + str + "\"";
        }
        static string toString(std::nullptr_t null, const string& indent = "") {
            return "null";
        }
        template<typename T1, typename T2>
        static string toString(const std::pair<T1, T2>& pair, const string& indent = "") {
            JSONList list;
            list.push(toString(pair.first, indent + "    "));
            list.push(toString(pair.second, indent + "    "));
            return list.toString(indent);
        }
        template<IterableType T> requires (IterableType<T> && !StringType<T>)
        static string toString(const T& range, const string& indent = "") {
            JSONList list;
            for (const auto& item : range) {
                list.push(toString(item, indent + "    "));
            }
            return list.toString(indent);
        }
        template<typename T> requires ReflectableType<T>
        static string toString(const T& value, const string& indent = "") {
            WriteReflector reflector(indent);
            const_cast<T&>(value).reflect(reflector);
            return reflector.toString();
        }
        template<typename T>
        static void serialize(const string& filepath, const T& value) {
            ofstream(filepath) << toString(value);
        }
        class ReadReflector {
        public:
            ReadReflector(const string& str)
                : m_object(str) {}
            template<typename T>
            void record(const string& key, T& value) {
                value = JSONSerializer::fromString<T>(m_object.at(key));
            }
        private:
            JSONObject m_object;
        };
        template<typename T> requires NumericType<T>
        static T fromString(const string& str) {
            T data;
            std::istringstream(str) >> data;
            return data;
        }
        template<typename T> requires std::same_as<T, string>
        static T fromString(const string& str) {
            return str.substr(1, str.length() - 2);
        }
        template<typename T> requires std::same_as<T, std::nullptr_t>
        static T fromString(const string& str) {
            return nullptr;
        }
        template<typename T> requires isPair<T>
        static std::pair<typename T::first_type, typename T::second_type> fromString(const string& str) {
            List<string> splitted = split(str.substr(1, str.length() - 2), { ',' });
            return { fromString<typename T::first_type>(splitted[0]), fromString<typename T::second_type>(splitted[1]) };
        }
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
        template<typename T> requires ReflectableType<T>
        static T fromString(const string& str) {
            ReadReflector reflector(str);
            T value;
            value.reflect(reflector);
            return value;
        }
        template<typename T>
        static T deserialize(const string& filepath) {
            string source = (strstream() << ifstream(filepath).rdbuf()).str();
            return fromString<T>(removeWhitespaces(source));
        }
    };
}