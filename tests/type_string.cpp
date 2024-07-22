#include "serialize.hpp"

// Test
struct Test {};
namespace ASST {
    template<>
    struct TypeString<Test> {
        string operator()() const {
            return "Test";
        }
    };
}

using namespace ASST;
int main() {
    cout << TypeString<int>()() << endl;
    cout << TypeString<string>()() << endl;
    cout << TypeString<Stack<int>>()() << endl;
    cout << TypeString<Map<int, List<string>>>()() << endl;
    cout << TypeString<Map<int, float>>()() << endl;
    cout << TypeString<Tuple<int, string, Map<int, float>>>()() << endl;
    cout << TypeString<Test>()() << endl;
    return EXIT_SUCCESS;
}