#include <iostream>
#include <any>
#include <variant>
#include <optional>

// make && ./any.cpp_gcc; ./any.cpp_clang

void types() {
    bool                b0 {false};
    bool                b1 {true};
    //
    short               x0 {static_cast<short>(1)}; // no literal for short
    unsigned short      x1 {static_cast<unsigned short>(1u)};   // no literal for unsigned short
    int                 x2 {1};
    unsigned int        x3 {1u};
    long                x4 {1l};
    unsigned long       x5 {1ul};
    long long           x6 {1ll};
    unsigned long long  x7 {1ull};
    long long unsigned  x8 {1llu};  // OK
    long unsigned long  x9 {1LLu};  // OK, but 1lul not possible
    //
    float               f0 {1.0f};
    double              d0 {1.0};
    double              d1 {1e0};
    long double         d2 {1.0l};
    double long         d3 {1.0l};  // OK

    std::cout << typeid(b0).name() << std::endl;    // b = bool
    std::cout << typeid(x0).name() << std::endl;    // s = short
    std::cout << typeid(x1).name() << std::endl;    // t = short unsigned
    std::cout << typeid(x2).name() << std::endl;    // i = int
    std::cout << typeid(x3).name() << std::endl;    // j = int unsigned
    std::cout << typeid(x4).name() << std::endl;    // l = long
    std::cout << typeid(x5).name() << std::endl;    // m = long unsigned
    std::cout << typeid(x6).name() << std::endl;    // x = long long
    std::cout << typeid(x7).name() << std::endl;    // y = long long unsigned
    std::cout << typeid(f0).name() << std::endl;    // f = float
    std::cout << typeid(d0).name() << std::endl;    // f = double
    std::cout << typeid(d1).name() << std::endl;    // f = double
    std::cout << typeid(d2).name() << std::endl;    // e = double long
    //
    std::cout << std::endl;
    auto a0 {1.0f};
    std::cout << typeid(a0).name() << std::endl;    // f
    auto a1 {1.0};
    std::cout << typeid(a1).name() << std::endl;    // d
    auto a2 {1.0l};
    std::cout << typeid(a2).name() << std::endl;    // e
}

void test1() {
    std::any v {1};
    std::cout << std::any_cast<int>(v) << std::endl;

    v = 1.0;
    std::cout << std::any_cast<double>(v) << std::endl;

    v = 1.0f;
    std::cout << std::any_cast<float>(v) << std::endl;  // cast to double will throw bad_any_cast

    v = 1l;
    std::cout << std::any_cast<long>(v) << std::endl;    // cast to int will throw bad_any_cast

    v = 1u;
    std::cout << std::any_cast<unsigned int>(v) << std::endl;   // cast to int will throw bad_any_cast

    v = std::string{"test"};
    std::cout << std::any_cast<std::string>(v) << std::endl;
}

int main() {
    types();
    test1();
    return 0;
}

