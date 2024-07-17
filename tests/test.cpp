#include "serialize.hpp"

struct Test {
    template<typename Reflector>
    void reflect(Reflector& reflector) {
        reflector.record("tag", tag);
        reflector.record("value", value);
    }

    std::string tag;
    int value;
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
    NestedTest test = { { "HALLO", 1}, Map<int, string>({ { 0, "zero" }, { 1, "one" }, { 2, "two" }, { 3, "three" }, { 4, "four" }, { 5, "five" } })};
    ASST::JSONSerializer::serialize("/home/flo/dev/asset/test.json", test);
    std::cout << "Hello World!" << std::endl;

    std::cout << ASST::JSONSerializer::fromString<std::string>("\"asdasd\"") << std::endl;
    auto map = JSONSerializer::fromString<Map<int, string>>("[[1,\"on,,[e\"],[2,\"two\"],[3,\"three\"]]");
    for (auto& [key, value] : map) {
        std::cout << "Key: " << key << ", Value: " << value << std::endl;
    }
    auto test2 = JSONSerializer::deserialize<NestedTest>("/home/flo/dev/asset/test.json");
    ASST::JSONSerializer::serialize("/home/flo/dev/asset/testto.json", test2);
    return EXIT_SUCCESS;
}