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
#include <variant> 
#include <tuple> 
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <mutex> 
#include <shared_mutex> 
#include <atomic> 
namespace ASST {
    namespace stdr = std::ranges;
    using address = std::size_t;
    using schar = signed char;
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
    template<typename T>
    using Optional = std::optional<T>;
    template<typename T1, typename T2>
    using Pair = std::pair<T1, T2>;
    template<typename... TArgs>
    using Tuple = std::tuple<TArgs...>;
    template<typename... TArgs>
    using Variant = std::variant<TArgs...>;
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
        return std::make_unique<T>(forward<Args...>(args)...);
    }
    template<class T, class... Args>
    auto makeSharedPtr(Args&&... args) {
        return std::make_shared<T>(forward<Args...>(args)...);
    }
    template<typename T>
    using UniquePtr = std::unique_ptr<T>;
    template<typename T>
    using SharedPtr = std::shared_ptr<T>;
    template<typename T>
    using WeakPtr = std::weak_ptr<T>;
    using std::function;
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::fstream;
    using std::ifstream;
    using std::ofstream;
    using strstream = std::stringstream;
    using istrstream = std::istringstream;
    using ostrstream = std::ostringstream;
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
// #include "logging.hpp" (HPPMERGE)
#if defined(BEAVER_LOGGING)
#include "beaver/beaver.hpp"
#else
#define LOG_TRACE(...)
#define LOG_DEBUG(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_FATAL(...)
#define ASSERT(...)
#define ASSERT_MSG(...)
#endif
// #include "string_utils.hpp" (HPPMERGE)
namespace ASST {
    inline List<string> split(const string& source, Set<char> delimiters) {
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
        if (result.size() == 1 && result.back().empty()) {
            return {};
        }
        return result;
    }
    // replace
    inline string replace(string source, const string& from, const string& to) {
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
    // removeWS
    inline string removeWS(const string& source) {
        string result;
        bool inString = false;
        for (address i = 0; i < source.length(); ++i) {
            char ch = source[i];
            if (ch == '"' && (i == 0 || source[i - 1] != '\\')) {
                inString = !inString;
            }
            if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v' || ch == '\f') {
                continue;
            }
            else {
                result.push_back(ch);
            }
        }
        return result;
    }
    inline string indent(const string& source) {
        return replace(source, "\n", "\n    ");
    }
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
        string toString() const;
        auto begin() { return m_list.begin(); }
        auto begin() const { return m_list.begin(); }
        auto end() { return m_list.end(); }
        auto end() const { return m_list.end(); }
    private:
        List<Pair<string, string>> m_list;
    };
    class JSONList {
    public:
        JSONList() = default;
        JSONList(const string& str);
        string& at(address index);
        const string& at(address index) const;
        string& operator[](address index);
        void push(const string& value);
        auto size() const;
        address length() const;
        bool isMultiline() const;
        string toString() const;
    private:
        List<string> m_list;
    };
}
// #include "type_string.hpp" (HPPMERGE)
namespace ASST {
    template<typename T>
    struct TypeString {
        string operator()() const {
            return typeid(T).name();
        }
    };
    template<typename TFirst, typename... TRest>
    inline string JoinedTypeString() {
        if constexpr (sizeof...(TRest) > 0) {
            return TypeString<TFirst>()() + "," + JoinedTypeString<TRest...>();
        }
        else {
            return TypeString<TFirst>()();
        }
    }
    template<>
    struct TypeString<void> {
        string operator()() const {
            return "void";
        }
    };
    template<>
    struct TypeString<bool> {
        string operator()() const {
            return "bool";
        }
    };
    template<>
    struct TypeString<char> {
        string operator()() const {
            return "char";
        }
    };
    template<>
    struct TypeString<signed char> {
        string operator()() const {
            return "signed char";
        }
    };
    template<>
    struct TypeString<unsigned char> {
        string operator()() const {
            return "unsigned char";
        }
    };
    template<>
    struct TypeString<int16_t> {
        string operator()() const {
            return "int16_t";
        }
    };
    template<>
    struct TypeString<uint16_t> {
        string operator()() const {
            return "uint16_t";
        }
    };
    template<>
    struct TypeString<int32_t> {
        string operator()() const {
            return "int32_t";
        }
    };
    template<>
    struct TypeString<uint32_t> {
        string operator()() const {
            return "uint32_t";
        }
    };
    template<>
    struct TypeString<int64_t> {
        string operator()() const {
            return "int64_t";
        }
    };
    template<>
    struct TypeString<uint64_t> {
        string operator()() const {
            return "uint64_t";
        }
    };
    template<>
    struct TypeString<float> {
        string operator()() const {
            return "float";
        }
    };
    template<>
    struct TypeString<double> {
        string operator()() const {
            return "double";
        }
    };
    template<>
    struct TypeString<string> {
        string operator()() const {
            return "string";
        }
    };
    template<typename T, address N>
    struct TypeString<Array<T, N>> {
        string operator()() const {
            return "Array<" + TypeString<T>()() + "," + std::to_string(N) + ">";
        }
    };
    template<typename T>
    struct TypeString<List<T>> {
        string operator()() const {
            return "List<" + TypeString<T>()() + ">";
        }
    };
    template<typename T>
    struct TypeString<Stack<T>> {
        string operator()() const {
            return "Stack<" + TypeString<T>()() + ">";
        }
    };
    template<typename T>
    struct TypeString<Queue<T>> {
        string operator()() const {
            return "Queue<" + TypeString<T>()() + ">";
        }
    };
    template<typename T>
    struct TypeString<Deque<T>> {
        string operator()() const {
            return "Deque<" + TypeString<T>()() + ">";
        }
    };
    template<typename T>
    struct TypeString<Set<T>> {
        string operator()() const {
            return "Set<" + TypeString<T>()() + ">";
        }
    };
    template<typename K, typename V>
    struct TypeString<Map<K, V>> {
        string operator()() const {
            return "Map<" + TypeString<K>()() + "," + TypeString<V>()() + ">";
        }
    };
    template<typename T>
    struct TypeString<HashSet<T>> {
        string operator()() const {
            return "HashSet<" + TypeString<T>()() + ">";
        }
    };
    template<typename K, typename V>
    struct TypeString<HashMap<K, V>> {
        string operator()() const {
            return "HashMap<" + TypeString<K>()() + "," + TypeString<V>()() + ">";
        }
    };
    template<typename T>
    struct TypeString<Optional<T>> {
        string operator()() const {
            return "Optional<" + TypeString<T>()() + ">";
        }
    };
    template<typename T1, typename T2>
    struct TypeString<Pair<T1, T2>> {
        string operator()() const {
            return "Pair<" + TypeString<T1>()() + "," + TypeString<T2>()() + ">";
        }
    };
    template<typename... TArgs>
    struct TypeString<Tuple<TArgs...>> {
        string operator()() const {
            return "Tuple<" + JoinedTypeString<TArgs...>() + ">";
        }
    };
    template<typename... TArgs>
    struct TypeString<Variant<TArgs...>> {
        string operator()() const {
            return "Variant<" + JoinedTypeString<TArgs...>() + ">";
        }
    };
}
// #include "trace.hpp" (HPPMERGE)
namespace ASST {
    class SerializationTrace {
    public:
        SerializationTrace(const string& str, const string& type) {
            m_error = "JSON deserialization failed: expected '" + str + "' to be of type '" + type +  "'";
        }
        void pushTrace(const string& str, const string& type) {
            m_list.emplace_back("in '" + str + "' of type '" + type + "'");
        }
        string toString() const {
            ostrstream sstream;
            sstream << m_error << endl;
            sstream << "Stack trace:" << endl;  
            sstream << "---" << endl;
            for (const string& str : m_list) {
                sstream << str << endl;
            }
            return sstream.str();
        }
    private:
        string m_error;
        List<string> m_list;
    };
}
// #include "serializable.hpp" (HPPMERGE)
namespace ASST {
    template<typename T>
    struct JSONSerializable;
    template<typename T>
    string toJSONString(const T& value) {
        return JSONSerializable<T>::toString(value);
    }
    template<typename T>
    void fromJSONString(const string& str, T& value) {
        JSONSerializable<T>::fromString(str, value);
    }
    template<typename T>
    T fromJSONString(const string& str) {
        T value;
        fromJSONString<T>(str, value);
        return value;
    }
    #define ASSERT_JSON_DESERIALIZE(COND, STR, TYPE) ASSERT_MSG(COND, "JSON deserialization failed: expected '{}' to be of type '{}'", STR, TYPE); 
}
// #include "serializer.hpp" (HPPMERGE)
namespace ASST {
    class JSONSerializer {
    public:
        template<typename T>
        static void serialize(const string& filepath, const T& value) {
            ofstream(filepath) << toJSONString<T>(value);
        }
        template<typename T>
        static T deserialize(const string& filepath) {
            string source = (strstream() << ifstream(filepath).rdbuf()).str();
            try {
                T data = fromJSONString<T>(removeWS(source));
                return data;
            }
            catch (const SerializationTrace& trace) {
                LOG_FATAL(trace.toString());
                throw;
            }
        }
    };
}
// #include "serialize_primitive.hpp" (HPPMERGE)
namespace ASST {
    template<>
    struct JSONSerializable<bool> {
        static string toString(const bool& value) {
            return (value ? "true" : "false");
        }
        static void fromString(const string& str, bool& value) {
            value = (str == "true");
        }
    };
    template<typename T> requires std::same_as<T, char>
    struct JSONSerializable<T> {
        static string toString(const T& value) {
            return toJSONString<string>(string({ value }));
        }
        static void fromString(const string& str, T& value) {
            value = fromJSONString<string>(str).front();
        }
    };
    template<typename T> requires ((std::integral<T> || std::floating_point<T>) && !std::same_as<T, char>)
    struct JSONSerializable<T> {
        static string toString(const T& value) {
            if constexpr (std::is_same_v<T, schar>) {
                return (ostrstream() << static_cast<int>(value)).str();
            }
            else if constexpr (std::is_same_v<T, uchar>) {
                return (ostrstream() << static_cast<uint>(value)).str();
            }
            else {
                return (ostrstream() << value).str();
            }
        }
        static void fromString(const string& str, T& value) {
            if constexpr (std::is_floating_point_v<T>) {
                value = static_cast<T>(std::stold(str));
            }
            else if constexpr (std::is_unsigned_v<T>) {
                value = static_cast<T>(std::stoull(str));
            }
            else if constexpr (std::is_signed_v<T>) {
                value = static_cast<T>(std::stoll(str));
            }
        }
    };
}
// #include "serialize_string.hpp" (HPPMERGE)
namespace ASST {
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
    template<typename T> requires std::same_as<T, string>
    struct JSONSerializable<T> {
        static string toString(const T& value) {
            string str(value);
            for (const auto& [from, to] : EscapeSequences) {
                str = replace(str, from, to);
            }
            return "\"" + str + "\"";
        }
        static void fromString(const string& str, T& value) {
            value = str.substr(1, str.length() - 2);
            for (const auto& [to, from] : EscapeSequences) {
                value = replace(value, from, to);
            }
        }
    };
}
// #include "serialize_pair.hpp" (HPPMERGE)
namespace ASST {
    template<typename T1, typename T2>
    struct JSONSerializable<Pair<T1, T2>> {
        static string toString(const Pair<T1, T2>& value) {
            JSONList list;
            list.push(toJSONString<T1>(value.first));
            list.push(toJSONString<T2>(value.second));
            return list.toString();
        }
        static void fromString(const string& str, Pair<T1, T2>& value) {
            List<string> splitted = split(str.substr(1, str.length() - 2), { ',' });
            fromJSONString<T1>(splitted[0], value.first);
            fromJSONString<T2>(splitted[1], value.second);
        }
    };
}
// #include "serialize_container.hpp" (HPPMERGE)
namespace ASST {
    template<typename T>
    constexpr bool isArray = false;
    template<typename T, address N>
    constexpr bool isArray<Array<T, N>> = true;
    template<typename T>
    constexpr bool isList = false;
    template<typename T>
    constexpr bool isList<List<T>> = true;
    template<typename T>
    constexpr bool isStack = false;
    template<typename T>
    constexpr bool isStack<Stack<T>> = true;
    template<typename T>
    constexpr bool isQueue = false;
    template<typename T>
    constexpr bool isQueue<Queue<T>> = true;
    template<typename T>
    constexpr bool isDeque = false;
    template<typename T>
    constexpr bool isDeque<Deque<T>> = true;
    template<typename T>
    constexpr bool isSet = false;
    template<typename T>
    constexpr bool isSet<Set<T>> = true;
    template<typename T>
    constexpr bool isMap = false;
    template<typename K, typename V>
    constexpr bool isMap<Map<K, V>> = true;
    template<typename T>
    constexpr bool isHashSet = false;
    template<typename T>
    constexpr bool isHashSet<HashSet<T>> = true;
    template<typename T>
    constexpr bool isHashMap = false;
    template<typename K, typename V>
    constexpr bool isHashMap<HashMap<K, V>> = true;
    template<typename T>
    constexpr bool isSequential = (isArray<T> || isList<T> || isStack<T> || isQueue<T> || isDeque<T>);
    template<typename T>
    constexpr bool isAssociative = (isSet<T> || isMap<T>);
    template<typename T>
    constexpr bool isUnordered = (isHashSet<T> || isHashMap<T>);
    template<typename T>
    constexpr bool isContainer = (isSequential<T> || isAssociative<T> || isUnordered<T>);
    template<typename T> requires isContainer<T>
    struct JSONSerializable<T> {
        static string toString(const T& value) {
            JSONList list;
            for (const auto& item : value) {
                if constexpr (isMap<T>) {
                    using Key = std::remove_const_t<typename T::value_type::first_type>;
                    using Value = typename T::value_type::second_type;
                    list.push(toJSONString<Pair<Key, Value>>(item));
                }
                else if constexpr (isHashMap<T>) {
                    using Key = std::remove_const_t<typename T::value_type::first_type>;
                    using Value = typename T::value_type::second_type;
                    list.push(toJSONString<Pair<Key, Value>>(item));
                }
                else {
                    list.push(toJSONString<typename T::value_type>(item));
                }
            }
            return list.toString();
        }
        static void fromString(const string& str, T& value) {
            List<string> splitted = split(str.substr(1, str.length() - 2), { ',' });
            for (address index = 0; index < splitted.size(); ++index) {
                if constexpr (isMap<T>) {
                    using Key = std::remove_const_t<typename T::value_type::first_type>;
                    using Value = typename T::value_type::second_type;
                    value.insert(fromJSONString<Pair<Key, Value>>(splitted[index]));
                }
                else if constexpr (isHashMap<T>) {
                    using Key = std::remove_const_t<typename T::value_type::first_type>;
                    using Value = typename T::value_type::second_type;
                    value.insert(fromJSONString<Pair<Key, Value>>(splitted[index]));
                }
                else {
                    auto item = fromJSONString<typename T::value_type>(splitted[index]);
                    if constexpr (isArray<T>) {
                        value[index] = item;
                    }
                    if constexpr (isList<T>) {
                        value.emplace_back(item);
                    }
                    if constexpr (isStack<T>) {
                        value.emplace(item);
                    }
                    if constexpr (isQueue<T>) {
                        value.emplace(item);
                    }
                    if constexpr (isDeque<T>) {
                        value.emplace_back(item);
                    }
                    if constexpr (isSet<T>) {
                        value.emplace(item);
                    }
                    if constexpr (isHashSet<T>) {
                        value.emplace(item);
                    }
                }
            }
        }
    };
}
// #include "reflectable.hpp" (HPPMERGE)
namespace ASST {
    struct VoidReflector {
        template<typename T>
        void reflect(const string& str, const T& value) {
        }
    };
    template<typename T>
    concept ReflectableType = requires(T x, VoidReflector reflector) {
        { x.reflect(reflector) };
    };
}
// #include "serialize_reflectable.hpp" (HPPMERGE)
namespace ASST {
    template<ReflectableType T>
    struct JSONSerializable<T> {
        class ToStringReflector {
        public:
            template<typename U>
            void record(const string& key, const U& value) {
                m_object[key] = indent(toJSONString<U>(value));
            }
            string toString() const {
                return m_object.toString();
            }
        private:
            JSONObject m_object;
        };
        static string toString(const T& value) {
            ToStringReflector reflector;
            const_cast<T&>(value).reflect(reflector);
            return reflector.toString();
        }
        class FromStringReflector {
        public:
            FromStringReflector(const string& str)
                : m_object(str) {}
            template<typename U>
            void record(const string& key, U& value) {
                fromJSONString<U>(m_object.at(key), value);
            }
        private:
            JSONObject m_object;
        };
        static void fromString(const string& str, T& value) {
            FromStringReflector reflector(str);
            value.reflect(reflector);
        }
    };
}
// #include "serialize_optional.hpp" (HPPMERGE)
namespace ASST {
    template<typename T>
    struct JSONSerializable<Optional<T>> {
        static string toString(const Optional<T>& value) {
            if (value.has_value()) {
                return toJSONString(value.value());
            }
            else {
                return "null";
            }
        }
        static void fromString(const string& str, Optional<T>& value) {
            if (str == "null") {
                value.reset();
            }
            else {
                value = fromJSONString<T>(str);
            }
        }
    };
}
// #include "serialize_tuple.hpp" (HPPMERGE)
namespace ASST {
    template<typename... TArgs>
    struct JSONSerializable<Tuple<TArgs...>> {
        template<address Index>
        static void toStringTuple(const Tuple<TArgs...>& tuple, JSONList& list) {
            using Type = std::tuple_element_t<Index, Tuple<TArgs...>>;
            list.push(toJSONString<Type>(std::get<Index>(tuple)));
            if constexpr (Index + 1 < sizeof...(TArgs)) {
                toStringTuple<Index + 1>(tuple, list);
            }
        }
        static string toString(const Tuple<TArgs...>& value) {
            JSONList list;
            toStringTuple<0>(value, list);
            return list.toString();
        }
        template<address Index>
        static void fromStringTuple(const JSONList& list, Tuple<TArgs...>& value) {
            using Type = std::tuple_element_t<Index, Tuple<TArgs...>>;
            fromJSONString<Type>(list.at(Index), std::get<Index>(value));
            if constexpr (Index + 1 < sizeof...(TArgs)) {
                fromStringTuple<Index + 1>(list, value);
            }
        }
        static void fromString(const string& str, Tuple<TArgs...>& value) {
            fromStringTuple<0>(JSONList(str), value);
        }
    };
}
// #include "serialize_variant.hpp" (HPPMERGE)
namespace ASST {
    template<typename... TArgs>
    struct JSONSerializable<std::variant<TArgs...>> {
        template<address Index>
        static string toStringVariant(const std::variant<TArgs...>& variant) {
            using Type = std::variant_alternative_t<Index, std::variant<TArgs...>>;
            if (std::holds_alternative<Type>(variant)) {
                return toJSONString<Pair<string, Type>>({ TypeString<Type>()(), std::get<Type>(variant) });
            }
            else {
                if constexpr (Index + 1 < sizeof...(TArgs)) {
                    return toStringVariant<Index + 1>(variant);
                }
                else {
                    throw std::exception();
                }
            }
        }
        static string toString(const std::variant<TArgs...>& value) {
            return toStringVariant<0>(value);
        }
        template<address Index>
        static std::variant<TArgs...> fromStringVariant(const string& type, const string& value) {
            using Type = std::variant_alternative_t<Index, std::variant<TArgs...>>;
            if (type == TypeString<Type>()()) {
                return fromJSONString<Type>(value);
            }
            else {
                if constexpr (Index + 1 < sizeof...(TArgs)) {
                    return fromStringVariant<Index + 1>(type, value);
                }
                else {
                    throw std::exception();
                }
            }
        }
        static void fromString(const string& str, std::variant<TArgs...>& data) {
            List<string> splitted = split(str.substr(1, str.length() - 2), { ',' });
            data = fromStringVariant<0>(fromJSONString<string>(splitted[0]), splitted[1]);
        }
    };
}