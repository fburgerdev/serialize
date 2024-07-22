#include "serialize.hpp"
#include "trace.hpp"

// Test
struct Test {
    template<typename Reflector>
    void reflect(Reflector& reflector) {
        reflector.record("tag", tag);
        reflector.record("value", value);
        reflector.record("opt", opt);
        reflector.record("variant", variant);
        reflector.record("tuple", tuple);
        reflector.record("list", list);
    }

    std::string tag;
    int value;
    std::optional<std::string> opt;
    std::variant<int, float> variant;
    std::tuple<int, float> tuple;
    std::vector<int> list;
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
    auto res = JSONSerializer::deserialize<Test>(root + "error.json");
    return EXIT_SUCCESS;
}