#include "serialize.hpp"

// Test
struct Test {
    template<typename Reflector>
    void reflect(Reflector& reflector) {
        reflector.record("tag", tag);
        reflector.record("value", value);
        reflector.record("opt", opt);
        reflector.record("variant", variant);
        reflector.record("tuple", tuple);
    }

    std::string tag;
    int value;
    std::optional<std::string> opt;
    std::variant<int, float> variant;
    std::tuple<int, float> tuple;
};
namespace ASST {
    template<>
    struct TypeString<Test> {
        string operator()() const {
            return "Test";
        }
    };
}

using namespace ASST;
string root = "/home/flo/dev/serialize/examples/";
int main() {
    // primitives
    using Primitives = std::tuple<bool, char, signed char, uchar, int16, uint16, int32, uint32, int64, uint64, float, double>;
    JSONSerializer::serialize(root + "primitive.json", Primitives(
        true, 'A', -12, 2, -1, 1, -1, 1, -1, 1, 1.0f, 1.0
    ));
    auto res1 = JSONSerializer::deserialize<Primitives>(root + "primitive.json");
    // string
    JSONSerializer::serialize(root + "string.json", std::string("Hello, World!"));
    auto res2 = JSONSerializer::deserialize<std::string>(root + "string.json");
    // pair
    JSONSerializer::serialize(root + "pair.json", std::pair<int, std::string>(42, "Hello, World!"));
    auto res3 = JSONSerializer::deserialize<std::pair<int, std::string>>(root + "pair.json");
    // map
    JSONSerializer::serialize(root + "map.json", std::map<std::string, int>{{ "key1", 1 }, { "key2", 2 }});
    auto res4 = JSONSerializer::deserialize<std::map<std::string, int>>(root + "map.json");
    // set
    JSONSerializer::serialize(root + "set.json", std::set<int>({1, 2, 3, 4, 5}));
    auto res5 = JSONSerializer::deserialize<std::set<int>>(root + "set.json");
    // list
    JSONSerializer::serialize(root + "vector.json", std::vector<int>{1, 2, 3, 4, 5});
    auto res6 = JSONSerializer::deserialize<std::vector<int>>(root + "vector.json");
    // optional
    JSONSerializer::serialize(root + "optional.json", std::optional<int>(42));
    auto res7 = JSONSerializer::deserialize<std::optional<int>>(root + "optional.json");
    // object
    JSONSerializer::serialize(root + "object.json", Test({ "HALLO", 42, {}, 1.0F, { 1, 2.0F }}));
    auto res8 = JSONSerializer::deserialize<Test>(root + "object.json");
    // variant
    JSONSerializer::serialize(root + "variant.json", std::variant<int, std::string>(42));
    auto res9 = JSONSerializer::deserialize<std::variant<int, std::string>>(root + "variant.json");
    // tuple
    JSONSerializer::serialize(root + "tuple.json", std::tuple<int, float>(42, 1.0F));
    auto res10 = JSONSerializer::deserialize<std::tuple<int, float>>(root + "tuple.json");
    return EXIT_SUCCESS;
}