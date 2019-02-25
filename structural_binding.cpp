#include <iostream>
#include <tuple>
#include <variant>
#include <vector>
#include <array>
#include <set>

void test1() {
    std::tuple<uint16_t> t1 {1};
    std::tuple<uint16_t,uint16_t> t2 {2,3};
    std::tuple<uint16_t,uint16_t,uint16_t> t3 {4,5,6};

    using namespace std;
    cout << std::get<0>(t1) << endl;
    cout << std::get<0>(t2) << endl;
    cout << std::get<1>(t2) << endl;
    cout << std::get<0>(t3) << endl;
    cout << std::get<1>(t3) << endl;
    cout << std::get<2>(t3) << endl;

    // both tuple and variant are accessed with get function

    std::variant<uint16_t, double> v {1.0};
    cout << std::get<1>(v) << endl;
    v = static_cast<uint16_t>(1);
    cout << std::get<0>(v) << endl;
    try {
        cout << std::get<1>(v) << endl;
    } catch (bad_variant_access&) {
        cout << "index 1 currently not set" << endl;
    }

    //
    auto [v1,v2,v3] = t3;
    std::vector vec {0,1,2};
}

int main() {
    test1();
    return 0;
}

