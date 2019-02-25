#include <iostream>
#include <optional>
#include <variant>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

// "" must not have spaces, space between "" and _m is optional
constexpr long double operator ""_m (long double val) {
    // std::cout << "conversion m" << std::endl;    // not constexrp
    return val;
}

constexpr long double operator "" _cm (long double val) {
    // std::cout << "conversion cm" << std::endl;   // not constexpr
    return 0.01*val;
}

constexpr long double operator ""  _mm (long double val) {
    // std::cout << "conversion mm" << std::endl;   // not constexpr
    return 0.001*val;
}

int test1() {
    long double length1 = 1.0_m;
    long double length2 = 100.0_cm;
    long double length3 = 1000.0_mm;

    using namespace std;
    cout << "legnth1: " << length1 << endl;
    cout << "legnth2: " << length2 << endl;
    cout << "legnth3: " << length3 << endl;

    cout << "1.0 + 1.0_m = " << (1.0 + 1.0_m) << endl;  // 2
    cout << "1.0 + 1.0_cm = " << (1.0 + 1.0_cm) << endl;  // 1.01
    cout << "1.0 + 1.0_mm = " << (1.0 + 1.0_mm) << endl;  // 1.001

    return 0;
}

int main() {
    test1();
    return 0;
}

