#include "serialize.hpp"

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
struct NestedTest {
    template<typename Reflector>
    void reflect(Reflector& reflector) {
        reflector.record("test", test);
        reflector.record("numToLit", numToLit);
    }

    Test test;
    ASST::Map<int, std::string> numToLit;
};

using namespace ASST;
int main() {
    uchar ch = 'A';
    Map<int, string> map = { { 0, "zero" }, { 1, "one" }, { 2, "two" }, { 3, "three" }, { 4, "four" }, { 5, "five" } };
    Pair<string, string> value("HALL\nO", "Ciau");
    NestedTest test = { { "Tag", 42, "HALLO", 1, { 3, 2.0F} }, map };

    JSONSerializer::serialize("/home/flo/dev/serialize/test.json", List<NestedTest>({ test }));
    auto result = JSONSerializer::deserialize<List<NestedTest>>("/home/flo/dev/serialize/test.json");
    return EXIT_SUCCESS;
}